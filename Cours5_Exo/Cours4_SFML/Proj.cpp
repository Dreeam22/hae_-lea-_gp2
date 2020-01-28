#include "pch.h"
#include "Proj.hpp"
#include "Entity.hpp"

void Proj::_draw(sf::RenderWindow & win) {
	win.draw(*sprite);
}

void Proj::move() {
	x += dir.x * projSpeed;
	y += dir.y * projSpeed;
	this->sprite->setPosition(x, y);

	this->box = this->sprite->getGlobalBounds();
}

void Proj::coll(Entity * meuble) {

	auto posProj = this->sprite->getPosition();
	auto meublePos = meuble->sprite->getPosition();
	auto meubleOff = meuble->box;

	if (posProj.x > meublePos.x + meubleOff.width || posProj.x < meublePos.x ) { dir.x *= -1; }
	else if (posProj.y > meublePos.y + meubleOff.height || posProj.y < meublePos.y ) { dir.y *= -1; }
	this->bounced = true;
}
