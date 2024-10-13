#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h> // 추가된 헤더
#include <unistd.h>

const char *mode_names[] = {"vim", "arrow", "wasd"};

// 방향키 ASCII 코드
const char arrow_keys[] = {'D', 'B', 'A', 'C'};
// WASD, VIM 모드의 키
const char wasd_keys[] = {'a', 's', 'w', 'd'};
const char vim_keys[] = {'h', 'j', 'k', 'l'};

// 터미널 설정
struct termios orig_termios;
void reset_terminal_mode() { tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios); }

void set_conio_terminal_mode() {
  struct termios new_termios;

  // 현재 터미널 속성 가져오기
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
    perror("tcgetattr");
    exit(EXIT_FAILURE);
  }

  // 종료 시 원래 터미널 모드로 복원
  atexit(reset_terminal_mode);

  new_termios = orig_termios;
  new_termios.c_lflag &= ~(ICANON | ECHO); // Canonical 모드 및 echo 비활성화

  // 새로운 터미널 속성 설정
  if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1) {
    perror("tcsetattr");
    exit(EXIT_FAILURE);
  }
}

// 키 입력
int getch() {
  int ch = getchar();
  if (ch == EOF) {
    return 0; // EOF가 발생한 경우 0을 반환
  }
  return ch;
}

// 미로 초기화
Container *init_maze(int w, int h, int mode) {
  Container *container = malloc(sizeof(Container));
  container->w = w;
  container->h = h;
  container->player = malloc(sizeof(Player));
  container->player->x = 1;
  container->player->y = 1;

  // 난수 초기화
  srand(time(NULL));

  container->maze = malloc(h * sizeof(int *));
  for (int i = 0; i < h; i++) {
    container->maze[i] = malloc(w * sizeof(int));
    for (int j = 0; j < w; j++) {
      // 미로 외곽에 벽 생성
      if (i == 0 || i == h - 1 || j == 0 || j == w - 1) {
        container->maze[i][j] = 1;
      } else {
        // 내부는 20% 확률로 벽을 생성하고, 나머지는 빈 공간
        container->maze[i][j] = (rand() % 5 == 0) ? 1 : 0;
      }
    }
  }
  container->maze[h - 2][w - 2] = 2; // 출구

  return container;
}

// 미로 메모리 해제
void free_maze(Container *container) {
  for (int i = 0; i < MAX_HEIGHT; i++) {
    free(container->maze[i]);
  }
  free(container->maze);
  free(container->player);
  free(container);
}

// 미로 출력
void print_maze(Container *container) {

  printf("\n");
  for (int i = 0; i < container->h; i++) {
    for (int j = 0; j < container->w; j++) {
      if (container->player->y == i && container->player->x == j) {
        printf("P ");
      } else if (container->maze[i][j] == 1) {
        printf("# ");
      } else if (container->maze[i][j] == 2) {
        printf("E ");
      } else {
        printf(". ");
      }
    }
    printf("\n");
  }
}

// 플레이어 이동
void move_player(Container *container, int direction) {
  int new_x = container->player->x;
  int new_y = container->player->y;

  switch (direction) {
  case LEFT:
    new_x -= 1;
    break;
  case DOWN:
    new_y += 1;
    break;
  case UP:
    new_y -= 1;
    break;
  case RIGHT:
    new_x += 1;
    break;
  }

  if (container->maze[new_y][new_x] != 1) { // 벽이 아닐 때 이동
    container->player->x = new_x;
    container->player->y = new_y;
  }
}

// 키 입력 방향 변환
int get_direction(char input, int mode) {
  // 모드에 따라 입력된 키와 방향을 매핑
  switch (mode) {
  case VIM_MODE:
    for (int i = 0; i < 4; i++) {
      if (input == vim_keys[i]) {
        return i;
      }
    }
    break;

  case WASD_MODE:
    for (int i = 0; i < 4; i++) {
      if (input == wasd_keys[i]) {
        return i;
      }
    }
    break;

  case ARROW_MODE:
    // 방향키 입력을 처리하는 부분
    if (input == 27) {       // ESC (이모지의 시작)
      int next = getch();    // 다음 문자를 읽어옵니다.
      if (next == 91) {      // '[' 문자의 ASCII 코드
        int arrow = getch(); // 방향키에 해당하는 문자를 읽어옵니다.
        for (int i = 0; i < 4; i++) {
          if (arrow == arrow_keys[i]) {
            return i;
          }
        }
      }
    }
    break;

  default:
    break;
  }

  return -1; // 유효하지 않은 입력
}

// 메인 게임 루프
void start_game(Container *container, int mode) {

  while (getchar() != '\n')
    ;
  while (1) {
    print_maze(container);
    printf("Enter move (Mode: %s): ", mode_names[mode]);

    int key = getch();
    printf("input key: %d\n", key);

    if (key == 'q') {
      printf("Quit this game.\n");
      break;
    }

    int direction = get_direction(key, mode);

    printf("direction: %d\n", direction);

    // 플레이어 또는 방향키를 입력
    if (direction != -1) {
      move_player(container, direction);
      if (container->maze[container->player->y][container->player->x] == 2) {
        printf("Congratulations! You escaped the maze!\n");
        break;
      }
    }
  }
}
