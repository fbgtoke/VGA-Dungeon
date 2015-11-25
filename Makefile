CC = g++
CFLAGS = -std=c++11 -Wall -O2
LFLAGS = 
SFML = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system
INCLUDES = .

TARGETS = game testTilemap testEventHistory dungeonlevel character characterfactory behavior command main
all: $(TARGETS)

game: main dungeonlevel character characterfactory behavior command tilemap dungeongenerator
	$(CC) main.o dungeonlevel.o character.o characterfactory.o behavior.o command.o tilemap.o tile.o dungeongenerator.o $(SFML) -o $@

testTilemap: tests/tilemap.test.cpp tilemap.cpp tile.cpp
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDES)
	$(CC) tilemap.test.o tilemap.o tile.o $(SFML) -o $@

testEventHistory: tests/eventhistory.test.cpp eventhistory.cpp
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDES)
	$(CC) eventhistory.test.o eventhistory.o $(SFML) -o $@

main: main.cpp
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDES)

dungeonlevel: dungeonlevel.cpp
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDES)

character: character.cpp
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDES)

characterfactory: characterfactory.cpp
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDES)

behavior: behavior.cpp
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDES)

command: command.cpp
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDES)

tilemap: tilemap.cpp tile.cpp
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDES)

dungeongenerator: dungeongenerator.cpp
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDES)

clean:
	rm -rf $(TARGETS) *.o
