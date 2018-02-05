CC = gcc
CFLAGS = -pedantic -Wall -Wextra -I./SDL/include
LFLAGS = -L./SDL/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -lSDL2_image -lSDL2_mixer

#Sources
SRC = main.c data.c
#Headers
HDRS = data.h
#Kompilierte Exe
EXE = e.exe


build: $(EXE)

all: $(EXE)
	./$<

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC) $(LFLAGS)