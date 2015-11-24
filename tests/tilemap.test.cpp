#include "utils.hpp"
#include "tilemap.hpp"
#include "tile.hpp"

Tilemap tilemap;
TilePermission p[NPERMISSIONS] = {NONE, WALK, WALL};

int getOption()
{
    std::cout << "Type next option:" << std::endl;
    std::cout << "0 to create Tilemap" << std::endl;
    std::cout << "1 to print Tilemap" << std::endl;
    std::cout << "2 to read Tiles" << std::endl;
    std::cout << "-1 to end" << std::endl;

    int op;
    std::cin >> op;
    return op;
}

void createTilemap()
{
    std::cout << "Create Tilemap" << std::endl;
    std::cout << "Type width and height" << std::endl;
    int width, height;
    std::cin >> width >> height;
    std::cout << "Read: " << width << " & " << height << std::endl;
    std::cout << "Instantiating Tilemap" << std::endl;
    tilemap = Tilemap(width, height);
    std::cout << "Tilemap created" << std::endl;
}

void readTiles()
{
    std::cout << "Type Tiles: x, y, permission" << std::endl;
    std::cout << "Permissions: 0=NONE 1=WALK 2=WALL" << std::endl;
    std::cout << "x=-1 to end" << std::endl;

    int x, y, permission;
    std::cin >> x;
    while (x != -1)
    {
        std::cin >> y >> permission;
        std::cout << "Read: " << x << " " << y << " with " << permission << std::endl;
        std::cout << "Instantiating Tile" << std::endl;
        Tile aux;
        aux.setPermission(p[permission]);
        std::cout << "Adding new Tile in Tilemap" << std::endl;
        tilemap.setTile(x, y, aux);
        std::cout << "Added new Tile" << std::endl;

        std::cin >> x;
    }

    std::cout << "Finish reading" << std::endl;
}

void printTilemap()
{
    std::cout << "Print Tilemap" << std::endl;
    tilemap.printMap();
    std::cout << "Finish printing" << std::endl;
}

int main()
{
    std::cout << "Test for Tile and Tilemap" << std::endl;
    int op;
    do {
        op = getOption();
        switch (op)
        {
        case 0:
            createTilemap();
            break;
        case 1:
            printTilemap();
            break;
        case 2:
            readTiles();
            break;
        default:
            break;
        }
    } while (op != -1);
    std::cout << "End of test" << std::endl;
}
