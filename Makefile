SRC = main.c sources/gamestate.c sources/graphics.c sources/event_manager.c sources/queue.c sources/keyboard.c sources/interface.c sources/level.c sources/animations.c sources/moving.c 
INC = headers/defines.h headers/gamestate.h headers/graphics.h headers/event_manager.h headers/keyboard.h headers/interface.h headers/level.h headers/animations.h headers/moving.h

# SRC = $(wildcard *.c)
# INC = $(wildcard *.h)

OBJ = $(SRC:.c=.o)
BIN = projet

CPPFLAGS = `sdl-config --cflags`
CFLAGS   = -std=c99 -Wall -Wextra
LDFLAGS  = `sdl-config --libs` -lm

.PHONY: all clean

all: $(BIN)

$(OBJ): $(INC)

$(BIN): $(OBJ)
	$(CC) $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH) -o $@
	rm -f $(OBJ)

delo:
	rm -f $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f $(BIN)
