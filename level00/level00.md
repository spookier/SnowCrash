## Phase 1: Reconnaissance

I used the following commands to gather initial information:

- `whoami` - To identify the current user
- `ls -la` - To list all files in the current directory with detailed information
- `cat /etc/passwd | cut -d: -f1` - To list all users in the system
- `pwd` - To identify the current working directory
- `find / -user username -ls` - To search for all files in the system owned by the user
- `groups` - To list all groups the current user is a part of

**Findings:** Nothing significant found...

---

## Phase 2: Target Research on System

User search resulted in no results so I changed my focus to the name of the flag `flag00`

- `find / -user flag00 2> /dev/null` 
- This search led to two paths containing weird text
- `/usr/sbin/john` and `/rofs/usr/sbin/john`
- The texts were entered into [dcode.fr](https://www.dcode.fr/cipher-) for cipher decryption, revealing a password

---

## Solved

The discovered password is provided below:

<details>
        <summary>Click to reveal password</summary>
        nottoohardhere
</details>  
