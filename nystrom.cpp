#include "nystrom.hpp"

void Nystrom::placeRooms()
{
    int nrooms = rand()%(maxrooms - minrooms + 1) + minrooms;
    int attempts = 0;
    while (rooms.size() < nrooms and attempts < placeattempts)
    {
        int x = 2*(rand()%(width/2)) + 1;
        int y = 2*(rand()%(height/2)) + 1;
        int w = minwidth + 2*(rand()%((maxwidth - minwidth)/2+1));
        int h = minheight + 2*(rand()%((maxheight - minheight)/2+1));
        Room r(x, y, w, h);

        if (roomFits(r))
        {
            placeRoom(r, nregions++);
            attempts = 0;
        }
        else
        {
            ++attempts;
        }
    }
}
void Nystrom::createPassages()
{
    for (int i = 1; i < height-1; i += 2)
    {
        for (int j = 1; j < width-1; j += 2)
        {
            if (map[i][j] == -1 and adjacentTiles(j, i, nregions) == 0)
            {
                map[i][j] = nregions;
                bfs(j, i, nregions);
                ++nregions;
            }
        }
    }
}
void Nystrom::connectRooms()
{
    std::list<sf::Vector2i> connections;
    for (int i = 1; i < height-1; i +=2)
    {
        for (int j = 1; j < width-1; j += 2)
        {
            int value = map[i][j];
            if (value == -1)
            {
                sf::Vector2i center(j, i);
                sf::Vector2i left = center + LEFT;
                sf::Vector2i right = center + RIGHT;
                sf::Vector2i top = center + UP;
                sf::Vector2i borrom = center + DOWN;
                if (
                    (not outOfBounds(left.x, left.y) and not outOfBounds(right.x, right.y)
                    and map[left.y][left.x] != map[right.y][right.x]) or
                    (not outOfBounds(top.x, top.y) and not outOfBounds(bottom.x, bottom.y)
                    and map[top.y][top.x] != map[bottom.y][bottom.x])
                    )
                {
                    connections.push_back(center);
                }
            }
        }
    }

    std::random_shuffle(connections.start(), connections.end());

    for (sf::Vector2i& c : connections)
    {
        int value = -1;
        for (int k = 0; k < 4; ++k)
        {
            int nx = c.x + dirs[k].x;
            int ny = c.y + dirs[k].y;
            if (map[ny][nx] > value)
                value = map[ny][nx];
        }
    }
}
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
void Nystrom::placeRoom(const Room& r, int value)
{
    for (int i = r.top; i < r.top+r.height; ++i)
        for (int j = r.left; j < r.left+r.width; ++j)
            map[i][j] = value;

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
        int index = rand()%(i+1);

        sf::Vector2i aux = d[i];
        d[i] = d[index];
        d[index] = aux;
    }
}
int Nystrom::adjacentTiles(int x, int y, int value) const
{
    static sf::Vector2i d[] = { UP, DOWN, LEFT, RIGHT };

    int count = 0;
    for (int i = 0; i < 4; ++i)
    {
        int nx = x + d[i].x;
        int ny = y + d[i].y;
        if (not outOfBounds(nx, ny) and map[ny][nx] == value)
            ++count;
    }
    return count;
}
void Nystrom::bfs(int x, int y, int value)
{
    std::cerr << "Starting bfs: (" << x << "," << y << ")" << std::endl;

    std::queue<sf::Vector2i> q;
    q.push(sf::Vector2i(x, y));

    sf::Vector2i dirs[] = {UP, DOWN, LEFT, RIGHT};
    while (not q.empty())
    {
        sf::Vector2i pos = q.front();
        q.pop();

        shuffle(dirs);
        for (int k = 0; k < 4; ++k)
        {
            int nx = pos.x + dirs[k].x;
            int ny = pos.y + dirs[k].y;
            int nx2 = nx + dirs[k].x;
            int ny2 = ny + dirs[k].y;

            if (boundary.contains(nx2, ny2) and map[ny2][nx2] != value
                and adjacentTiles(nx, ny, -1) == 3)
            {
                map[ny][nx] = value;
                map[ny2][nx2] = value;
                q.push(sf::Vector2i(nx2, ny2));
            }
        }
    }
    std::cerr << "Done bfs" << std::endl;
}

Nystrom::Nystrom() {}
//Nystrom::Nystrom(DungeonLevel& lvl) : DungeonGenerator(lvl) {}
Nystrom::~Nystrom() {}

void Nystrom::create()
{
    map = matrix<int> (height, std::vector<int>(width, -1));
    rooms.clear();
    nregions = 0;

    placeRooms();
    createPassages();
    connectRooms();
    uncarve();

    std::cerr << "Done creating" << std::endl;
}

void Nystrom::setSize(int w, int h)
{
    assert (w > 0 and h > 0);

    width = w;
    height = h;
    boundary = Room(1, 1, width-2, height-2);
}
int Nystrom::setNumRooms(int min, int max)
{
    assert (min <= max);

    minrooms = min;
    maxrooms = max;
}
int Nystrom::setRoomSize(int minw, int maxw, int minh, int maxh)
{
    assert (minw <= maxw);
    assert (minh <= maxh);

    minwidth = (minw%2 == 0) ? minw+1 : minw;
    maxwidth = (maxw%2 == 0) ? maxw-1 : maxw;
    minheight = (minh%2 == 0) ? minh+1 : minh;
    maxheight = (maxh%2 == 0) ? maxh-1 : maxh;
}
int Nystrom::setPlaceAttempts(int attempts)
{
    assert (attempts > 0);

    placeattempts = attempts;
}

void Nystrom::printMap()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
            std::cout << ((unsigned int) map[i][j])%10 << " ";
        std::cout << std::endl;
    }
}
int Nystrom::getTile(int x, int y) const
{
    return map[y][x];
}
