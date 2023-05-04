# Penetration Testing Report: Level01

## Phase 1: Reconnaissance

The following commands were executed to gather initial information:

- `whoami` - To identify the current user
- `ls -la` - To list all files in the current directory with detailed information
- `cat /etc/passwd | cut -d: -f1` - To list all users in the system
- `pwd` - To identify the current working directory
- `find / -user username -ls` - To search for all files in the system owned by the user
- `groups` - To list all groups the current user is a part of
- `printenv` - To print all or part of the environment
- `ls -l /etc/shadow` - To check the shadow file permissions (Access was denied)

---

## Phase 2: Target Research on System

The focus was directed towards user `level01` and group `flag01`:

- `find / -user level01` - To search for all files owned by user `level01`
- `find / -user flag01` - To search for all files owned by user `flag01`

The command `cat /etc/passwd` revealed an interesting entry:

```
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
```

John the Ripper was utilized to crack the encrypted password, using `rockyou.txt` as the wordlist

The password was successfully cracked

---

## Solved

The cracked password is provided below:

<details>
        <summary>Click to reveal password</summary>
        abcdefg
</details>  
