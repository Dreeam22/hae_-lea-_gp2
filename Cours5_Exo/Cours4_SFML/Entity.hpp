#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Entity {
public:

	sf::Shape 	*sprite = nullptr; // pour le rendu
	sf::FloatRect		box;//pour les collisions
	bool isPlayer = false, isCanon = false;
	Entity(sf::Shape *forme, sf::Vector2f Pos) {
		this->sprite = forme;
		this->sprite->setPosition(Pos.x, Pos.y);

		this->box = this->sprite->getGlobalBounds();

	}

	~Entity()
	{

	}
	void _draw(sf::RenderWindow &win);

	void _destroy(int player);

};