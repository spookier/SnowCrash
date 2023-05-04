# --- reconnaisance ---
- ls -la

- found executable 

- once ran it asks to be exploited (uwu)
>so probably indentifying and exploiting a vulnerability like buffer overflow?


# --- target research on system ---

- lets do some analysis on the file

- file ./level03
```txt
./level03: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0x3bee584f790153856e826e38544b9e80ac184b7b, not stripped
```
>so its an executable...

- strings ./level03
> revealed it.s a c file, gnu c 4.6.3 compiled exec, uses types.h 
- look for vulnerable functions in the output
>vulnerable functions like strcpy, gets, scanf, sprintf, memcpy 
- strings ./level03 | grep "strcpy"
>nothing interesting..


- lets intercept .dll calls with ltrace ./level03
```txt
__libc_start_main(0x80484a4, 1, 0xbffff6e4, 0x8048510, 0x8048580 <unfinished ...>
getegid()                                                                                                  = 2003
geteuid()                                                                                                  = 2003
setresgid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280)                                                        = 0
setresuid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280)                                                        = 0
system("/usr/bin/env echo Exploit me"Exploit me
 <unfinished ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                                                                     = 0
```
- maybe system() function exploitable ?
> this function is used to call a shell command (/usr/bin/env echo Exploit me)
> 





## --- solved ---
