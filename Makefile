SRC = main.c gamestate.c graphics.c event_manager.c
INC = h/defines.h h/gamestate.h h/graphics.h h/event_manager.h

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
