###############
# VGA Dungeon #
###############

CC = g++
CFLAGS = -std=c++11
SFML = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

FILES = main.cpp dungeonlevel.cpp dungeonview.cpp tilemap.cpp character.cpp behavior.cpp dungeongenerator.cpp actor.cpp turncontroller.cpp 

all: debug release

debug:
	$(CC) $(CFLAGS) -DDEBUG -c $(FILES)
	$(CC) -o debug.exe *.o $(SFML)

release:
	$(CC) $(CFLAGS) -c $(FILES)
	$(CC) -o VGADungeon.exe *.o $(SFML)

clean:
	rm -rf *.o *.exe
