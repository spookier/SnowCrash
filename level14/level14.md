## Phase 1: Reconnaissance

After logging in, there are no files or hints in the home directory...

We search the filesystem for a while but do not find anything relevant besides the `getflag` binary itself   

To analyze it properly, we copy the binary to our host machine:

```bash
scp -P 4242 level14@192.168.1.111:/bin/getflag .
```

---

## Phase 2: Static Analysis

We load the binary into **Ghidra** and analyze the program flow

A critical portion of the decompiled code looks like this:

```c
  ptraceRes = ptrace(PTRACE_TRACEME,0,1,0);
  if (ptraceRes < 0)
  {
    newBuffer = "You should not reverse this";
    puts("You should not reverse this");
    retvalue = 1;
  }
  
```

This reveals an **anti-debugging protection**

The function `ptrace(PTRACE_TRACEME)` is used to detect if the program is being traced
>  Being traced means that another program is watching/controlling the program while it runs

- If the program **is being traced**, `ptrace` returns `-1`
- If the program **is NOT being traced**, `ptrace` returns `0`

> Basically `-1` means “a debugger is already attached” or “someone is trying to reverse this program”


So when running `getflag` inside `gdb`, this call returns `-1`, causing the program to exit early

This explains why the program immediately quits when debugged

---

## Phase 3: Bypassing ptrace

As we saw before, On 32-bit x86 Linux, function return values are stored in the **`$eax` register**

So after calling `ptrace`, its return value is stored in `$eax`

From Ghidra, we identify the relevant instructions:

```asm
      08048989 e8 b2 fb      CALL      <EXTERNAL>::ptrace
      0804898e 85 c0         TEST      EAX,EAX
```

We set a breakpoint right after the `ptrace` call:

```bash
gdb getflag
```

```gdb
(gdb) b *0x0804898e
(gdb) run
(gdb) i r
```

When inspecting registers `i r` we observe:

```
eax = 0xffffffff   (-1)
```

We can see `$eax` was set to `-1` by `ptrace`, so we change it to a positive value

```gdb
(gdb) set $eax = 10
(gdb) i r
...
eax            0xa	10
...
```

Now the program believes it is **not being debugged**

We then run `continue` and execute the normal flow of the program

```gdb
(gdb) continue

Check flag.Here is your token :
Nope there is no token here for you sorry. Try again :)
```

- This means we successfully escaped the `ptrace` protection mechanism

---

## Phase 4: Automating the Bypass

To simplify repeated testing, we create a gdb script in `/tmp/exploitscript`:

```text
b *0x804898e
run
set $eax=100
i r
b *0x08048afd
continue
i r
```

We execute it using:

```bash
gdb getflag -x /tmp/exploitscript -q
```

---

## Phase 5: UID Check Bypass

Next, we identify where the program calls `getuid()`
> We need this instruction to know when we are able to change `$eax`

- From Ghidra, we see the first `getuid` is called at `0x08048afd`
- So we go to the next address where `$eax` is being interracted with, at `0x08048b02`

- In gdb, we set a breakpoint at `0x08048b02`
- We see the returned UID (`2014`) is placed into `$eax`

We overwrite it with the highest UID we can find from the decompiled code, which would mean last level

```gdb
set $eax = 3014
```

Now we allow the program to continue:

```gdb
continue
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```

---

## Phase 6: Final Step 🏴‍☠️

We switch to the `flag14` user and confirm the solution:

```bash
su flag14
getflag
```

Output:

```txt
Congratulation. Type getflag to get the key and send it to me the owner of this livecd :)
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```
