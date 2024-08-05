#include "snake.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void draw_snake(struct Snake *snake, enum Direction dir) {
  if (snake == NULL)
    return;

  // draw the head
  if (dir == UP) {
    mvprintw(snake->y, snake->x, "^");
  } else if (dir == DOWN) {
    mvprintw(snake->y, snake->x, "V");
  } else if (dir == LEFT) {
    mvprintw(snake->y, snake->x, "<");
  } else if (dir == RIGHT) {
    mvprintw(snake->y, snake->x, ">");
  }

  // draw the body
  struct Snake *current = snake->next;
  while (current != NULL) {
    mvprintw(current->y, current->x, "o");
    current = current->next;
  }
}

void move_snake(struct Snake *snake, enum Direction dir, int width,
                int height) {
  if (snake == NULL)
    return;

  // current position of the head
  int new_x = snake->x;
  int new_y = snake->y;

  // get the new position of the head
  switch (dir) {
  case UP:
    --new_y;
    break;
  case DOWN:
    ++new_y;
    break;
  case LEFT:
    --new_x;
    break;
  case RIGHT:
    ++new_x;
    break;
  }

  // bounds wrapping
  if (new_x < 0)
    new_x = width - 1;
  if (new_x >= width)
    new_x = 0;
  if (new_y < 0)
    new_y = height - 1;
  if (new_y >= height)
    new_y = 0;

  // Update the head
  int prev_x = snake->x;
  int prev_y = snake->y;
  snake->x = new_x;
  snake->y = new_y;

  // Update the rest of the snake segments
  struct Snake *current = snake->next;
  while (current != NULL) {
    int temp_x = current->x;
    int temp_y = current->y;
    current->x = prev_x;
    current->y = prev_y;
    prev_x = temp_x;
    prev_y = temp_y;
    current = current->next;
  }
}

void add_segment(struct Snake *snake) {
  // get last segment
  struct Snake *current = snake;
  while (current->next != NULL) {
    current = current->next;
  }

  // allocate new segment
  struct Snake *new_segment = malloc(sizeof(struct Snake));
  if (new_segment == NULL) {
    endwin();
    exit(1);
    printf("Failed to allocate memory for new snake segment\n");
  }

  // set new segment position
  new_segment->x = current->x;
  new_segment->y = current->y;
  current->next = new_segment;
}

void free_snake(struct Snake *snake) {
  struct Snake *current = snake;
  while (current != NULL) {
    struct Snake *temp = current;
    current = current->next;
    free(temp);
  }
}

int check_collision(struct Snake *snake) {
  struct Snake *current = snake->next;
  while (current != NULL) {
    if (snake->x == current->x && snake->y == current->y) {
      return true;
    }
    current = current->next;
  }
  return false;
}