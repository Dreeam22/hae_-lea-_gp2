#include "pch.h"
#include "Entity.hpp"

void Entity::_draw(sf::RenderWindow & win) {
	this -> box = this-> sprite->getGlobalBounds();
	spritetexture->setPosition(sprite->getPosition());
	win.draw(*sprite);
	win.draw(*spritetexture);
}

void Entity::_destroy(sf::RenderWindow & win) {
	this->sprite->setScale(0, 0);
	this->spritetexture->setScale(0, 0);
	this->box = this->sprite->getGlobalBounds();
	win.draw(*sprite);
	//this->isPlayer = false;
}

void Entity::_changeTexture(sf::RenderWindow & win, sf::Texture * newtext) {
	//spritetexture->setPosition(sprite->getPosition());
	spritetexture->setTexture(newtext);
}
