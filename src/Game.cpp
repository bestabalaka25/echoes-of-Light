#include "Game.h"

#include <filesystem>
#include <iostream>
#include <memory>

#include "components/AnimationComponent.h"
#include "components/EnemyComponent.h"
#include "components/LightComponent.h"
#include "components/LightSourceComponent.h"
#include "components/PlayerComponent.h"
#include "components/PuzzleComponent.h"
#include "components/RenderComponent.h"
#include "components/TransformComponent.h"
#include "components/UpgradeComponent.h"

namespace {
    constexpr char windowTitle[] = "Echoes of Light";
}

Game::Game()
    : window_{}
    , clock_{}
    , idleTexture_{}
    , moveTexture_{}
    , initialized_{false}
    , player_{}
    , lightBeacon_{}
    , enemy_{}
    , entities_{} {}

int Game::run() {
    if (!initialized_ && !initialize()) {
        return -1;
    }

    while (window_.isOpen()) {
        float deltaTime = clock_.restart().asSeconds();

        handleEvents();
        update(deltaTime);
        render();
    }

    return 0;
}

bool Game::initialize() {
    window_.create(sf::VideoMode({ windowWidth, windowHeight }), windowTitle);
    window_.setFramerateLimit(framerateLimit);

    std::cout << "=== ECHOES OF LIGHT ===" << std::endl;

    if (!loadResources()) {
        return false;
    }

    createEntities();
    clock_.restart();

    std::cout << "Controls: WASD to move, ESC to exit" << std::endl;
    std::cout << "Animation system active!" << std::endl;

    initialized_ = true;
    return true;
}

bool Game::loadResources() {
    const std::string idlePath = findResourcePath("resources/sprites/Character_Idle.png");
    const std::string movePath = findResourcePath("resources/sprites/Character_Move.png");

    if (!idleTexture_.loadFromFile(idlePath)) {
        std::cerr << "ERROR: Failed to load idle texture" << std::endl;
        return false;
    }

    if (!moveTexture_.loadFromFile(movePath)) {
        std::cerr << "ERROR: Failed to load move texture" << std::endl;
        return false;
    }

    std::cout << "Textures loaded successfully" << std::endl;
    return true;
}

void Game::createEntities() {
    player_ = createPlayerEntity();
    lightBeacon_ = createLightBeaconEntity();
    enemy_ = createEnemyEntity();

    entities_.clear();
    entities_.push_back(&player_);
    // Additional entities will be added once their rendering data is available.
}

Entity Game::createPlayerEntity() {
    Entity entity;
    entity.name = "Player";

    entity.components.emplace_back(std::make_unique<eol::TransformComponent>(
        sf::Vector2f{ 400.f, 300.f },
        sf::Vector2f{ 0.5f, 0.5f },
        0.f));

    entity.components.emplace_back(std::make_unique<eol::RenderComponent>());
    entity.components.emplace_back(std::make_unique<eol::PlayerComponent>());

    auto animationComponent = std::make_unique<eol::AnimationComponent>();

    eol::Animation idleAnim;
    idleAnim.name = "idle";
    idleAnim.texture = &idleTexture_;
    idleAnim.frameCount = 4;
    idleAnim.frameWidth = 128;
    idleAnim.frameHeight = 128;
    idleAnim.frameDuration = 0.15f;
    idleAnim.loop = true;
    animationComponent->addAnimation("idle", idleAnim);

    eol::Animation walkAnim;
    walkAnim.name = "walk";
    walkAnim.texture = &moveTexture_;
    walkAnim.frameCount = 6;
    walkAnim.frameWidth = 128;
    walkAnim.frameHeight = 128;
    walkAnim.frameDuration = 0.1f;
    walkAnim.loop = true;
    animationComponent->addAnimation("walk", walkAnim);

    animationComponent->setAnimation("idle");
    entity.components.emplace_back(std::move(animationComponent));

    entity.components.emplace_back(std::make_unique<eol::LightComponent>());
    entity.components.emplace_back(std::make_unique<eol::UpgradeComponent>());

    return entity;
}

Entity Game::createLightBeaconEntity() {
    Entity entity;
    entity.name = "LightBeacon";
    entity.components.emplace_back(std::make_unique<eol::TransformComponent>());
    entity.components.emplace_back(std::make_unique<eol::LightSourceComponent>());
    entity.components.emplace_back(std::make_unique<eol::PuzzleComponent>());
    entity.components.emplace_back(std::make_unique<eol::RenderComponent>());
    return entity;
}

Entity Game::createEnemyEntity() {
    Entity entity;
    entity.name = "Enemy";
    entity.components.emplace_back(std::make_unique<eol::TransformComponent>());
    entity.components.emplace_back(std::make_unique<eol::EnemyComponent>());
    entity.components.emplace_back(std::make_unique<eol::RenderComponent>());
    entity.components.emplace_back(std::make_unique<eol::LightComponent>());
    return entity;
}

void Game::handleEvents() {
    while (const auto event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window_.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                window_.close();
            }
        }
    }
}

void Game::update(float deltaTime) {
    inputSystem_.update(player_, deltaTime);
    animationSystem_.update(entities_, deltaTime);

    // Level progression and win-condition logic will be reinstated when
    // LevelManager support is ready.
}

void Game::render() {
    window_.clear(sf::Color(20, 20, 30));
    renderSystem_.render(window_, entities_);
    window_.display();
}

std::string Game::findResourcePath(const std::string& relativePath) const {
    const std::vector<std::string> possiblePaths = {
        relativePath,
        "../../../" + relativePath,
        "../../../../" + relativePath,
        "D:/code/echoes/echoes-of-Light/" + relativePath
    };

    for (const auto& path : possiblePaths) {
        if (std::filesystem::exists(path)) {
            return path;
        }
    }

    return relativePath;
}

