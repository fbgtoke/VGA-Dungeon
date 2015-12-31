#ifndef NYSTROM_HPP
#define NYSTROM_HPP

#include "utils.hpp"
//#include "dungeongenerator.hpp"

class Nystrom //: public DungeonGenerator
{
private:
    matrix<Tile> map;

    int width, height;

    int minrooms, maxrooms;
    int minwidth, maxwidth;
    int minheight, maxheight;
    int placeattempts;

    typedef sf::IntRect Room;
    std::vector<Room> rooms;
    Room boundary;

    void placeRooms();
    void createPassages();
    void connectRooms();
    void uncarve();

    bool roomFits(const Room& r);
    void placeRoom(const Room& r);
    static bool intersects(const Room& r1, const Room& r2);
    static bool contains(const Room& r1, const Room& r2);
    bool outOfBounds(int x, int y) const;
    void shuffle(sf::Vector2i* d) const;
    int adjacentTiles(int x, int y) const;
    void bfs(int x, int y);

public:
     Nystrom();
//    Nystrom(DungeonLevel& lvl);
    ~Nystrom();

    void create(); //final;

    void setSize(int width, int height);
    int setNumRooms(int min, int max);
    int setRoomSize(int minw, int maxw, int minh, int maxh);
    int setPlaceAttempts(int attempts);

    void printMap();
    Tile getTile(int x, int y) const;
};

#endif // NYSTROM_HPP
