Submitter name: Aman Palariya
Roll No: 2019CSB1068
Course: CS303

# What does the program do?

It simulates resource requests from threads and checks for detection and preempts the threads based on some heuristics.


# How does this program work?

The user inputs a set of resources and number of threads.
The simulator simulates working of threads.
The threads request for random resources or sleep for some time. 
Another thread detects deadlock at given intervals.
If a deadlock is detected, the program preempts that thread and frees the resources.
At the end, it prints the number of deadlocks detected and the average deadlock occurrence time.

# How to compile and run?

1. Unzip the source code.
2. Inside the directory, run `make` to build the project.
3. Run the program by executing `./build/main.out`
4. Enter number of resources n, number of threads m, deadlock detection interval in milliseconds d, and heuristic number h (space separated)
5. Then enter n numbers (space separated), ith of which denotes the number of instances of resource i
6. To finish the program, close the stdin (by pressing Ctrl+D)

## Heuristic number

0: Max allocation (i.e. the thread whose Σ(allocated resources) is maximum)
1: Min allocation (i.e. the thread whose Σ(allocated resources) is minimum)
2: Max max allocation (i.e. the thread whose max(allocated resources) is maximum)
3: Min min allocation (i.e. the thread whose min(allocated resources) is minimum)
4: Max distinct allocation (i.e. the thread whose count(distinct allocated resources) is maximum)
5: Min distinct allocation (i.e. the thread whose count(distinct allocated resources) is minimum)

## Testing

1. Run `make test` to run tests

# Snapshot

After doing the following steps

1. Compile the project by running `make`
2. Start the simulation by executing `{ printf "3 4 1000 0\n4 4 4\n"; cat; } | ./build/main.out`.
   This starts the simulation with 3 resource (4 instances of each), 4 threads, max total allocation preemption heuristic, and 1000 ms deadlock detection interval
3. Press Ctrl+D when you want to finish execution 

A possible output can be the following
---
Starting simulation with following configuration
Resources: 3 [4, 4, 4]
Number of threads: 4
Deadlock detection interval: 1000ms
Preemption heuristic: Max total allocation

