#ifndef MAZE_H
#define MAZE_H

#define MAX_WIDTH 100
#define MAX_HEIGHT 100

#define LEFT 0
#define DOWN 1
#define UP 2
#define RIGHT 3

#define VIM_MODE 0
#define ARROW_MODE 1
#define WASD_MODE 2

extern const char *mode_names[];

// 방향키 ASCII 코드
extern const char arrow_keys[];
// WASD, VIM 모드의 키
extern const char wasd_keys[];
extern const char vim_keys[];

typedef struct {
  int x;
  int y;
} Player;

typedef struct {
  int w, h;
  int **maze;
  Player *player;
} Container;

Container *init_maze(int w, int h, int mode);

void move_player(Container *container, int direction);

void print_maze(Container *container);

void free_maze(Container *container);

void set_conio_terminal_mode();

void start_game(Container *container, int mode);

void reset_terminal_mode();

#endif
