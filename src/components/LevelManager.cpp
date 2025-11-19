#include "LevelManager.hpp"
#include <iostream>

LevelManager::LevelManager() {
    levelFiles = {
        "resources/levels/past.txt",
        "resources/levels/present.txt",
        "resources/levels/future.txt"
    };
}

bool LevelManager::loadCurrentLevel() {
    if(currentIndex >= levelFiles.size()) return false;

    std::cout << "Loading level " << currentIndex + 1 
              << ": " << levelFiles[currentIndex] << std::endl;

    return map.loadFromFile(levelFiles[currentIndex]);
}

void LevelManager::nextLevel() {
    currentIndex++;
    if (!isFinished()) {
        loadCurrentLevel();
    }
}

bool LevelManager::isFinished() const {
    return currentIndex >= levelFiles.size();
}

const Map& LevelManager::getMap() const {
    return map;
}