
#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

using namespace sf;

class Proj {
public:

	sf::Shape 	*sprite = nullptr; // pour le rendu
	sf::FloatRect		box;//pour les collisions
	Vector2f dir;
	float x, y;
	bool bounced = false;
	int projSpeed = 5;

	Proj(sf::Shape *forme, sf::Vector2f Pos, float angle) {
		this->sprite = forme;
		this->sprite->setPosition(Pos.x, Pos.y);

		this->box = forme->getGlobalBounds();

		this->dir = Vector2f(cos(angle), sin(angle));		

		this->x = this->sprite->getPosition().x;
		this->y = this->sprite->getPosition().y;

	}

	~Proj()
	{
		if (dir != Vector2f(0, 0)) dir = Vector2f(0, 0);
		if (sprite) delete sprite;
		sprite = nullptr;
	}
	void _draw(sf::RenderWindow &win);

	void move();

	void coll(Entity* meuble);

};