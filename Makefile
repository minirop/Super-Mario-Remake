FILES=src/main.c src/GameState.c src/MainState.c src/JeuState.c src/Mario.c
LIBSW=-lmingw32 -lSDLmain -lSDL.dll -lSDL_image
LIBSU=-lSDLmain -lSDL -lSDL_image
OPTS=-Wall -Wextra -ansi -pedantic -iquoteinclude
OUTPUT=SMB

all:
	gcc $(OPTS) $(FILES) -mwindows $(LIBSW) -o $(OUTPUT)

unix:
	gcc $(OPTS) $(FILES) $(LIBSU) -o $(OUTPUT)
