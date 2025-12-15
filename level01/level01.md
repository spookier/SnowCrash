## Phase 1: Reconnaissance

Same thing as the last level, I used the following commands to gather initial information:

- `whoami` - To identify the current user
- `ls -la` - To list all files in the current directory with detailed information
- `cat /etc/passwd | cut -d: -f1` - To list all users in the system
- `pwd` - To identify the current working directory
- `find / -user level01 -ls` - To search for all files in the system owned by the user level00, nothing interesting aswell, but we get permission denied on level04 and level12, maybe useful later?
- `groups` - To list all groups the current user is a part of

**Findings:** Nothing significant found...

---


## Phase 2: Target Research on System

Then again, we focus on `flag01`

- `find / -user flag01` - Searching for all files owned by user `flag01`, nothing interesting...
- `cat /etc/passwd` revealed an interesting entry

```
level12:x:2012:2012::/home/user/level12:/bin/bash
level13:x:2013:2013::/home/user/level13:/bin/bash
level14:x:2014:2014::/home/user/level14:/bin/bash
flag00:x:3000:3000::/home/flag/flag00:/bin/bash
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
flag02:x:3002:3002::/home/flag/flag02:/bin/bash
flag03:x:3003:3003::/home/flag/flag03:/bin/bash
```
- `flag01` password hash is exposed, this means it can be cracked
- We can assume its an old encryption system since modern hashes are much longer (MD5 uses ~34 chars, SHA-256 uses ~60 chars)
- We copy its hash `flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash` and try to crack it with John The Ripper
- We will use John The Ripper and compile and build it locally since installing anything is not allowed on School PCs
```console
git clone https://github.com/openwall/john.git
cd john/src && ./configure && make -s clean && make -sj24
cd ../run
echo "flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash" > password && ./john password
```
- The hash was successfully cracked, we get `abcdefg          (flag01)`
- The complete hash is now `flag01:abcdefg:` instead of `flag01:42hDRfypTqqnw:`
- We run `su flag01` and use this decrypted hash as password

