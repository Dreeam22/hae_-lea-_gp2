// Cours4_SFML.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Lib.hpp"

using namespace sf;


static RectangleShape *rec = nullptr;
static CircleShape *circ = nullptr;
static Vector2f shPos;
static Vector2f shDir;
static Vector2f circPos;

int squareSpeed = 3;
int projSpeed = 30;

bool launch = false;

float lerp(float a, float b, float r) {
	return a + (b - a) * r;
}

float rd() {
	return 1.0 * rand() / RAND_MAX;
}

/*sf::Color hsv(int hue, float sat, float val)
{
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255);
	case 1: return sf::Color(q * 255, val * 255, p * 255);
	case 2: return sf::Color(p * 255, val * 255, t * 255);
	case 3: return sf::Color(p * 255, q * 255, val * 255);
	case 4: return sf::Color(t * 255, p * 255, val * 255);
	case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}*/

class Entity {
public:

	sf::Shape 	*sprite = nullptr; // pour le rendu
	sf::IntRect		*box;//pour les collisions
	Entity(sf::Shape *forme, sf::Vector2f Pos) {
		this->sprite = forme;
		this->sprite->setPosition(Pos.x, Pos.y);

		auto coll = new IntRect(Pos.x, Pos.y, forme->getLocalBounds().width, forme->getLocalBounds().height);
		this->box = coll;
	}

	~Entity()
	{

	}
	void _draw(sf::RenderWindow &win) {
		win.draw(*sprite);
	}

	void _addforce(Vector2f dir, float spd) {

		auto angle = atan2(dir.x - rec->getPosition().x, dir.y - rec->getPosition().y);

		sprite->setPosition((sprite->getPosition().x + angle)*spd, (sprite->getPosition().y - angle) *spd);
	}

};

static Entity *meuble[3];

static Entity *proj[5];


static void initRec()
{
	rec = new RectangleShape(Vector2f(16, 16));
	rec->setOrigin(16, 16);
	rec->setPosition(shPos.x = 400, shPos.y = 400);
	rec->setFillColor(sf::Color(0xFF95D0ff));
	rec->setOutlineColor(sf::Color(0xFFBB4Dff));
	rec->setOutlineThickness(2);

	circ = new CircleShape(8.f);
	circ->setOrigin(8, 8);
	circ->setPosition(circPos.x = 600, circPos.y = 600);
	circ->setFillColor(sf::Color(0x4EEB83ff));
	circ->setOutlineColor(sf::Color(0x000000ff));
	circ->setOutlineThickness(1);
}

static void drawMovingRec(sf::RenderWindow &win)
{
	if (rec == nullptr) rec = new sf::RectangleShape(Vector2f(16, 16));
	rec->setOrigin(16, 16);
	rec->setFillColor(sf::Color(0xFF95D0ff));
	rec->setOutlineColor(sf::Color(0xFFBB4Dff));
	rec->setOutlineThickness(2);
	win.draw(*rec);

	if (circ == nullptr) circ = new sf::CircleShape(8.f);
	circ->setOrigin(8, 8);
	circ->setFillColor(sf::Color(0x4EEB83ff));
	circ->setOutlineColor(sf::Color(0x000000ff));
	circ->setOutlineThickness(1);
	win.draw(*circ);

	
}

CircleShape *initCircShape(float r) {
	auto _circle = new CircleShape(r);
	return _circle;
}

RectangleShape *initRecShape(int x, int y) {
	auto _rectangle = new RectangleShape(Vector2f(x, y));
	return _rectangle;
}


static void initEntities() {
	meuble[0] = new Entity(initRecShape(10,10), Vector2f(0,0));
	meuble[0]->sprite->setScale(8, 8);
	meuble[0]->sprite->setFillColor(sf::Color(0xEB78FFff));	

	meuble[1] = new Entity(initRecShape(10, 10), Vector2f(800, 500));
	meuble[1]->sprite->setScale(8, 8);
	meuble[1]->sprite->setFillColor(sf::Color(0xEB78FFff));

	meuble[2] = new Entity(initRecShape(10, 10),Vector2f(100,100));
	meuble[2]->sprite->setScale(8, 8);
	meuble[2]->sprite->setFillColor(sf::Color(0xEB78FFff));

	for (int i = 0; i < 11; i++) {
		proj[i] = new Entity(initCircShape(5), Vector2f(rec->getPosition().x, rec->getPosition().y));
		proj[i]->sprite->setFillColor(sf::Color::Red);
	}
}

static void drawEntities(sf::RenderWindow &win) {
	if (meuble == nullptr) initEntities();

	for (int i = 0; i <3; i++) {
		meuble[i]->_draw(win);		
	}	
}

