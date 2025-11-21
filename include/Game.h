#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Systems.h"

class Game {
public:
    Game();

    int run();

private:
    bool initialize();
    bool loadResources();
    void createEntities();
    Entity createPlayerEntity();
    Entity createLightBeaconEntity();
    Entity createEnemyEntity();
    void handleEvents();
    void update(float deltaTime);
    void render();
    std::string findResourcePath(const std::string& relativePath) const;

private:
    static constexpr unsigned int windowWidth = 800;
    static constexpr unsigned int windowHeight = 600;
    static constexpr unsigned int framerateLimit = 60;

    sf::RenderWindow window_;
    sf::Clock clock_;

    sf::Texture idleTexture_;
    sf::Texture moveTexture_;
    bool initialized_;

    Entity player_;
    Entity lightBeacon_;
    Entity enemy_;
    std::vector<Entity*> entities_;

    InputSystem inputSystem_;
    AnimationSystem animationSystem_;
    RenderSystem renderSystem_;
};

