# SnowCrash

## 🛑 WARNING 🛑

This repository contains the solutions for the SnowCrash project

Please proceed with caution as the following content will reveal the passwords

Before you take a peek at the solution - HOLD UP! Let me give you a word of wisdom: If you've been bashing your head against the problem for a couple hours (or days, or months - no judgement here, time is a human construct), **THEN and ONLY THEN** are you allowed a little peek 

Only seek help after you've exhausted all your options and remember the satisfaction you'll get from finding the solution yourself will far outweigh any temporary frustration or confusion you might experience along the way

So channel that inner Neo or better yet, Sherlock Holmes, and get back to the puzzle

 ~ *AD ASTRA PER ASPERA*


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
