SRC = main.c gamestate.c fighter.c
INC = defines.h	gamestate.h fighter.h

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

clean:
	rm -f $(OBJ)
	rm -f $(BIN)
