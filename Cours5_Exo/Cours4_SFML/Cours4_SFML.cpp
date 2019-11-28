// Cours4_SFML.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include <Box2D/Box2D.h>

using namespace sf;

static RectangleShape *rec = nullptr;
static CircleShape *circ = nullptr;
static Vector2f shPos;
static Vector2f shDir;
static Vector2f circPos;

int squareSpeed = 3;

b2Vec2 gravity(0.f, -10.f);
b2World world(gravity);
b2Vec2 inter,normal;

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
	Vector2f dir;
	float x, y;
	bool isProj = false;

	b2BodyDef meubleBodydef;
	b2Body* meubleBody = world.CreateBody(&meubleBodydef);
	b2PolygonShape meubleBox;

	b2RayCastOutput output;
	b2RayCastInput input;
	b2Transform transform;
	int32 childIndex = 0;
	
	Entity(sf::Shape *forme, sf::Vector2f Pos, float angle, bool _isProj) {
		this->sprite = forme;
		this->sprite->setPosition(Pos.x, Pos.y);

		auto coll = new IntRect(Pos.x, Pos.y, forme->getLocalBounds().width, forme->getLocalBounds().height);
		this->box = coll;

		this->dir = Vector2f(cos(angle), sin(angle));
		this->isProj = _isProj;

		this->x = rec->getPosition().x;
		this->y = rec->getPosition().y;

		meubleBodydef.position.Set(Pos.x, Pos.y);
		meubleBox.SetAsBox(forme->getLocalBounds().width*0.5, forme->getLocalBounds().height*0.5);
		meubleBody->CreateFixture(&meubleBox, 0.f);

	}

	~Entity()
	{

	}
	void _draw(sf::RenderWindow &win) {
		win.draw(*sprite);
	}

	void move() {
		x += dir.x;
		y += dir.y;
		sprite->setPosition(x,y);
	}

	bool willCollide(Vector2f pos, Vector2f speed, Shape * other, b2Vec2 & inter, b2Vec2 & normal) {

		sf::FloatRect oBounds = other->getGlobalBounds();
		b2Transform transform;
		transform.SetIdentity();

		b2RayCastInput input;
		input.p1.Set(pos.x, pos.y);
		input.p2.Set(pos.x + speed.x, pos.y + speed.y);

		input.maxFraction = 1.0f;
		int32 childIndex = 0;
		b2RayCastOutput output;

		b2PolygonShape polyB;

		b2Vec2 center;
		center.x = oBounds.left + oBounds.width * 0.5f;
		center.y = oBounds.top + oBounds.height * 0.5f;

		b2Vec2 size;
		size.x = oBounds.width;
		size.y = oBounds.height;
		polyB.SetAsBox(size.x*0.5, size.y*0.5, center, 0.0f);

		bool hit = polyB.RayCast(&output, input, transform, childIndex);
		if (hit) {
			inter = input.p1 + output.fraction * (input.p2 - input.p1);
			normal = output.normal;
			return true;
		}
		return false;
	}

	/*if (willCollide) {
		b2Vec2 startToInter = inter - b2Vec2(p0.x, p0.y);
		b2Vec2 refl = startToInter - 2 * Lib::dot(startToInter, normal) * normal;
		b2Vec2 endRefl = inter + refl;
	}*/
	
};

static std::vector<Entity*> meuble;



static void initRec()
{
	rec = new RectangleShape(Vector2f(16, 16));
	rec->setOrigin(8, 8);
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
	/*if (rec == nullptr) rec = new sf::RectangleShape(Vector2f(16, 16));
	rec->setOrigin(16, 16);
	rec->setFillColor(sf::Color(0xFF95D0ff));
	rec->setOutlineColor(sf::Color(0xFFBB4Dff));
	rec->setOutlineThickness(2);*/
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
	auto meuble1 = new Entity(initRecShape(10,10), Vector2f(0,0),0,false);
	meuble1->sprite->setScale(8, 8);
	meuble1->sprite->setFillColor(sf::Color(0xEB78FFff));	
	meuble.push_back(meuble1);

	auto meuble2 = new Entity(initRecShape(10, 10), Vector2f(800, 500),0,false);
	meuble2->sprite->setScale(8, 8);
	meuble2->sprite->setFillColor(sf::Color(0xEB78FFff));
	meuble.push_back(meuble2);

	auto meuble3 = new Entity(initRecShape(10, 10),Vector2f(100,100),0,false);
	meuble3->sprite->setScale(8, 8);
	meuble3->sprite->setFillColor(sf::Color(0xEB78FFff));
	meuble.push_back(meuble3);

	
}

static void drawEntities(sf::RenderWindow &win) {

	for (int i = 0; i <meuble.size(); i++) {
		meuble[i]->_draw(win);		
	}	
}

void launchProj(sf::RenderWindow &win) {

	auto angle = atan2(sf::Mouse::getPosition(win).y - rec->getPosition().y, sf::Mouse::getPosition(win).x - rec->getPosition().x);
	
	auto proj = new Entity(initRecShape(4,4), Vector2f(rec->getPosition().x, rec->getPosition().y), angle,true);
	meuble.push_back(proj);
}


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;

	sf::RenderWindow window(sf::VideoMode(1240, 720), "SFML works!", sf::Style::Default, settings); //taille de la fenêtre
	window.setVerticalSyncEnabled(true);

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
					launchProj(window);
				}
				break;

			case sf::Event::KeyReleased:
				
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
					//printf("coll ");
					squareSpeed = 0;
					shPos.x = lastGoodPos.x;
					shPos.y = lastGoodPos.y;
					break;  
				}
				else
					squareSpeed = 5;
				
			}

		}

		window.clear(); // nettoie la fenêtre
		
		//window.draw(myFPScounter); // on demande le dessin d'une forme
		//window.draw(myMousePos);
		
		for (int i = 0; i < meuble.size(); i++)
		{		
			if (meuble[i]->isProj)
			{				
				meuble[i]->move();
			}
		}

		drawEntities(window);			
		

		sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(rec->getPosition())),
		sf::Vertex(sf::Vector2f(myMouse.getPosition(window).x, myMouse.getPosition(window).y))
		};
		window.draw(line, 2, sf::Lines);
		drawMovingRec(window);

		window.draw(myJoystick);

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
