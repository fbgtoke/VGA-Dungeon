CC = g++
FLAGS = -std=c++11 -Wall
SFML = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system

TARGETS = game
all: $(TARGETS)

game: main.cpp
	$(CC) -c $(FLAGS) $(SFML) $^ -o $@

clean:
	rm -rf $(TARGETS) *.o
