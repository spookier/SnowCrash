# SnowCrash

## ☠️ 🚫  BEWARE, TARNISHED 🚫  ☠️

This repository contains my thought process + the solutions for the SnowCrash project

*Please proceed with caution, for the secrets whispered in this domain unveil the sacred passwords...*


## Before You Unravel the Enigma...

Wait! Before you take a peek at the solutions in this repository, consider this:

Let me give you a word of wisdom: If you've been bashing your head against the problem for a couple hours, **THEN and ONLY THEN** are you allowed a little peek 

Always seek help after you've exhausted all your options and remember the satisfaction you'll get from finding the solution yourself will far outweigh any temporary frustration or confusion you might experience along the way

*So champion, summon your inner spirit, akin to the undying flame and venture once more into the enigmatic labyrinth that awaits...*

---


# Snowcrash VM Login Guide

There are three different methods to log into the Snowcrash VM

>If the first two methods fail or if you're using a school PC, use the third method

## Method 1: Bridge Networking

Firstly, configure your local machine:

1. Go to VirtualBox
2. Navigate to Network
3. Set the network attachment to "Bridged adapter"

Then, on your VM, run the command `ifconfig` to get the IP. Use the IP in the following way:

```bash
ssh -p 4242 level00@VM_IP
```

## Method 2: Port Forwarding

Firstly, configure your local machine:

1. Go to VirtualBox
2. Navigate to Network
3. Set the network attachment to "NAT"
4. Set up Port Forwarding as follows:

```bash
SSH | TCP | 127.0.0.1 | 4242 | 10.0.2.15 | 4242 
```

## Method 3: Host-only Adapter (Alternative method)

If the above methods don't work, follow these steps:

1. Turn off VM if it's running
2. On your local machine, go to VirtualBox -> Network
3. Set the network attachment to "Host-only Adapter"
4. Start the VM
5. You should see an IP appearing now right on top of your input
6. Use that IP to connect to it as follows:

```bash
ssh level00@VM_IP -p 4242
```

---

# First Level Login

To login to the first level, use the following credentials:

Username: level00
Password: level00

---
