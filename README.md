# SnowCrash




you can login to the VM in two different ways:


### - First method bridge networking

on local machine: virtualbox -> Network -> attached to -> Bridged adapter

on VM: ifconfig,find IP and use it like this with -p 4242

#### ssh -p 4242 level00@192.xxx.x.xx

---

### - Second method port forwarding

on local machine: virtualbox -> Network -> attached to : NAT -> Port Forwarding

#### 127.0.0.1 | 4242 | 10.0.2.15 | 4242 

---
### first level

login:level00
password:level00