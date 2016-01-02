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
    findConnections();
    std::random_shuffle(connections.begin(), connections.end());

    std::vector<Connection>::iterator it;
    for (it = connections.begin(); it != connections.end(); ++it)
    {
        int x = it->x;
        int y = it->y;

        int value = -1;
        for (int k = 0; k < 4; ++k)
        {
            int nx = x + dirs[k].x;
            int ny = y + dirs[k].y;
            if (boundary.contains(nx, ny))
                value = max(value, map[ny][nx]);
        }
        if (value != -1)
        {
            flood(x, y, value);
            eraseRedundantConnections(it);
        }
    }
}
void Nystrom::uncarve()
{
    for (int i = 1; i < height; ++i)
    {
        for (int j = 1; j < width; ++j)
        {
            if (isDeadEnd(j, i))
                killDeadEnd(j, i);
        }
    }
}
void Nystrom::apply()
{
    level.setMapSize(width, height);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            Tile value = (map[i][j] == -1 ? WALL : WALK);
            level.setTile(j, i, value);
        }
    }
}

bool Nystrom::outOfBounds(int x, int y) const
{
    return (
        x < 0 or x >= width or
        y < 0 or y >= height
    );
}
inline bool Nystrom::outOfBounds(const sf::Vector2i& p) const
{
    return outOfBounds(p.x, p.y);
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

inline bool Nystrom::horizontalConnection(const sf::Vector2i left, const sf::Vector2i& right) const
{
    return (
        boundary.contains(left) and boundary.contains(right)
        and map[left.y][left.x] != -1 and map[right.y][right.x] != -1
        and map[left.y][left.x] != map[right.y][right.x]
        );
}
inline bool Nystrom::verticalConnection(const sf::Vector2i& top, const sf::Vector2i& bottom) const
{
    return (
        boundary.contains(top) and boundary.contains(bottom)
        and map[top.y][top.x] != -1 and map[bottom.y][bottom.x] != -1
        and map[top.y][top.x] != map[bottom.y][bottom.x]
        );
}
bool Nystrom::isConnection(int x, int y)
{
    if (not boundary.contains(x, y) or map[y][x] != -1) return false;
    sf::Vector2i center(x, y);
    sf::Vector2i left = center + LEFT;
    sf::Vector2i right = center + RIGHT;
    sf::Vector2i top = center + UP;
    sf::Vector2i bottom = center + DOWN;

    bool h = horizontalConnection(left, right);
    bool v = verticalConnection(top, bottom);
    return (h != v);
}
void Nystrom::findConnections()
{
    connections.clear();
    for (int i = 1; i < height-1; ++i)
    {
        for (int j = 1; j < width-1; ++j)
        {
            if (isConnection(j, i))
                connections.push_back(Connection(j, i));
        }
    }
}
void Nystrom::eraseRedundantConnections(std::vector<Connection>::iterator start)
{
    std::vector<Connection>::iterator it = start+1;
    while (it != connections.end())
    {
        if (not isConnection(it->x, it->y)) it = connections.erase(it);
        else ++it;
    }
}
void Nystrom::flood(int x, int y, int value)
{
    if (not outOfBounds(x, y))
    {
        map[y][x] = value;
        for (sf::Vector2i& d : dirs)
        {
            int nx = x + d.x;
            int ny = y + d.y;
            if (boundary.contains(nx, ny))
            {
                int v = map[ny][nx];
                if (v != -1 and v != value)
                    flood(nx, ny, value);
            }
        }
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
    std::queue<sf::Vector2i> q;
    q.push(sf::Vector2i(x, y));

    std::random_shuffle(dirs.begin(), dirs.end());
    while (not q.empty())
    {
        sf::Vector2i pos = q.front();
        q.pop();

        std::random_shuffle(dirs.begin(), dirs.end());
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
}

bool Nystrom::isDeadEnd(int x, int y) const
{
    if (not boundary.contains(x, y) or map[y][x] == -1) return false;
    sf::Vector2i p(x, y);

    int value = map[y][x];
    int count = 0;
    for (int k = 0; k < 4; ++k)
    {
        sf::Vector2i pos = p + dirs[k];
        int newvalue = map[pos.y][pos.x];
        if (boundary.contains(p) and newvalue != -1)
            ++count;
    }
    return count == 1;
}
void Nystrom::killDeadEnd(int x, int y)
{
    map[y][x] = -1;
    sf::Vector2i start(x, y);

    std::queue<sf::Vector2i> q;
    q.push(start);
    while (not q.empty())
    {
        sf::Vector2i pos = q.front();
        q.pop();

        for (int k = 0; k < 4; ++k)
        {
            int nx = pos.x + dirs[k].x;
            int ny = pos.y + dirs[k].y;
            if (isDeadEnd(nx, ny))
            {
                map[ny][nx] = -1;
                q.push(sf::Vector2i(nx, ny));
            }
        }
    }
}

Nystrom::Nystrom(DungeonLevel& lvl) : DungeonGenerator(lvl) {}
Nystrom::~Nystrom() {}

void Nystrom::create()
{
    std::cerr << "constructing matrix" << std::endl;
    map = matrix<int> (height, std::vector<int>(width, -1));
    std::cerr << "erasing previous rroms" << std::endl;
    rooms.clear();
    nregions = 0;

    std::cerr << "placing rooms" << std::endl;
    placeRooms();
    std::cerr << "creating passages" << std::endl;
    createPassages();
    std::cerr << "connecting" << std::endl;
    connectRooms();
    std::cerr << "uncarving" << std::endl;
    uncarve();
    std::cerr << "applying" << std::endl;
    apply();
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
