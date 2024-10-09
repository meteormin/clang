## Multi task simulator

여러 프로세스의 CPU 실행 순서를 관리하는 운영 체제의 스케줄링 알고리즘을 구현합니다. 라운드 로빈, 우선순위 기반 스케줄링 등의 알고리즘을 통해 각 프로세스의 실행 시간을 할당하고, 대기 큐에 프로세스를 관리합니다.

## Build and run
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
