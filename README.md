# SnowCrash

## 🛑 WARNING 🛑

This repository contains the solutions for the SnowCrash project

Please proceed with caution as the following content will reveal the passwords

If you are currently working on this project i strongly recommend that you only check this solution if you have been stuck for hours and have exhausted all other resources

It's crucial to learn and grow from the challenges you face so give it your best shot before looking at the solution

 ~**AD ASTRA PER ASPERA**


---


you can login to the VM in two different ways:


### - First method bridge networking

on local machine: virtualbox -> Network -> attached to -> Bridged adapter

on VM: ifconfig,find IP and use it like this with -p 4242

#### ssh -p 4242 level00@192.xxx.x.xx




### - Second method port forwarding

on local machine: virtualbox -> Network -> attached to : NAT -> Port Forwarding

#### 127.0.0.1 | 4242 | 10.0.2.15 | 4242 

---

### first level

login:level00
password:level00
