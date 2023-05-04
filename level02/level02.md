# --- reconnaisance ---

- ls -la

- use scp command to transfer pcap file to local machine
> depending on the way u configured access to ur VM scp command may vary
> example: scp ./level02.pcap spxxky@192.xxx.x.xxx:/home/spxxky/Desktop/savehere

- found pcap file that needed to be inspected with wireshark
>follow -> TCP stream

- file contains:
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
- lets try password found in packet


- passwords didnt work
>ft_wandr
>ft_wandr...NDRel.L0L
>NDRel.L0L

# --- target research on system ---

- trying to find files related to wwwbugs / www / bugs / ft_wandr
- find / -iname "*wwwbugs*" 2>/dev/null

- nothing found 

- back to wireshark to further inspect packet in Hexdump view
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
- found that 7f in hexa means delete and 0d enter

## --- solved ---

- password: ft_waNDReL0L