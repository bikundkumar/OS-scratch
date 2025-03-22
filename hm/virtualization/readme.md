This program, called `process-run.py`, allows you to see how the state of a process changes as it runs on a CPU. As described in the chapter, processes can be in a few different states:

- **RUNNING** - The process is using the CPU right now.
- **READY** - The process could be using the CPU right now, but (alas) some other process is.
- **BLOCKED** - The process is waiting on I/O (e.g., it issued a request to a disk).
- **DONE** - The process is finished executing.

## 1. Running with `-l 5:100,5:100`

### Expected CPU Utilization
With two processes, each having 5 CPU instructions, the CPU should be fully utilized. The expected CPU utilization is **100%**.

### Verification
Use the following command to verify:
```bash
python process-run.py -l 5:100,5:100 -c -p
```

## 2. Running with `-l 4:100,1:0`

This specifies:
- One process with 4 CPU instructions
- One process that only issues an I/O and waits

### Expected Completion Time
- The CPU process runs for **4 time units**.
- The I/O process issues an I/O and waits.
- If the CPU process completes first, the I/O process will continue after.

### Verification
```bash
python process-run.py -l 4:100,1:0 -c -p
```

## 3. Switching Process Order: `-l 1:0,4:100`

### Expected Behavior
- The first process issues an I/O and waits.
- The second process executes all its CPU instructions while the first process waits.
- The order of execution matters since the first process starts with I/O, which can delay execution.

### Verification
```bash
python process-run.py -l 1:0,4:100 -c -p
```

## 4. Using `-S SWITCH ON END`

### Expected Behavior
- The system does not switch to another process when one is doing I/O.
- It waits until the I/O process is completely finished before continuing.

### Verification
```bash
python process-run.py -l 1:0,4:100 -c -S SWITCH ON END
```

## 5. Using `-S SWITCH ON IO`

### Expected Behavior
- The system switches to another process while one is waiting for I/O.
- This allows better CPU utilization.

### Verification
```bash
python process-run.py -l 1:0,4:100 -c -S SWITCH ON IO
```

## 6. Using `-I IO RUN LATER`

### Expected Behavior
- When an I/O completes, the process that issued it is not run immediately.
- The currently running process continues until it voluntarily gives up the CPU.
- This may lead to inefficient CPU utilization.

### Verification
```bash
python process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH ON IO -c -p -I IO RUN LATER
```

## 7. Using `-I IO RUN IMMEDIATE`

### Expected Behavior
- When an I/O completes, the process that issued it runs immediately.
- This improves responsiveness and resource utilization.

### Verification
```bash
python process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH ON IO -c -p -I IO RUN IMMEDIATE
```

## 8. Running with Randomly Generated Processes

Use the following commands:
```bash
python process-run.py -s 1 -l 3:50,3:50
python process-run.py -s 2 -l 3:50,3:50
python process-run.py -s 3 -l 3:50,3:50
```

### Observations
- Using `-I IO RUN IMMEDIATE` vs. `-I IO RUN LATER` affects when an I/O process resumes.
- Using `-S SWITCH ON IO` vs. `-S SWITCH ON END` affects CPU utilization.

By analyzing the traces, we can better understand process scheduling and CPU efficiency.

