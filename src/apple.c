#include "apple.h"
#include <ncurses.h>
#include <stdlib.h>

void draw_apple(struct Apple *apple) { mvprintw(apple->y, apple->x, "X"); }

void generate_apple(struct Apple *apple, int width, int height) {
  apple->x = rand() % width;
  apple->y = rand() % height;
}