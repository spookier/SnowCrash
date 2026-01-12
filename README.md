<div align="center">
  <img src="https://github.com/user-attachments/assets/26566604-559b-4b95-8c25-ea0ecdfce446" width="550" alt="prepare to crash">





  
## ☠️ 🚫  BEWARE TARNISHED 🚫  ☠️

This repo contains my writeups and solutions for SnowCrash, an offensive security project at 42 School


Each level required finding and exploiting a specific vulnerability from forensics, scripting, race conditions, reverse engineering and binary exploitation to escalate privileges and grab the flag


| Level | Key Focus                                      | Link                          |
|-------|------------------------------------------------|-------------------------------|
| 00    | Linux reconnaissance and basic cryptography    | [View](./level00)            |
| 01    | Password hash cracking                         | [View](./level01)            |
| 02    | Network packet forensics                     | [View](./level02)            |
| 03    | PATH Interception Attack                | [View](./level03)            |
| 04    | Command injection in CGI scripts             | [View](./level04)            |
| 05    | Cron job misconfiguration exploitation         | [View](./level05)            |
| 06    | PHP remote code execution                      | [View](./level06)            |
| 07    | Argument injection in system()                     | [View](./level07)            |
| 08    | Bypassing access with Symlink attack              | [View](./level08)            |
| 09    | Behavioral analysis of custom encryption          | [View](./level09)            |
| 10    | TOCTOU race condition exploitation             | [View](./level10)            |
| 11    | Command injection + bypassing sanitization                  | [View](./level11)            |
| 12    | Input processing bypass on a web server             | [View](./level12)            |
| 13    | Debug and modify CPU registers to bypass security checks           | [View](./level13)            |
| 14    | Advanced binary protection bypass               | [View](./level14)            |

</div>

---





# Snowcrash VM Login Guide

### (NAT + Port Forward)  
### VirtualBox → SnowCrash → Settings → Network



1 - Attached to: NAT

2- Click Advanced → Port Forwarding then add a rule:
- Protocol: TCP
- Host IP: 127.0.0.1
- Host Port: 2222
- Guest IP: (leave empty)
- Guest Port: 4242

3 - You can SSH to the VM now.

``
ssh level00@127.0.0.1 -p 2222
``

---

# First Level Login

To login to the first level, use the following credentials:

Username: level00
Password: level00

---
