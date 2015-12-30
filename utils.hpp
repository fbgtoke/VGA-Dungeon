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

const sf::Vector2i UP(0, -1);
const sf::Vector2i DOWN(0, 1);
const sf::Vector2i LEFT(-1, 0);
const sf::Vector2i RIGHT(1, 0);

enum Tile {NONE, WALL, WALK};

#endif // UTILS_HPP