void launchProj(sf::RenderWindow &win) {
	auto angle = atan2(sf::Mouse::getPosition().x - rec->getPosition().x, sf::Mouse::getPosition().y - rec->getPosition().y);

	proj[0]->_draw(win);
}


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;

	sf::RenderWindow window(sf::VideoMode(1240, 720), "SFML works!", sf::Style::Default, settings); //taille de la fenêtre
	window.setVerticalSyncEnabled(true);
	/*sf::CircleShape shape(200.f);  //forme
	shape.setFillColor(sf::Color(0xFF8C71ff));  //couleur
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color(0xE8AE5Aff));*/

	

	sf::Clock clock;

	sf::Time displayDuration = clock.getElapsedTime();

	sf::Time appstart = clock.getElapsedTime();
	sf::Time frameStart = clock.getElapsedTime();
	sf::Time prevFrameStart = clock.getElapsedTime();


	float fps[4] = { 0.f,0.f ,0.f ,0.f };
	int step = 0;

	char fpslabel[64];

	sf::Font MyFont;
	MyFont.loadFromFile("arial.ttf");

	// Chargement à partir d'un fichier sur le disque

	if (!MyFont.loadFromFile("arial.ttf"))
	{
		// Erreur...
	}

	sf::Text myFPScounter;
	myFPScounter.setFont(MyFont);
	sf::Text myMousePos;
	myMousePos.setFont(MyFont);
	sf::Text myJoystick;
	myJoystick.setFont(MyFont);

	sf::Mouse myMouse;
	
	int every = 0;	

	initRec();
	initEntities();

	/*auto recbounds = rec->getGlobalBounds();
	auto recbounds2 = meuble[1]->sprite->getGlobalBounds();*/
	

	if (sf::Joystick::isConnected(0)) myJoystick.setString("Connected");

	while (window.isOpen())  // on passe tout le temps
	{
		sf::Event event; 
		frameStart = clock.getElapsedTime();		
		window.setMouseCursorVisible(false);
		if (every == 0)
		{
			myFPScounter.setString("FPS : " + std::to_string(fps[(step - 1) % 4]));
			myMousePos.setString("MousePos : " + std::to_string(myMouse.getPosition(window).x));
			myMousePos.setPosition(1000, 0);
		
		}
		while (window.pollEvent(event))  //met l'évènement en premier de la queue
		{
			switch (event.type)					
			{
			case sf::Event::KeyPressed:						
				
				if (event.key.code == sf::Keyboard::Q)
				{
					shPos.x -= squareSpeed;
					//shDir.x = -1;
					//shDir.y = 0;
				}
				if (event.key.code == sf::Keyboard::D) {
					shPos.x += squareSpeed;
					//shDir.x = 1;
					//shDir.y = 0;
				}
				if (event.key.code == sf::Keyboard::Z) {
					shPos.y -= squareSpeed;
					//shDir.x = 0;
					//shDir.y = -1;
				}
				if (event.key.code == sf::Keyboard::S) {
					shPos.y += squareSpeed;
					//shDir.x = 0;
					//shDir.y = 1;
				}

				if (event.key.code == sf::Keyboard::A) {
					launch = true;
				}
				break;

			case sf::Event::KeyReleased:
				/*if (event.key.code == sf::Keyboard::A) {
					launch = false;
				}*/
				break;
			//case sf::Event::JoystickMoved:

			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}

			Vector2f lastGoodPos = rec->getPosition();

			rec->setPosition(shPos);
			circ->setPosition(myMouse.getPosition(window).x, myMouse.getPosition(window).y);

			for( Entity * ent : meuble )
			{
				if (rec->getGlobalBounds().intersects(ent->sprite->getGlobalBounds()) == true) {
					printf("coll ");
					squareSpeed = 0;
					shPos.x = lastGoodPos.x;
					shPos.y = lastGoodPos.y;
					break;  
				}
				else
					squareSpeed = 30;
			}
	
			
			
		}

		if (launch == true) {
			proj[0]->_addforce(sf::Vector2f(myMouse.getPosition(window)), 1);
		}

		window.clear(); // nettoie la fenêtre
		
		//window.draw(myFPScounter); // on demande le dessin d'une forme
		//window.draw(myMousePos);
		drawEntities(window);

		window.draw(myJoystick);	
		drawMovingRec(window);

		sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(shPos.x, shPos.y)),
		sf::Vertex(sf::Vector2f(myMouse.getPosition(window).x, myMouse.getPosition(window).y))
		};

		window.draw(line, 2, sf::Lines);

		
		launchProj(window);
		

		window.display(); //dessine & attends la vsync

		fps[step % 4] = 1.0f/(frameStart - prevFrameStart).asSeconds();
		prevFrameStart = frameStart;

		

		step++;
	}
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
