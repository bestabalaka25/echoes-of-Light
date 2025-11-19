#include "LevelManager.hpp"
#include <iostream>

constexpr int TILE_SIZE = 32; // used for converting tile -> world coords

LevelManager::LevelManager() {
    // Ordered maps define game progression
    levelFiles = {
        "resources/levels/past.txt",
        "resources/levels/present.txt",
        "resources/levels/future.txt"
    };
}

bool LevelManager::loadCurrentLevel() {
    if (currentLevelIndex >= levelFiles.size()) {
        std::cout << "No more levels to load.\n";
        return false;
    }

    std::string filename = levelFiles[currentLevelIndex];

    std::cout << "Loading level: " << filename << std::endl;

    bool success = map.loadFromFile(filename);
    
    if (success) {
        levelCompleted = false;
        findExitTile();
    }

    return success;
}

void LevelManager::nextLevel() {
    currentLevelIndex++;

    if (!isFinished()) {
        loadCurrentLevel();
    }
}

bool LevelManager::isFinished() const {
    return currentLevelIndex >= levelFiles.size();
}

void LevelManager::markLevelComplete() {
    levelCompleted = true;
}

bool LevelManager::isLevelComplete() const {
    return levelCompleted;
}

void LevelManager::findExitTile() {
    for (int y = 0; y < map.getHeight(); ++y) {
        for (int x = 0; x < map.getWidth(); ++x) {
            if (map.getTile(x, y) == TileType::END) {
                exitTile = {x, y};
                std::cout << "Exit tile found at: (" << x << ", " << y << ")\n";
                return;
            }
        }
    }

    std::cerr << "WARNING: No exit tile found in this level.\n";
}
