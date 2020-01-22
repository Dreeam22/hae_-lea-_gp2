#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Entity {
public:

	sf::Shape 	*sprite = nullptr; // pour le rendu
	sf::FloatRect		box;//pour les collisions

	Entity(sf::Shape *forme, sf::Vector2f Pos) {
		this->sprite = forme;
		this->sprite->setPosition(Pos.x, Pos.y);

		this->box = forme->getGlobalBounds();

	}

	~Entity()
	{

	}
	void _draw(sf::RenderWindow &win);


};