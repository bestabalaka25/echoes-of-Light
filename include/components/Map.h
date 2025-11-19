#pragma once
#include <vector>
#include <string>

enum class TileType {
    EMPTY,
    WALL,
    LIGHT_SOURCE,
    MIRROR,
    START,
    END
};

class Map {
public:
    Map(const std::string& filename);
    TileType getTile(int x, int y) const;
    int getWidth() const;
    int getHeight() const;

private:
    std::vector<std::vector<TileType>> tiles;
    int width = 0;
    int height = 0;    

    TileType charToTileType(char c) const;