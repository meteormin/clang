## Multi task simulator

## build and run
```sh
$ mkdir -p build
$ cd build
$ cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
$ make
$ ./mt-scheduler.out
```

### Usage
```sh
Enter time slice for Round Robin scheduling: 4
Enter the number of processes to simulate: 3

Enter details for Process 1
PID: 1
Priority: 1
Burst Time: 10
Arrival Time: 0

Enter details for Process 2
PID: 2
Priority: 2
Burst Time: 8
Arrival Time: 1

Enter details for Process 3
PID: 3
Priority: 3
Burst Time: 6
Arrival Time: 2

Starting Round Robin Scheduling Simulation...

Process 1 is running for 4 units
Process 2 is running for 4 units
Process 3 is running for 4 units
Process 1 is running for 4 units
Process 2 is running for 4 units and finished
Process 3 is running for 2 units and finished
Process 1 is running for 2 units and finished
```
