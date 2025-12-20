
undefined4 main(void)
{
  long ptraceRes;
  undefined4 retvalue;
  char *newBuffer;
  int fd_preload;
  int syscall_fd;
  __uid_t uid;
  uint getsRes;
  int in_GS_OFFSET;
  char buffer [256];
  int local_14;
  bool loop_flag;
  FILE *stdout_var;
  
  local_14 = *(int *)(in_GS_OFFSET + 0x14);
  loop_flag = false;
  fd_preload = 1;
  stdout_var = NULL;
  ptraceRes = ptrace(PTRACE_TRACEME,0,1,0);
  if (ptraceRes < 0)
  {
    newBuffer = "You should not reverse this";
    puts("You should not reverse this");
    retvalue = 1;
  }
  else
  {
    newBuffer = getenv("LD_PRELOAD");
    if (newBuffer == NULL)
    {
      fd_preload = open("/etc/ld.so.preload",0);
      if (fd_preload < 1)
      {
        syscall_fd = syscall_open();
        if (syscall_fd == -1)
        {
          fd_preload = 70;
          stdout_var = (FILE *)0x1;
          newBuffer = "/proc/self/maps is unaccessible, probably a LD_PRELOAD attempt exit..\n";
          fwrite("/proc/self/maps is unaccessible, probably a LD_PRELOAD attempt exit..\n",1,70,
                 stderr);
          retvalue = 1;
        }
        else
        {
          do
          {
            do
            {
              while( true )
              {
                stdout_var = (FILE *)256;
                newBuffer = buffer;
                fd_preload = syscall_fd;
                getsRes = syscall_gets((int)newBuffer,256);
                if (getsRes == 0) goto LAB_08048ead;
                fd_preload = isLib(buffer,0x8049063);
                if (fd_preload == 0) break;
                loop_flag = true;
              }
            } while (!loop_flag);
            fd_preload = isLib(buffer,0x8049068);
            if (fd_preload != 0)
            {
              fd_preload = 32;
              fwrite("Check flag.Here is your token : ",1,32,stdout);
              uid = getuid();
              stdout_var = stdout;
              if (uid == 3006)
              {
                newBuffer = ft_des("H8B8h_20B4J43><8>\\ED<;j@3");
                fputs(newBuffer,stdout_var);
              }
              else if (uid < 3007)
              {
                if (uid == 3002)
                {
                  newBuffer = ft_des("<>B16\\AD<C6,G_<1>^7ci>l4B");
                  fputs(newBuffer,stdout_var);
                }
                else if (uid < 3003)
                {
                  if (uid == 3000)
                  {
                    newBuffer = ft_des("I`fA>_88eEd:=`85h0D8HE>,D");
                    fputs(newBuffer,stdout_var);
                  }
                  else if (uid < 3001)
                  {
                    if (uid == 0)
                    {
                      fd_preload = 33;
                      fwrite("You are root are you that dumb ?\n",1,33,stdout);
                    }
                    else
                    {
LAB_08048e06:
                      fd_preload = 56;
                      fwrite("\nNope there is no token here for you sorry. Try again :)",1,56,stdout
                            );
                    }
                  }
                  else
                  {
                    newBuffer = ft_des("7`4Ci4=^d=J,?>i;6,7d416,7");
                    fputs(newBuffer,stdout_var);
                  }
                }
                else if (uid == 3004)
                {
                  newBuffer = ft_des("?4d@:,C>8C60G>8:h:Gb4?l,A");
                  fputs(newBuffer,stdout_var);
                }
                else if (uid < 3005)
                {
                  newBuffer = ft_des("B8b:6,3fj7:,;bh>D@>8i:6@D");
                  fputs(newBuffer,stdout_var);
                }
                else
                {
                  newBuffer = ft_des("G8H.6,=4k5J0<cd/D@>>B:>:4");
                  fputs(newBuffer,stdout_var);
                }
              }
              else if (uid == 3010)
              {
                newBuffer = ft_des("74H9D^3ed7k05445J0E4e;Da4");
                fputs(newBuffer,stdout_var);
              }
              else if (uid < 3011)
              {
                if (uid == 3008)
                {
                  newBuffer = ft_des("bci`mC{)jxkn<\"uD~6%g7FK`7");
                  fputs(newBuffer,stdout_var);
                }
                else if (uid < 3009)
                {
                  newBuffer = ft_des("78H:J4<4<9i_I4k0J^5>B1j`9");
                  fputs(newBuffer,stdout_var);
                }
                else
                {
                  newBuffer = ft_des("Dc6m~;}f8Cj#xFkel;#&ycfbK");
                  fputs(newBuffer,stdout_var);
                }
              }
              else if (uid == 3012)
              {
                newBuffer = ft_des("8_Dw\"4#?+3i]q&;p6 gtw88EC");
                fputs(newBuffer,stdout_var);
              }
              else if (uid < 3012)
              {
                newBuffer = ft_des("70hCi,E44Df[A4B/J@3f<=:`D");
                fputs(newBuffer,stdout_var);
              }
              else if (uid == 3013)
              {
                newBuffer = ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
                fputs(newBuffer,stdout_var);
              }
              else
              {
                if (uid != 3014) goto LAB_08048e06;
                newBuffer = ft_des("g <t61:|4_|!@IF.-62FH&G~DCK/Ekrvvdwz?v|");
                fputs(newBuffer,stdout_var);
              }
              newBuffer = (char *)0xa;
              stdout_var = stdout;
              fputc(10,stdout);
              goto LAB_08048ead;
            }
            newBuffer = afterSubstr(buffer,0x8049281);
          } while (newBuffer != NULL);
          fd_preload = 0x30;
          stdout_var = (FILE *)0x1;
          newBuffer = "LD_PRELOAD detected through memory maps exit ..\n";
          fwrite("LD_PRELOAD detected through memory maps exit ..\n",1,0x30,stderr);
LAB_08048ead:
          retvalue = 0;
        }
      }
      else
      {
        fd_preload = 0x25;
        stdout_var = (FILE *)0x1;
        newBuffer = "Injection Linked lib detected exit..\n";
        fwrite("Injection Linked lib detected exit..\n",1,0x25,stderr);
        retvalue = 1;
      }
    }
    else
    {
      fd_preload = 0x25;
      stdout_var = (FILE *)0x1;
      newBuffer = "Injection Linked lib detected exit..\n";
      fwrite("Injection Linked lib detected exit..\n",1,0x25,stderr);
      retvalue = 1;
    }
  }
  if (local_14 == *(int *)(in_GS_OFFSET + 0x14))
  {
    return retvalue;
  }
  __stack_chk_fail(newBuffer,stdout_var,fd_preload);
}


