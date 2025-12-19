## Phase 1: Reconnaissance

When connecting to the level, we find a single file in the home directory:
- A binary named `level13`

Since no source code is provided, the next step is to analyze the binary

---

## Phase 2: Static Analysis

We copy the binary to our local machine and decompile it using **Ghidra**

The simplified decompiled C code is:

```c
void main(void)
{
    __uid_t uid;
    char *token;

    uid = getuid();
    if (uid != 4242)
    {
        uid = getuid();
        printf("UID %d started us but we we expect %d\n", uid, 4242);
        exit(1);
    }
    token = ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
    printf("your token is %s\n", token);
    return;
}
```


---


From the code, the program logic is very simple:

- The program retrieves our **real user ID** using `getuid()`
- It checks if our UID is equal to **4242**
- If our UID is not 4242, the program exits
- If our UID is 4242, the program decrypts and prints the token

We verify our current UID:

```bash
echo $UID
```

Output:
```
2013
```

This means to get the flag, we must change our UID to `4242`

---

## Phase 3: Vulnerability Research

After some research we find the following information:

> On **32-bit x86 Linux**, function return values follow a strict convention:
>
> - Return values up to 32 bits are stored in the **EAX register**
> - This includes integers, pointers, and types like `uid_t`

Since `getuid()` returns a `uid_t`, it means its return value is placed in **`$eax`**

This means:
- After `getuid()` is called
- The UID value (`2013`) is stored in `$eax`
- If we modify `$eax` before the comparison, we can bypass the UID check

---

## Phase 4: Exploitation

We will use **GDB** to modify the value of `$eax`


```bash
gdb ./level13
```

Set a breakpoint at `main` and run:
```gdb
(gdb) b main
(gdb) run
```

Step through the program instruction by instruction:
```gdb
(gdb) ni
```

After each instruction, inspect the registers:
```gdb
(gdb) i r
```

We continue stepping until we see `eax = 2013`

On the third `ni` call, we can see `$eax = 2013`, this means `getuid()` just returned the value


Now we overwrite the register:
```gdb
(gdb) set $eax = 4242
(gdb) i r
```

The register now holds the expected UID

Finally, we let the program continue until it ends:
```gdb
(gdb) continue
```

The program prints the token:

```txt
your token is 2A31L79asukciNyi8uppkEuSx
```

We use this to connect to level14 😎
