#include "pch.h"
#include "Entity.hpp"

void Entity::_draw(sf::RenderWindow & win) {
	win.draw(*sprite);
}
