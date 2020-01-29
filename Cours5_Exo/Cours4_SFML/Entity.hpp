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
	int life = 2;

	Entity(sf::Shape *forme, sf::Shape *formeText, sf::Vector2f Pos, sf::Color color, sf::Texture * texture, sf::Texture * _spritetexture) {
		sprite = forme;
		sprite->setPosition(Pos.x, Pos.y);
		sprite->setFillColor(color);
		sprite->setTexture(texture);

		box = this->sprite->getGlobalBounds();
		
		spritetexture = formeText;
		spritetexture->setPosition(Pos.x, Pos.y);
		spritetexture->setTexture(_spritetexture);
		//destroyable = _destroyable;
		
	}

	~Entity()
	{

	}
	void _draw(sf::RenderWindow &win);

	void _destroy(sf::RenderWindow & win);

	void _changeTexture(sf::RenderWindow &win, sf::Texture * newtext);

};