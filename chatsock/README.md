## Chatting with Socket Communication

여러 클라이언트가 동시에 접속하여 서로 메시지를 주고받을 수 있는 간단한 채팅 프로그램을 작성합니다. 서버는 각 클라이언트의 연결을 관리하고, 클라이언트가 보낸 메시지를 다른 클라이언트에게 중계합니다.

## Build and run
```sh
$ mkdir -p build
$ cd build
$ cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
$ make
$ ./server.out # run server on port 8080
$ ./client.out # run client
```
