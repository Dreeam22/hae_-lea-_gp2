#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Entity {
public:

	sf::Shape 	*sprite = nullptr; // pour le rendu
	sf::Shape	*spritetexture = nullptr;
	sf::FloatRect		box;//pour les collisions
	bool isPlayer = false, isCanon = false;
	sf::Texture _texture;

	Entity(sf::Shape *forme, sf::Shape *formeText, sf::Vector2f Pos, sf::Texture * texture) {
		this->sprite = forme;
		this->sprite->setPosition(Pos.x, Pos.y);

		this->box = this->sprite->getGlobalBounds();
		
		spritetexture = formeText;
		spritetexture->setPosition(Pos.x, Pos.y);
		spritetexture->setTexture(texture);
	}

	~Entity()
	{

	}
	void _draw(sf::RenderWindow &win);

	void _destroy(sf::RenderWindow & win);

};