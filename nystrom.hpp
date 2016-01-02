#ifndef NYSTROM_HPP
#define NYSTROM_HPP

#include "utils.hpp"
#include "dungeongenerator.hpp"

class Nystrom : public DungeonGenerator
{
private:
    matrix<int> map;
    int nregions;

    int width, height;

    int minrooms, maxrooms;
    int minwidth, maxwidth;
    int minheight, maxheight;
    int placeattempts;

    bool outOfBounds(int x, int y) const;
    bool outOfBounds(const sf::Vector2i& p) const;
    std::vector<sf::Vector2i> dirs = { UP, DOWN, LEFT, RIGHT };

    typedef sf::IntRect Room;
    std::vector<Room> rooms;
    Room boundary;
    static bool intersects(const Room& r1, const Room& r2);
    static bool contains(const Room& r1, const Room& r2);
    bool roomFits(const Room& r);
    void placeRoom(const Room& r, int value);

    typedef sf::Vector2i Connection;
    std::vector<Connection> connections;
    bool horizontalConnection(const sf::Vector2i left, const sf::Vector2i& right) const;
    bool verticalConnection(const sf::Vector2i& top, const sf::Vector2i& bottom) const;
    bool isConnection(int x, int y);
    void findConnections();
    void eraseRedundantConnections(std::vector<Connection>::iterator start);
    void flood(int x, int y, int value);

    void placeRooms();
    void createPassages();
    void connectRooms();
    void uncarve();
    void apply();

    int adjacentTiles(int x, int y, int value) const;
    void bfs(int x, int y, int value);

    bool isDeadEnd(int x, int y) const;
    void killDeadEnd(int x, int y);

public:
    Nystrom(DungeonLevel& lvl);
    ~Nystrom();

    void create();

    void setSize(int width, int height);
    int setNumRooms(int min, int max);
    int setRoomSize(int minw, int maxw, int minh, int maxh);
    int setPlaceAttempts(int attempts);

    void printMap();
    int getTile(int x, int y) const;
};

#endif // NYSTROM_HPP
