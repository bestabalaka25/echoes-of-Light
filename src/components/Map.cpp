#include "Map.hpp"
#include <fstream>
#include <iostream>

TileType Map::charToTileType(char c) const {
    switch (c) {
        case '#': return TileType::WALL;
        case 'L': return TileType::LIGHT_SOURCE;
        case '/': return TileType::MIRROR;
        case 'S': return TileType::START;
        case 'E': return TileType::END;
        default:  return TileType::EMPTY;
    }
}

bool Map::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to load map: " << filename << std::endl;
        return false;
    }

    grid.clear();
    std::string line;

    while (std::getline(file, line)) {
        std::vector<TileType> row;
        for (char c : line) {
            row.push_back(charToTile(c));
        }
        grid.push_back(row);
    }

    height = grid.size();
    width = height > 0 ? grid[0].size() : 0;

    std::cout << "Map loaded: " << width << "x" << height << std::endl;
    return true;
}

TileType Map::getTile(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return TileType::WALL; // Out of bounds treated as wall
    }
    return grid[y][x];
}