## Textbase Maze game.

## Build and run
```sh
$ mkdir -p build
$ cd build
$ cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
$ make
$ ./maze.out
```
## Usage

### Input
> [TODO] issue: 풀 수 없는 미로가 생성될 수 있습니다.
>> `q`를 눌러 현재 게임을 종료하고 다음 게임을 시작할 수 있습니다.

#### vim mode
- `h` : left
- `j` : down
- `k` : up
- `l` : right

#### WASD mode
- `a` : left
- `s` : down
- `w` : up
- `d` : right

#### Arrow mode
- `←` : left
- `↓` : down
- `↑` : up
- `→` : right

