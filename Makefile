CC = clang
CFLAGS = -Wall -Wextra -Iinclude
OBJ = src/main.o src/snake.o src/apple.o
TARGET = csnake
LIBS = -lncurses

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)