## Simple Database

데이터를 파일에 저장하고 검색할 수 있는 간단한 데이터베이스 시스템을 구축합니다. 데이터를 구조체로 관리하며, 파일에서 데이터를 읽고 쓰는 기능을 제공합니다. 예를 들어, 사용자가 이름과 나이를 입력하면 파일에 저장하고, 이후에 해당 데이터를 검색할 수 있습니다.

## Build and run
```sh
$ mkdir -p build
$ cd build
$ cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
$ make
$ ./simple-db.out
```

### Usage
- h: help.
- find: find data
  - find all: find all data
  - find %s %s: find key and value
- put: put data
  - put %s %s: put key and value
- rm: remove data
  - rm %d: remove by id
- q: quit.
