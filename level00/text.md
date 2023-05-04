# --- reconnaisance ---

- whoami
- ls -la
- cat /etc/passwd | cut -d: -f1
- pwd
- search all my files on system with find / -user username -ls
- groups

~ nothing found here

---

# --- target research on system ---

~ searching for user didn't work lets try searching for the groups flag

- find / -user flag00 2> /dev/null
> " 2> /dev/null " = redirects any error messages that occur during the search to the null device (/dev/null) so you dont get access denied errors spammed on screen

- found two paths that lead to weird text
- tried https://www.dcode.fr/cipher- on the texts and found password


# --- solved ---

- password: nottoohardhere
