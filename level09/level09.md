## Phase 1: Reconnaissance

Upon connecting to the level, we find two files in the home directory:
- A binary named `level09`
- A data file named `token`

Running the binary without arguments shows that it expects an input parameter  
After several tests it becomes clear that the binary **transforms (encrypts)** the input we provide

Using `strings` on the binary reveals the message:

```
You should not reverse this
```

Based on this hint, we avoid reversing the binary itself and instead focus on **understanding the encryption logic**

---

## Phase 2: Algorithm Observation

By experimenting with different inputs we notice some patterns

- The **first character never changes**
- Each following character is incremented by **its index** in the string
- The transformation is based on the **ASCII table**

Examples:

- Input: `00000`  
  Output: `01234`

- Input: `0000a`  
  Output: `0123e`  
  (`a + 4 = e`)


### More examples
- For `1a2b` =>
    - 1 stays same
    - a becomes a + 1 = b
    - 2 becomes 2 + 2 = 4
    - b becomes b + 3 = e
    - = `1b4e`


- Now for `gdf8e`
    - g stays same
    - d + 1 = e
    - f + 2 = h
    - 8 + 3 = ;
    - e + 4 = i
    -  = `geh;i`

---

## Phase 3: Token Analysis

Attempting to read the `token` file directly:

```bash
cat token
```

Produces unreadable output:

```txt
f4kmm6p|=�p�n��DB�Du{��
```

This hints that the token might be **encrypted using the same algorithm** and must be **decrypted by reversing the logic**

---

## Phase 4: Decryption Strategy

Since now we understand how the encryption works, we write a small C program to decrypt the token file

### Decryption Code

```c

	int i = 0;
	while ((bytes_read = read(fd, &c, 1)) > 0)
	{
		if(c == '\n')
		    break ;

		new_char = c - i;

		printf("[%d]	=	%02x	=> %c\n", i + 1, new_char, new_char);
		buffer[i] = new_char;
		i++;
	}
	buffer[i] = 0;

	printf("\n[END] - final string is: %s", buffer);
	
```

---

## Phase 5: Decryption

Running our decryption program on the `token` file gives us:

```txt

[1]     =	66	=> f
[2]     =	33	=> 3
[3]     =	69	=> i
[4]     =	6a	=> j
[5]     =	69	=> i
[6]     =	31	=> 1
[7]     =	6a	=> j
[8]     =	75	=> u
[9]     =	35	=> 5
[10]	=	79	=> y
[11]	=	75	=> u
[12]	=	65	=> e
[13]	=	76	=> v
[14]	=	61	=> a
[15]	=	75	=> u
[16]	=	73	=> s
[17]	=	34	=> 4
[18]	=	31	=> 1
[19]	=	71	=> q
[20]	=	31	=> 1
[21]	=	61	=> a
[22]	=	66	=> f
[23]	=	69	=> i
[24]	=	75	=> u
[25]	=	71	=> q

[END] - final string is: f3iji1ju5yuevaus41q1afiuq  
```

---

## Phase 6: Getting the Flag

Using the decrypted token:

```bash
su flag09
getflag
```

Output:

```txt
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
```

