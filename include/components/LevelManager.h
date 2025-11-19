#pragma once
#include <string>
#include <vector>
#include "Map.hpp"

class LevelManager {
   public:
    LevelManager();
    ~LevelManager();

    bool loadLevel(const std::string& levelName);
    void nextLevel();
    bool isLevelComplete() const;
    const Map& getCurrentMap() const;

    private:
    std::vector<std::string> levelFiles;
    int currentLevelIndex = 0;
    Map map;
};