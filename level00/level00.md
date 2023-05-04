## Phase 1: Reconnaissance

The following commands were executed to gather initial information:

- `whoami` - To identify the current user
- `ls -la` - To list all files in the current directory with detailed information
- `cat /etc/passwd | cut -d: -f1` - To list all users in the system
- `pwd` - To identify the current working directory
- `find / -user username -ls` - To search for all files in the system owned by the user
- `groups` - To list all groups the current user is a part of

**Findings:** No significant discoveries were made in this phase

---

## Phase 2: Target Research on System

With the user search resulting in no results, the focus was shifted to the group `flag`

- The command `find / -user flag00 2> /dev/null` was executed
> The `2> /dev/null` portion redirects any error messages that occur during the search to the null device (`/dev/null`), preventing "access denied" errors from cluttering the screen
- This search led to two paths containing weird text
- The texts were entered into [dcode.fr](https://www.dcode.fr/cipher-) for cipher decryption, revealing a password

---

## Solved

The discovered password is provided below:

<details>
        <summary>Click to reveal password</summary>
        nottoohardhere
</details>  
