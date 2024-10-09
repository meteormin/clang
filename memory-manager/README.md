## Memory Management simulator

각 셀이 숫자를 저장하는 간단한 스프레드시트 프로그램을 만들고, 사용자가 값을 입력하면 다른 셀에서 이를 참조하여 계산할 수 있도록 구현합니다. 예를 들어, B2 셀이 A1+B1 값을 가지도록 설정할 수 있습니다.

### Build and run

```sh
$ mkdir -p build
$ cd build
$ cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
$ make
$ ./memory-manager.out
```

### Usage
```sh
Memory Manager
1. Allocate Memory
2. Free Memory
3. Show Memory Status
4. Exit
```
