#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <iostream>
#include <list>
#include <queue>
#include <map>
#include <algorithm>
#include <assert.h>

template <typename T> using matrix = std::vector<std::vector<T>>;

const std::string app_name = "VGA Dungeon";
const int window_width = 800;
const int window_height = 640;

const std::string resources = "resources/";

typedef sf::Vector2i Direction;
const Direction UP(0, -1);
const Direction DOWN(0, 1);
const Direction LEFT(-1, 0);
const Direction RIGHT(1, 0);

enum Tile {NONE, WALL, WALK};

enum CommandType {IDLE, MOVE, ATTACK};
struct Command
{
    CommandType type;
    Direction direction;
    Command() : type(IDLE) {}
    Command(CommandType t, Direction d) :
        type(t), direction(d) {}
};

#define min(a, b) ( (a < b) ? a : b)
#define max(a, b) ( (a > b) ? a : b)

#endif // UTILS_HPP
