## Spreadsheet CLI

각 셀이 숫자를 저장하는 간단한 스프레드시트 프로그램을 만들고, 사용자가 값을 입력하면 다른 셀에서 이를 참조하여 계산할 수 있도록 구현합니다. 예를 들어, B2 셀이 A1+B1 값을 가지도록 설정할 수 있습니다.

## Build and run
```sh
$ mkdir -p Build
$ cd Build
$ cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
$ make
$ ./spreadsheet-cli.out
```
## Usage
```sh
Command:
  set <row> <col> <value>         : 특정 셀에 값 입력 (예: 0 0 1)
  formula <row> <col> <formula>   : 특정 셀에 수식 입력 (예: =A0+B1)
  calc <row> <col>                : 특정 셀의 값 계산
  save <filename>                 : 스프레드시트 CSV로 저장
  load <filename>                 : CSV 파일에서 스프레드시트 불러오기
  print                           : 스프레드시트 출력
  help                            : 명령어 목록 출력
  exit                            : 프로그램 종료
```
