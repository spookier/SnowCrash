# --- reconnaisance ---
- ls -la

- found executable 

- once ran it asks to be exploited (uwu) so probably indentifying and exploiting a vulnerability (like buffer overflow)


# --- target research on system ---

- will do some analysis on the file

- file ./level03
```txt
./level03: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0x3bee584f790153856e826e38544b9e80ac184b7b, not stripped
```
- strings ./level03
- look for vulnerable functions like strcpy, gets, scanf, sprintf, memcpy
strings ./level03 | grep "mem"

- revealed it.s a c file, gnu c 4.6.3 compiled exec, uses types.h lib

- nothing interesting





## --- solved ---
