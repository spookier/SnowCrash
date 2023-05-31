## Phase 1: Reconnaissance

Initial investigation involved listing the directory contents with `ls -la`

A pcap file was identified and transferred to the local machine for inspection using the `scp` command:

```bash
scp ./level02.pcap spxxky@192.xxx.x.xxx:/home/spxxky/Desktop/savehere
```

Note: The specific `scp` command may vary based on your VM access configuration

The pcap file was then inspected using Wireshark, with the "Follow -> TCP Stream" function

The contents included:

```txt
>? Linux 2.6.38-8-generic-pae (::ffff:10.1.1.2) (pts/10)
>
>..wwwbugs login: l.le.ev.ve.el.lX.X
>..
>Password: ft_wandr...NDRel.L0L
>.
>..
>Login incorrect
>wwwbugs login: 
```

Several potential passwords were identified and tested, but none were successful:

- `ft_wandr`
- `ft_wandr...NDRel.L0L`
- `NDRel.L0L`

---

## Phase 2: Target Research on System

The search was extended to look for files related to the keywords "wwwbugs", "www", "bugs", and "ft_wandr"

```bash
find / -iname "*wwwbugs*" 2>/dev/null
```

No relevant files were found...

A return to Wireshark for further packet inspection in Hexdump view revealed the following:

```hex
000000B9  66                                                 f
000000BA  74                                                 t
000000BB  5f                                                 _
000000BC  77                                                 w
000000BD  61                                                 a
000000BE  6e                                                 n
000000BF  64                                                 d
000000C0  72                                                 r
000000C1  7f                                                 .
000000C2  7f                                                 .
000000C3  7f                                                 .
000000C4  4e                                                 N
000000C5  44                                                 D
000000C6  52                                                 R
000000C7  65                                                 e
000000C8  6c                                                 l
000000C9  7f                                                 .
000000CA  4c                                                 L
000000CB  30                                                 0
000000CC  4c                                                 L
000000CD  0d                                                 .
```

- I discovered that '7f' in hex represents a delete action and '0d' represents enter

> That means, '7f' deletes the last keystroke and '0d' confirms and sends the message

---

## Solved

The deciphered password is provided below:

<details>
        <summary>Click to reveal password</summary>
        ft_waNDReL0L
</details>  


