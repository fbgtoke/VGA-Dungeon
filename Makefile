CC = g++
FLAGS = -std=c++11 -Wall
SFML = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system
INCLUDES = .

TARGETS = game testTilemap
all: $(TARGETS)

game: main.cpp
	$(CC) $(FLAGS) $(SFML) $^ -o $@

testTilemap: tests/tilemap.test.cpp tilemap.cpp tile.cpp
	$(CC) $(FLAGS) -c tile.cpp
	$(CC) $(FLAGS) -c tilemap.cpp
	$(CC) $(FLAGS) $(SFML) $^ -o $@ -I$(INCLUDES)

clean:
	rm -rf $(TARGETS) *.o
