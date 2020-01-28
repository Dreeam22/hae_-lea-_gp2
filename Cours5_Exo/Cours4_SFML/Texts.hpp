#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Textes : public Text
{
public:
	sf::Text *UI = new Text;
	bool isMenu, isIG;
	Textes(sf::Font *_myfont, int _size, sf::Vector2f _pos, sf::Color _color, sf::String _string, bool _isMenu) {

		UI->setFont(*_myfont);
		UI->setCharacterSize(_size);
		UI->setPosition(_pos);
		UI->setFillColor(_color);
		UI->setString(_string);
		isMenu = _isMenu;
	}
	//~Textes();

	void _draw(sf::RenderWindow & win);

};
