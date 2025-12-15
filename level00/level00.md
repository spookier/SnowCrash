## Phase 1: Reconnaissance

I used the following commands to gather initial information:

- `whoami` - To identify the current user
- `ls -la` - To list all files in the current directory with detailed information
- `cat /etc/passwd | cut -d: -f1` - To list all users in the system
- `pwd` - To identify the current working directory
- `find / -user level00 -ls` - To search for all files in the system owned by the user level00, nothing really interesting
- `groups` - To list all groups the current user is a part of

**Findings:** Nothing significant found...

---

## Phase 2: Target Research on System

level00 search resulted in nothing interesting, so I changed my focus to the name of the flag `flag00`  

- `find / -user flag00 2> /dev/null` 
- This search led to two paths containing weird text
- `/usr/sbin/john` and `/rofs/usr/sbin/john`
- After doing `cat /usr/sbin/john` we get the following text: `cdiiddwpgswtgt`
- The text was entered into [dcode.fr](https://www.dcode.fr/cipher-), clicked on the many results until one of the Disk Cipher methods reveals a password
- <details>
        <summary><b>PASSWORD</b></summary>
        nottoohardhere
</details>

- Finally we run `su flag00` with this password and run `getflag` and get our token for the next level

---

