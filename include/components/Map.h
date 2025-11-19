#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

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
    Map() = default;                        // allows constructing without a filename
    bool loadFromFile(const std::string& filename);

    TileType getTile(int x, int y) const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // Textures for rendering
    void setTextures(
        const sf::Texture& wallTex,
        const sf::Texture& lightTex,
        const sf::Texture& mirrorTex,
        const sf::Texture& startTex,
        const sf::Texture& endTex,
        const sf::Texture& emptyTex
    );

    void draw(sf::RenderWindow& window) const;

    // Collision checks
    bool isWalkableTile(TileType t) const;
    bool isWalkableTileCoord(int tx, int ty) const;
    bool isWalkableWorld(float worldx, float worldy) const;

private:
    TileType charToTile(char c) const;

    std::vector<std::vector<TileType>> grid;
    int width = 0;
    int height = 0;

    // Texture pointers
    const sf::Texture* wallTexture = nullptr;
    const sf::Texture* lightTexture = nullptr;
    const sf::Texture* mirrorTexture = nullptr;
    const sf::Texture* startTexture = nullptr;
    const sf::Texture* exitTexture = nullptr;
    const sf::Texture* emptyTexture = nullptr;
};
