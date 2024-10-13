#include "maze.h"
#include <stdio.h>

int main() {
  int width, height, mode;
  char retry;

  do {
    printf("Enter maze width (max %d): ", MAX_WIDTH);
    scanf("%d", &width);
    printf("Enter maze height (max %d): ", MAX_HEIGHT);
    scanf("%d", &height);

    if (width > MAX_WIDTH || height > MAX_HEIGHT || width <= 2 || height <= 2) {
      printf(
          "Invalid maze size. Width and height should be between 3 and %d.\n",
          MAX_WIDTH);
      return 1;
    }

    printf("Select control mode:\n");
    for (int i = 0; i < 3; i++) {
      printf("%d - %s\n", i, mode_names[i]);
    }
    printf("Enter mode (0 for vim, 1 for arrow, 2 for wasd): ");
    scanf("%d", &mode);

    if (mode < 0 || mode > 2) {
      printf("Invalid mode selection.\n");
      return 1;
    }

    // Initialize game
    printf("Initializing game...\n");
    Container *container = init_maze(width, height, mode);

    // Start the game
    printf("Set up game...\n");
    set_conio_terminal_mode(); // Enable non-blocking input mode

    printf("Starting game...\n");
    start_game(container, mode);
    reset_terminal_mode(); // Reset terminal mode on exit

    // Free memory
    free_maze(container);

    // Ask if the player wants to retry or exit
    printf("Congratulations! You completed the maze!\n");
    printf("Do you want to play again? (y/n): ");
    scanf(" %c", &retry); // Space before %c to consume newline
  } while (retry == 'y' || retry == 'Y');

  printf("Thanks for playing!\n");
  return 0;
}