INFO  08:45:16: [0] Deciding requirement
INFO  08:45:16: [0] Printing requirement
INFO  08:45:16: [1] Deciding requirement
INFO  08:45:16: [3] Deciding requirement
INFO  08:45:16: [0] Res [0] = 0
INFO  08:45:16: [0] Res [1] = 0
INFO  08:45:16: [2] Deciding requirement
INFO  08:45:16: [0] Res [2] = 0
INFO  08:45:16: [0] Freeing all resources
INFO  08:45:16: [0] Sleeping for 1065.65
INFO  08:45:16: [1] Printing requirement
INFO  08:45:16: [1] Res [0] = 0
INFO  08:45:16: [1] Res [1] = 0
INFO  08:45:16: [1] Res [2] = 2
INFO  08:45:16: [3] Printing requirement
INFO  08:45:16: [3] Res [0] = 0
INFO  08:45:16: [3] Res [1] = 0
INFO  08:45:16: [3] Res [2] = 4
INFO  08:45:16: [3] Sleeping for 169.32
INFO  08:45:16: [2] Printing requirement
INFO  08:45:16: [1] Request of res 2 x 2, currently have 4
INFO  08:45:16: [2] Res [0] = 3
INFO  08:45:16: [2] Res [1] = 3
INFO  08:45:16: [2] Res [2] = 1
INFO  08:45:16: [2] Request of res 2 x 1, currently have 4
INFO  08:45:16: [1] Freeing all resources
INFO  08:45:16: [2] Request of res 0 x 1, currently have 4
INFO  08:45:16: [1] Sleeping for 865.32
INFO  08:45:16: [2] Sleeping for 214.13
INFO  08:45:17: [3] Request of res 2 x 1, currently have 3
INFO  08:45:17: [3] Sleeping for 472.71
INFO  08:45:17: [2] Request of res 0 x 2, currently have 3
INFO  08:45:17: [2] Request of res 1 x 3, currently have 4
INFO  08:45:17: [2] Freeing all resources
INFO  08:45:17: [2] Sleeping for 1304.13
INFO  08:45:17: [3] Request of res 2 x 3, currently have 3
INFO  08:45:17: [3] Freeing all resources
INFO  08:45:17: [3] Sleeping for 921.61
INFO  08:45:17: [1] Deciding requirement
INFO  08:45:17: [1] Printing requirement
INFO  08:45:17: [1] Res [0] = 0
INFO  08:45:17: [1] Res [1] = 2
INFO  08:45:17: [1] Res [2] = 0
INFO  08:45:17: [1] Sleeping for 969.81
INFO  08:45:17: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Available
4 4 4 
INFO  08:45:17: NO DEADLOCK
INFO  08:45:18: [0] Deciding requirement
INFO  08:45:18: [0] Printing requirement
INFO  08:45:18: [0] Res [0] = 0
INFO  08:45:18: [0] Res [1] = 0
INFO  08:45:18: [0] Res [2] = 0
INFO  08:45:18: [0] Freeing all resources
INFO  08:45:18: [0] Sleeping for 1278.33
INFO  08:45:18: [2] Deciding requirement
INFO  08:45:18: [2] Printing requirement
INFO  08:45:18: [2] Res [0] = 2
INFO  08:45:18: [2] Res [1] = 2
INFO  08:45:18: [2] Res [2] = 0
INFO  08:45:18: [2] Sleeping for 147.46
INFO  08:45:18: [3] Deciding requirement
INFO  08:45:18: [3] Printing requirement
INFO  08:45:18: [3] Res [0] = 2
INFO  08:45:18: [3] Res [1] = 1
INFO  08:45:18: [3] Res [2] = 3
INFO  08:45:18: [3] Sleeping for 807.59
INFO  08:45:18: [2] Sleeping for 357.39
INFO  08:45:18: [1] Request of res 1 x 1, currently have 4
INFO  08:45:18: [1] Request of res 1 x 1, currently have 3
INFO  08:45:18: [1] Freeing all resources
INFO  08:45:18: [1] Sleeping for 1061.69
INFO  08:45:18: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Available
4 4 4 
INFO  08:45:18: NO DEADLOCK
INFO  08:45:18: [2] Request of res 0 x 2, currently have 4
INFO  08:45:18: [2] Sleeping for 787.33
INFO  08:45:19: [0] Deciding requirement
INFO  08:45:19: [0] Printing requirement
INFO  08:45:19: [0] Res [0] = 0
INFO  08:45:19: [0] Res [1] = 0
INFO  08:45:19: [0] Res [2] = 0
INFO  08:45:19: [0] Freeing all resources
INFO  08:45:19: [0] Sleeping for 1485.40
INFO  08:45:19: [3] Request of res 1 x 1, currently have 4
INFO  08:45:19: [3] Request of res 2 x 3, currently have 4
INFO  08:45:19: [3] Sleeping for 316.75
INFO  08:45:19: [3] Request of res 0 x 2, currently have 2
INFO  08:45:19: [3] Freeing all resources
INFO  08:45:19: [3] Sleeping for 1042.36
INFO  08:45:19: [2] Sleeping for 769.85
INFO  08:45:19: [1] Deciding requirement
INFO  08:45:19: [1] Printing requirement
INFO  08:45:19: [1] Res [0] = 4
INFO  08:45:19: [1] Res [1] = 4
INFO  08:45:19: [1] Res [2] = 2
INFO  08:45:19: [1] Request of res 1 x 2, currently have 4
INFO  08:45:19: [1] Request of res 0 x 4, currently have 2
INFO  08:45:19: DETECTING DEADLOCK...
Request
0 0 0 
4 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 2 0 
2 0 0 
0 0 0 
Available
2 2 4 
INFO  08:45:19: NO DEADLOCK
INFO  08:45:20: [2] Request of res 1 x 2, currently have 2
INFO  08:45:20: [2] Freeing all resources
INFO  08:45:20: [2] Sleeping for 1401.69
INFO  08:45:20: [1] Request of res 1 x 2, currently have 2
INFO  08:45:20: [1] Request of res 2 x 2, currently have 4
INFO  08:45:20: [1] Freeing all resources
INFO  08:45:20: [1] Sleeping for 1113.24
INFO  08:45:20: [3] Deciding requirement
INFO  08:45:20: [3] Printing requirement
INFO  08:45:20: [3] Res [0] = 3
INFO  08:45:20: [3] Res [1] = 0
INFO  08:45:20: [3] Res [2] = 0
INFO  08:45:20: [3] Request of res 0 x 3, currently have 4
INFO  08:45:20: [3] Freeing all resources
INFO  08:45:20: [3] Sleeping for 778.11
INFO  08:45:20: [0] Deciding requirement
INFO  08:45:20: [0] Printing requirement
INFO  08:45:20: [0] Res [0] = 0
INFO  08:45:20: [0] Res [1] = 4
INFO  08:45:20: [0] Res [2] = 1
INFO  08:45:20: [0] Request of res 1 x 4, currently have 4
INFO  08:45:20: [0] Request of res 2 x 1, currently have 4
INFO  08:45:20: [0] Freeing all resources
INFO  08:45:20: [0] Sleeping for 842.85
INFO  08:45:20: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Available
4 4 4 
INFO  08:45:20: NO DEADLOCK
INFO  08:45:21: [3] Deciding requirement
INFO  08:45:21: [3] Printing requirement
INFO  08:45:21: [3] Res [0] = 0
INFO  08:45:21: [3] Res [1] = 0
INFO  08:45:21: [3] Res [2] = 0
INFO  08:45:21: [3] Freeing all resources
INFO  08:45:21: [3] Sleeping for 1355.47
INFO  08:45:21: [0] Deciding requirement
INFO  08:45:21: [0] Printing requirement
INFO  08:45:21: [0] Res [0] = 2
INFO  08:45:21: [0] Res [1] = 3
INFO  08:45:21: [0] Res [2] = 0
INFO  08:45:21: [0] Request of res 0 x 2, currently have 4
INFO  08:45:21: [0] Request of res 1 x 2, currently have 4
INFO  08:45:21: [0] Request of res 1 x 1, currently have 2
INFO  08:45:21: [0] Freeing all resources
INFO  08:45:21: [0] Sleeping for 1279.34
INFO  08:45:21: [1] Deciding requirement
INFO  08:45:21: [1] Printing requirement
INFO  08:45:21: [1] Res [0] = 0
INFO  08:45:21: [1] Res [1] = 2
INFO  08:45:21: [1] Res [2] = 0
INFO  08:45:21: [1] Sleeping for 692.29
INFO  08:45:21: [2] Deciding requirement
INFO  08:45:21: [2] Printing requirement
INFO  08:45:21: [2] Res [0] = 0
INFO  08:45:21: [2] Res [1] = 0
INFO  08:45:21: [2] Res [2] = 1
INFO  08:45:21: [2] Sleeping for 96.35
INFO  08:45:21: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Available
4 4 4 
INFO  08:45:21: NO DEADLOCK
INFO  08:45:22: [2] Request of res 2 x 1, currently have 4
INFO  08:45:22: [2] Freeing all resources
INFO  08:45:22: [2] Sleeping for 789.41
INFO  08:45:22: [1] Request of res 1 x 1, currently have 4
INFO  08:45:22: [1] Sleeping for 32.10
INFO  08:45:22: [1] Request of res 1 x 1, currently have 3
INFO  08:45:22: [1] Freeing all resources
INFO  08:45:22: [1] Sleeping for 1161.10
INFO  08:45:22: [3] Deciding requirement
INFO  08:45:22: [3] Printing requirement
INFO  08:45:22: [3] Res [0] = 4
INFO  08:45:22: [3] Res [1] = 0
INFO  08:45:22: [3] Res [2] = 0
INFO  08:45:22: [3] Request of res 0 x 1, currently have 4
INFO  08:45:22: [3] Request of res 0 x 3, currently have 3
INFO  08:45:22: [3] Freeing all resources
INFO  08:45:22: [3] Sleeping for 1170.96
INFO  08:45:22: [2] Deciding requirement
INFO  08:45:22: [2] Printing requirement
INFO  08:45:22: [2] Res [0] = 0
INFO  08:45:22: [2] Res [1] = 1
INFO  08:45:22: [2] Res [2] = 0
INFO  08:45:22: [2] Request of res 1 x 1, currently have 4
INFO  08:45:22: [2] Freeing all resources
INFO  08:45:22: [2] Sleeping for 1496.47
INFO  08:45:22: [0] Deciding requirement
INFO  08:45:22: [0] Printing requirement
INFO  08:45:22: [0] Res [0] = 1
INFO  08:45:22: [0] Res [1] = 4
INFO  08:45:22: [0] Res [2] = 0
INFO  08:45:22: [0] Request of res 1 x 3, currently have 4
INFO  08:45:22: [0] Request of res 1 x 1, currently have 1
INFO  08:45:22: [0] Request of res 0 x 1, currently have 4
INFO  08:45:22: [0] Freeing all resources
INFO  08:45:22: [0] Sleeping for 1321.91
INFO  08:45:22: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Available
4 4 4 
INFO  08:45:22: NO DEADLOCK
INFO  08:45:23: [1] Deciding requirement
INFO  08:45:23: [1] Printing requirement
INFO  08:45:23: [1] Res [0] = 0
INFO  08:45:23: [1] Res [1] = 0
INFO  08:45:23: [1] Res [2] = 0
INFO  08:45:23: [1] Freeing all resources
INFO  08:45:23: [1] Sleeping for 846.82
INFO  08:45:23: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Available
4 4 4 
INFO  08:45:23: NO DEADLOCK
INFO  08:45:23: [3] Deciding requirement
INFO  08:45:23: [3] Printing requirement
INFO  08:45:23: [3] Res [0] = 4
INFO  08:45:23: [3] Res [1] = 0
INFO  08:45:23: [3] Res [2] = 2
INFO  08:45:23: [3] Request of res 0 x 3, currently have 4
INFO  08:45:23: [3] Request of res 2 x 2, currently have 4
INFO  08:45:24: [3] Request of res 0 x 1, currently have 1
INFO  08:45:24: [3] Freeing all resources
INFO  08:45:24: [3] Sleeping for 1365.04
INFO  08:45:24: [0] Deciding requirement
INFO  08:45:24: [0] Printing requirement
INFO  08:45:24: [0] Res [0] = 0
INFO  08:45:24: [0] Res [1] = 3
INFO  08:45:24: [0] Res [2] = 0
INFO  08:45:24: [0] Request of res 1 x 2, currently have 4
INFO  08:45:24: [0] Sleeping for 819.77
INFO  08:45:24: [2] Deciding requirement
INFO  08:45:24: [2] Printing requirement
INFO  08:45:24: [2] Res [0] = 0
INFO  08:45:24: [2] Res [1] = 3
INFO  08:45:24: [2] Res [2] = 0
INFO  08:45:24: [2] Request of res 1 x 2, currently have 2
INFO  08:45:24: [2] Sleeping for 319.73
INFO  08:45:24: [1] Deciding requirement
INFO  08:45:24: [1] Printing requirement
INFO  08:45:24: [1] Res [0] = 1
INFO  08:45:24: [1] Res [1] = 0
INFO  08:45:24: [1] Res [2] = 0
INFO  08:45:24: [1] Sleeping for 21.42
INFO  08:45:24: [1] Request of res 0 x 1, currently have 4
INFO  08:45:24: [1] Freeing all resources
INFO  08:45:24: [1] Sleeping for 805.89
INFO  08:45:24: [2] Request of res 1 x 1, currently have 0
INFO  08:45:24: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 1 0 
0 0 0 
Allocation
0 2 0 
0 0 0 
0 2 0 
0 0 0 
Available
4 0 4 
INFO  08:45:24: NO DEADLOCK
INFO  08:45:25: [0] Request of res 1 x 1, currently have 0
INFO  08:45:25: [1] Deciding requirement
INFO  08:45:25: [1] Printing requirement
INFO  08:45:25: [1] Res [0] = 0
INFO  08:45:25: [1] Res [1] = 0
INFO  08:45:25: [1] Res [2] = 4
INFO  08:45:25: [1] Sleeping for 76.78
INFO  08:45:25: [1] Request of res 2 x 4, currently have 4
INFO  08:45:25: [1] Freeing all resources
INFO  08:45:25: [1] Sleeping for 720.68
INFO  08:45:25: [3] Deciding requirement
INFO  08:45:25: [3] Printing requirement
INFO  08:45:25: [3] Res [0] = 0
INFO  08:45:25: [3] Res [1] = 0
INFO  08:45:25: [3] Res [2] = 0
INFO  08:45:25: [3] Freeing all resources
INFO  08:45:25: [3] Sleeping for 1094.28
INFO  08:45:25: DETECTING DEADLOCK...
Request
0 1 0 
0 0 0 
0 1 0 
0 0 0 
Allocation
0 2 0 
0 0 0 
0 2 0 
0 0 0 
Available
4 0 4 
INFO  08:45:25: DEADLOCK PRESENT
0 2 
INFO  08:45:25: Preempting thread 0
INFO  08:45:25: [0] Freeing all resources
INFO  08:45:25: [0] Sleeping for 963.32
INFO  08:45:25: [2] Freeing all resources
INFO  08:45:25: [2] Sleeping for 728.40
INFO  08:45:26: [1] Deciding requirement
INFO  08:45:26: [1] Printing requirement
INFO  08:45:26: [1] Res [0] = 0
INFO  08:45:26: [1] Res [1] = 0
INFO  08:45:26: [1] Res [2] = 0
INFO  08:45:26: [1] Freeing all resources
INFO  08:45:26: [1] Sleeping for 1191.24
INFO  08:45:26: [3] Deciding requirement
INFO  08:45:26: [3] Printing requirement
INFO  08:45:26: [3] Res [0] = 3
INFO  08:45:26: [3] Res [1] = 0
INFO  08:45:26: [3] Res [2] = 3
INFO  08:45:26: [3] Sleeping for 451.96
INFO  08:45:26: [2] Deciding requirement
INFO  08:45:26: [2] Printing requirement
INFO  08:45:26: [2] Res [0] = 2
INFO  08:45:26: [2] Res [1] = 0
INFO  08:45:26: [2] Res [2] = 2
INFO  08:45:26: [2] Request of res 0 x 2, currently have 4
INFO  08:45:26: [2] Request of res 2 x 2, currently have 4
INFO  08:45:26: [2] Freeing all resources
INFO  08:45:26: [2] Sleeping for 800.95
INFO  08:45:26: [3] Request of res 2 x 1, currently have 4
INFO  08:45:26: [3] Sleeping for 253.15
INFO  08:45:26: [0] Deciding requirement
INFO  08:45:26: [0] Printing requirement
INFO  08:45:26: [0] Res [0] = 0
INFO  08:45:26: [0] Res [1] = 1
INFO  08:45:26: [0] Res [2] = 0
INFO  08:45:26: [0] Request of res 1 x 1, currently have 4
INFO  08:45:26: [0] Freeing all resources
INFO  08:45:26: [0] Sleeping for 1418.97
INFO  08:45:26: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 0 0 
0 0 0 
0 0 1 
Available
4 4 3 
INFO  08:45:26: NO DEADLOCK
INFO  08:45:27: [3] Sleeping for 71.36
INFO  08:45:27: [1] Deciding requirement
INFO  08:45:27: [1] Printing requirement
INFO  08:45:27: [1] Res [0] = 0
INFO  08:45:27: [1] Res [1] = 1
INFO  08:45:27: [1] Res [2] = 4
INFO  08:45:27: [1] Request of res 1 x 1, currently have 4
INFO  08:45:27: [1] Sleeping for 801.07
INFO  08:45:27: [3] Request of res 0 x 3, currently have 4
INFO  08:45:27: [3] Sleeping for 203.60
INFO  08:45:27: [3] Request of res 2 x 2, currently have 3
INFO  08:45:27: [3] Freeing all resources
INFO  08:45:27: [3] Sleeping for 782.69
INFO  08:45:27: [2] Deciding requirement
INFO  08:45:27: [2] Printing requirement
INFO  08:45:27: [2] Res [0] = 0
INFO  08:45:27: [2] Res [1] = 0
INFO  08:45:27: [2] Res [2] = 0
INFO  08:45:27: [2] Freeing all resources
INFO  08:45:27: [2] Sleeping for 950.70
INFO  08:45:27: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 1 0 
0 0 0 
0 0 0 
Available
4 3 4 
INFO  08:45:27: NO DEADLOCK
INFO  08:45:28: [1] Request of res 2 x 4, currently have 4
INFO  08:45:28: [1] Freeing all resources
INFO  08:45:28: [1] Sleeping for 1331.52
INFO  08:45:28: [3] Deciding requirement
INFO  08:45:28: [3] Printing requirement
INFO  08:45:28: [3] Res [0] = 2
INFO  08:45:28: [3] Res [1] = 0
INFO  08:45:28: [3] Res [2] = 0
INFO  08:45:28: [3] Request of res 0 x 2, currently have 4
INFO  08:45:28: [3] Freeing all resources
INFO  08:45:28: [3] Sleeping for 728.38
INFO  08:45:28: [0] Deciding requirement
INFO  08:45:28: [0] Printing requirement
INFO  08:45:28: [0] Res [0] = 2
INFO  08:45:28: [0] Res [1] = 0
INFO  08:45:28: [0] Res [2] = 2
INFO  08:45:28: [0] Request of res 0 x 1, currently have 4
INFO  08:45:28: [0] Sleeping for 890.76
INFO  08:45:28: [2] Deciding requirement
INFO  08:45:28: [2] Printing requirement
INFO  08:45:28: [2] Res [0] = 0
INFO  08:45:28: [2] Res [1] = 1
INFO  08:45:28: [2] Res [2] = 0
INFO  08:45:28: [2] Sleeping for 231.08
INFO  08:45:28: [2] Sleeping for 664.28
INFO  08:45:28: [3] Deciding requirement
INFO  08:45:28: [3] Printing requirement
INFO  08:45:28: [3] Res [0] = 0
INFO  08:45:28: [3] Res [1] = 3
INFO  08:45:28: [3] Res [2] = 0
INFO  08:45:28: [3] Request of res 1 x 2, currently have 4
INFO  08:45:28: [3] Sleeping for 116.51
INFO  08:45:28: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
1 0 0 
0 0 0 
0 0 0 
0 2 0 
Available
3 2 4 
INFO  08:45:28: NO DEADLOCK
INFO  08:45:29: [3] Sleeping for 418.55
INFO  08:45:29: [0] Request of res 2 x 2, currently have 4
INFO  08:45:29: [0] Sleeping for 486.13
INFO  08:45:29: [2] Request of res 1 x 1, currently have 2
INFO  08:45:29: [2] Freeing all resources
INFO  08:45:29: [2] Sleeping for 1461.73
INFO  08:45:29: [1] Deciding requirement
INFO  08:45:29: [1] Printing requirement
INFO  08:45:29: [1] Res [0] = 4
INFO  08:45:29: [1] Res [1] = 0
INFO  08:45:29: [1] Res [2] = 0
INFO  08:45:29: [1] Request of res 0 x 4, currently have 3
INFO  08:45:29: [3] Sleeping for 556.66
INFO  08:45:29: [0] Request of res 0 x 1, currently have 3
INFO  08:45:29: [0] Freeing all resources
INFO  08:45:29: [0] Sleeping for 1436.39
INFO  08:45:29: [1] Freeing all resources
INFO  08:45:29: [1] Sleeping for 1260.51
INFO  08:45:29: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 0 0 
0 0 0 
0 2 0 
Available
4 2 4 
INFO  08:45:29: NO DEADLOCK
INFO  08:45:30: [3] Request of res 1 x 1, currently have 2
INFO  08:45:30: [3] Freeing all resources
INFO  08:45:30: [3] Sleeping for 966.95
INFO  08:45:30: [2] Deciding requirement
INFO  08:45:30: [2] Printing requirement
INFO  08:45:30: [2] Res [0] = 1
INFO  08:45:30: [2] Res [1] = 0
INFO  08:45:30: [2] Res [2] = 0
INFO  08:45:30: [2] Request of res 0 x 1, currently have 4
INFO  08:45:30: [2] Freeing all resources
INFO  08:45:30: [2] Sleeping for 1215.44
INFO  08:45:30: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Available
4 4 4 
INFO  08:45:30: NO DEADLOCK
INFO  08:45:30: [1] Deciding requirement
INFO  08:45:30: [1] Printing requirement
INFO  08:45:30: [1] Res [0] = 0
INFO  08:45:30: [1] Res [1] = 0
INFO  08:45:30: [1] Res [2] = 1
INFO  08:45:30: [1] Request of res 2 x 1, currently have 4
INFO  08:45:30: [1] Freeing all resources
INFO  08:45:30: [1] Sleeping for 821.25
INFO  08:45:31: [3] Deciding requirement
INFO  08:45:31: [3] Printing requirement
INFO  08:45:31: [3] Res [0] = 0
INFO  08:45:31: [3] Res [1] = 0
INFO  08:45:31: [3] Res [2] = 3
INFO  08:45:31: [3] Request of res 2 x 3, currently have 4
INFO  08:45:31: [3] Freeing all resources
INFO  08:45:31: [3] Sleeping for 1097.34
INFO  08:45:31: [0] Deciding requirement
INFO  08:45:31: [0] Printing requirement
INFO  08:45:31: [0] Res [0] = 1
INFO  08:45:31: [0] Res [1] = 0
INFO  08:45:31: [0] Res [2] = 0
INFO  08:45:31: [0] Request of res 0 x 1, currently have 4
INFO  08:45:31: [0] Freeing all resources
INFO  08:45:31: [0] Sleeping for 1458.64
INFO  08:45:31: [1] Deciding requirement
INFO  08:45:31: [1] Printing requirement
INFO  08:45:31: [1] Res [0] = 0
INFO  08:45:31: [1] Res [1] = 0
INFO  08:45:31: [1] Res [2] = 1
INFO  08:45:31: [1] Request of res 2 x 1, currently have 4
INFO  08:45:31: [1] Freeing all resources
INFO  08:45:31: [1] Sleeping for 1140.91
INFO  08:45:31: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Available
4 4 4 
INFO  08:45:31: NO DEADLOCK
INFO  08:45:32: [2] Deciding requirement
INFO  08:45:32: [2] Printing requirement
INFO  08:45:32: [2] Res [0] = 4
INFO  08:45:32: [2] Res [1] = 0
INFO  08:45:32: [2] Res [2] = 0
INFO  08:45:32: [2] Sleeping for 462.98
INFO  08:45:32: [3] Deciding requirement
INFO  08:45:32: [3] Printing requirement
INFO  08:45:32: [3] Res [0] = 0
INFO  08:45:32: [3] Res [1] = 4
INFO  08:45:32: [3] Res [2] = 0
INFO  08:45:32: [3] Request of res 1 x 4, currently have 4
INFO  08:45:32: [3] Freeing all resources
INFO  08:45:32: [3] Sleeping for 766.96
INFO  08:45:32: [2] Request of res 0 x 2, currently have 4
INFO  08:45:32: [2] Request of res 0 x 1, currently have 2
INFO  08:45:32: [2] Request of res 0 x 1, currently have 1
INFO  08:45:32: [2] Freeing all resources
INFO  08:45:32: [2] Sleeping for 1378.43
INFO  08:45:32: [0] Deciding requirement
INFO  08:45:32: [0] Printing requirement
INFO  08:45:32: [0] Res [0] = 0
INFO  08:45:32: [0] Res [1] = 0
INFO  08:45:32: [0] Res [2] = 0
INFO  08:45:32: [0] Freeing all resources
INFO  08:45:32: [0] Sleeping for 929.66
INFO  08:45:32: [3] Deciding requirement
INFO  08:45:32: [3] Printing requirement
INFO  08:45:32: [3] Res [0] = 2
INFO  08:45:32: [3] Res [1] = 2
INFO  08:45:32: [3] Res [2] = 0
INFO  08:45:32: [3] Request of res 0 x 2, currently have 4
INFO  08:45:32: [3] Request of res 1 x 2, currently have 4
INFO  08:45:32: [3] Freeing all resources
INFO  08:45:32: [3] Sleeping for 1245.62
INFO  08:45:32: [1] Deciding requirement
INFO  08:45:32: [1] Printing requirement
INFO  08:45:32: [1] Res [0] = 0
INFO  08:45:32: [1] Res [1] = 0
INFO  08:45:32: [1] Res [2] = 4
INFO  08:45:32: [1] Sleeping for 424.88
INFO  08:45:32: DETECTING DEADLOCK...
Request
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Allocation
0 0 0 
0 0 0 
0 0 0 
0 0 0 
Available
4 4 4 
INFO  08:45:32: NO DEADLOCK


Detected deadlocks 1 times
Average deadlock interval: 9005.21 ms

---