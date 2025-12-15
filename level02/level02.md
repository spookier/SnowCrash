## Phase 1: Reconnaissance

As with previous levels, the first step was to inspect the current directory and identify any unusual files

- `ls -la` gives us a file named `level02.pcap`

`.pcap ` is a **packet capture** file, suggesting that it can be opened with Wireshark

To analyze it properly, we must first transfer the file to our local machine

```bash
scp -P 4242 level02@REPLACE_WITH_VM_IP:~/level02.pcap .
```

---

## Phase 2: Packet Analysis

- We open the `.pcap` file with **Wireshark**
- We click Follow -> PCP Stream
- We get the following data:
```txt
Linux 2.6.38-8-generic-pae (::ffff:10.1.1.2) (pts/10)

..wwwbugs login: l.le.ev.ve.el.lX.X
..
Password: ft_wandr...NDRel.L0L
.
..
Login incorrect
wwwbugs login: 
```

We try several possible passwords from the data:
```
- ft_wandr
- ft_wandr...NDRel.L0L
- NDRel.L0L
```
- However, **none of these work**
- To better understand the captured keystrokes we do a deeper analysis with hexdump
- On Wireshark choose "Show data as Hex Dump"


```hex
000000D6  00 0d 0a 50 61 73 73 77  6f 72 64 3a 20            ...Passw ord: 
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

### Interpretation

- `0x7f` in Hex this means **Delete / Backspace**
- `0x0d` in Hex this means **Enter / Submit**

This means:
- The user typed characters
- Then deleted some of them (`7f`)
- And finally submitted the corrected input (`0d`)
---

- By reconstructing the keystrokes we get the following:
- `ft_waNDReL0L`
- We use this as password to su into flag02 and getflag successfully


- *In contrast, because this login uses an interactive terminal protocol like Telnet, every keypress is sent byte-by-byte through TCP... if this was SSH, the traffic would be encrypted and typically only the final line would be sent to the server, so this kind of reconstruction would not be possible*
