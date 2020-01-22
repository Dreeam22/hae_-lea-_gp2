#include "pch.h"
#include "Proj.hpp"
#include "Entity.hpp"

void Proj::_draw(sf::RenderWindow & win) {
	win.draw(*sprite);
}

void Proj::move() {
	x += dir.x * projSpeed;
	y += dir.y * projSpeed;
	sprite->setPosition(x, y);
}

void Proj::coll(float posXProj, float posYProj, Entity * meuble) {

	auto meublePos = meuble->sprite->getPosition();
	auto meubleOff = meuble->box;
	if (posXProj < meublePos.x || posXProj > meublePos.x + meubleOff.width) { dir.x *= -1; }
	else if (posYProj < meublePos.y || posYProj > meublePos.y + meubleOff.height) { dir.y *= -1; }

}
