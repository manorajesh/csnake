#pragma once

struct Apple {
    int x, y;
};

void draw_apple(struct Apple *apple);
void generate_apple(struct Apple *apple, int width, int height);