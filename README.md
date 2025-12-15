# SnowCrash

## ☠️ 🚫  BEWARE, TARNISHED 🚫  ☠️

This repository contains my thought process + the solutions for the SnowCrash project


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

``bash
level00@127.0.0.1 -p 2222
``

---

# First Level Login

To login to the first level, use the following credentials:

Username: level00
Password: level00

---
