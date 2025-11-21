#pragma once
#include <memory>
#include "Game.h"

class Menu : public Scene {
private: 
	sf::Text text;
	sf::Font font;

public:
	Menu() = default;
	void update(const float& dt) override;
	void render() override;
	void load() override;
};