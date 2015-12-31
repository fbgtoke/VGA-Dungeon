#include "nystrom.hpp"

void Nystrom::placeRooms()
{
    int nrooms = rand()%(maxrooms - minrooms + 1) + minrooms;
    int attempts = 0;
    while (rooms.size() < nrooms and attempts < placeattempts)
    {
        int x = rand()%width;
        int y = rand()%height;
        int w = rand()%(maxwidth - minwidth + 1) + minwidth;
        int h = rand()%(maxheight - minheight + 1) + minheight;
        Room r(x, y, w, h);

        if (roomFits(r))
        {
            placeRoom(r);
            attempts = 0;
        }
        else
        {
            ++attempts;
        }
    }
}
void Nystrom::createPassages() {}
void Nystrom::connectRooms() {}
void Nystrom::uncarve() {}

bool Nystrom::roomFits(const Room& r)
{
    if (not contains(Room(1, 1, width-2, height-2), r))
        return false;

    for (Room& r2 : rooms)
    {
        Room skin(r2.left-1, r2.top-1, r2.width+2, r2.height+2);
        if (intersects(r, skin)) return false;
    }

    return true;
}
void Nystrom::placeRoom(const Room& r)
{
    for (int i = r.top; i < r.top+r.height; ++i)
        for (int j = r.left; j < r.left+r.width; ++j)
            map[i][j] = WALK;

    rooms.push_back(r);
}

bool Nystrom::intersects(const Room& r1, const Room& r2)
{
    return (
        r1.left < r2.left+r2.width and
        r1.left+r1.width > r2.left and
        r1.top < r2.top+r2.height and
        r1.top+r1.height > r2.top
    );
}
bool Nystrom::contains(const Room& r1, const Room& r2)
{
    return (
        r1.left < r2.left and
        r1.left+r1.width > r2.left+r2.width and
        r1.top < r2.top and
        r1.top+r1.height > r2.top+r2.height
    );
}
bool Nystrom::outOfBounds(int x, int y) const
{
    return (
        x < 0 or x >= width or
        y < 0 or y >= height
    );
}
void Nystrom::shuffle(sf::Vector2i* d) const
{
    for (int i = 3; i > 0; --i)
    {
        sf::Vector2i aux = d[i];
        int index = rand()%i;
        d[i] = d[index];
        d[index] = aux;
    }
}
int Nystrom::adjacentTiles(int x, int y) const
{
    static sf::Vector2i d[] = { UP+LEFT, UP, UP+RIGHT, LEFT, RIGHT, DOWN+LEFT, DOWN, DOWN+RIGHT };

    int count = 0;
    for (int i = 0; i < 8; ++i)
    {
        int nx = x + d[i].x;
        int ny = y + d[i].y;
        if (not outOfBounds(nx, ny) and map[ny][nx] == WALK)
            ++count;
    }
    return count;
}

Nystrom::Nystrom() {}
//Nystrom::Nystrom(DungeonLevel& lvl) : DungeonGenerator(lvl) {}
Nystrom::~Nystrom() {}

void Nystrom::create()
{
    map = matrix<Tile> (height, std::vector<Tile>(width, WALL));

    placeRooms();
    createPassages();
    connectRooms();
    uncarve();
}

void Nystrom::setSize(int w, int h)
{
    width = w;
    height = h;
}
int Nystrom::setNumRooms(int min, int max)
{
    minrooms = min;
    maxrooms = max;
}
int Nystrom::setRoomSize(int minw, int maxw, int minh, int maxh)
{
    minwidth = minw;
    maxwidth = maxw;
    minheight = minh;
    maxheight = maxh;
}
int Nystrom::setPlaceAttempts(int attempts)
{
    placeattempts = attempts;
}

void Nystrom::printMap()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
            std::cout << map[i][j];
        std::cout << std::endl;
    }
}
Tile Nystrom::getTile(int x, int y) const
{
    return map[y][x];
}
