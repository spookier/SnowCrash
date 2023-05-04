# --- reconnaisance ---

- whoami
- ls -la
- cat /etc/passwd | cut -d: -f1
- pwd
- search all my files on system with find / -user username -ls
- groups
- printenv
- ls -l /etc/shadow
> (no permissions)



# --- target research on system ---

- find / -user level01
- find / -user flag01

? (SSH_TTY=/dev/pts/0)

- cat /etc/passwd
found something...

flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash

- use john the ripper to crack password with rockyou.txt wordlist

- john the ripper successfully cracked the password

# --- solved ---

- password: abcdefg
