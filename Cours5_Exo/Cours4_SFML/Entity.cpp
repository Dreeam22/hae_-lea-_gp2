#include "pch.h"
#include "Entity.hpp"

void Entity::_draw(sf::RenderWindow & win) {
	box = sprite->getGlobalBounds();
	win.draw(*sprite);
	win.draw(*spritetexture);
}

void Entity::_destroy(sf::RenderWindow & win) {
	this->sprite->setScale(0, 0);
	this->box = this->sprite->getGlobalBounds();
	win.draw(*sprite);
	this->isPlayer = false;
}
