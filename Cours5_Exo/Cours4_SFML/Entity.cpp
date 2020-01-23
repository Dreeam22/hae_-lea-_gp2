#include "pch.h"
#include "Entity.hpp"

void Entity::_draw(sf::RenderWindow & win) {
	this->box = this->sprite->getGlobalBounds();
	win.draw(*sprite);
}

void Entity::_destroy(int player) {

}
