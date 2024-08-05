#pragma once

struct Snake {
    int x, y;
    struct Snake *next;
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void draw_snake(struct Snake *snake, enum Direction dir);
void move_snake(struct Snake *snake, enum Direction dir, int width, int height);
void add_segment(struct Snake *snake);
void free_snake(struct Snake *snake);
int check_collision(struct Snake *snake);