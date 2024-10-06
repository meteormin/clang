## Simple Database

## build and run
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
