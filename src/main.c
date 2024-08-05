#include "apple.h"
#include "snake.h"
#include <ncurses.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void process_input(int ch, enum Direction *dir, struct Snake *snake,
                   int *score) {
  switch (ch) {
  case 'q':
    endwin();
    exit(0);
    break;

  case 'w':
    if (*dir != DOWN)
      *dir = UP;
    break;

  case 's':
    if (*dir != UP)
      *dir = DOWN;
    break;

  case 'a':
    if (*dir != RIGHT)
      *dir = LEFT;
    break;

  case 'd':
    if (*dir != LEFT)
      *dir = RIGHT;
    break;

  case '=':
  case '+':
    add_segment(snake);
    ++*score;
    break;
  }
}

int main() {
  initscr();
  nodelay(stdscr, TRUE); // Set non-blocking mode
  noecho();              // Don't echo input characters
  curs_set(FALSE);       // Hide the cursor

  int width, height;
  getmaxyx(stdscr, height, width);

  struct Snake *snake = malloc(sizeof(struct Snake));
  snake->x = width / 2;
  snake->y = height / 2;
  snake->next = NULL;

  struct Apple apple;
  generate_apple(&apple, width, height);

  enum Direction dir = RIGHT;

  int score = 1; // initial score

  struct pollfd fds[1];
  fds[0].fd = STDIN_FILENO;
  fds[0].events = POLLIN;

  while (true) {
    int ret = poll(fds, 1, 100); // 100 ms timeout

    if (ret > 0 && (fds[0].revents & POLLIN)) {
      int ch = getch();
      if (ch != ERR) {
        process_input(ch, &dir, snake, &score);
      }
    }

    // update snake
    move_snake(snake, dir, width, height);
    if (check_collision(snake))
      break;

    if (snake->x == apple.x && snake->y == apple.y) {
      add_segment(snake);
      generate_apple(&apple, width, height);
      ++score;
    }

    // draw snake if input or update
    erase();
    mvprintw(0, 0, "Score: %d", score);
    draw_snake(snake, dir);
    draw_apple(&apple);
    refresh();
  }

  free_snake(snake);
  endwin();
  printf("Game Over\nScore: %d\n", score);
  return 0;
}