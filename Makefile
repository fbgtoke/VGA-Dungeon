###############
# VGA Dungeon #
###############

CC = g++
CFLAGS = -std=c++11
SFML = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

SDIR = .
ODIR = bin
OUT = VGADungeon.exe

_OBJS = dungeonlevel.o dungeonview.o tilemap.o character.o behavior.o dungeongenerator.o actor.o turncontroller.o textbox.o dungeoncontroller.o nystrom.o main.o

OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

$(OUT): $(OBJS)
	$(CC) -o $(OUT) $^ $(SFML)

clean:
	rm -rf $(ODIR)/*.o $(OUT) *.exe
