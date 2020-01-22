// Cours4_SFML.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include "Entity.hpp"
#include "Proj.hpp"

using namespace sf;

static RectangleShape *rec = nullptr;
static RectangleShape *rec2 = nullptr;
//static CircleShape *circ = nullptr;
static RectangleShape *canon = nullptr;
static RectangleShape *canon2 = nullptr;
static Vector2f shPos;
static Vector2f shDir;
static Vector2f circPos;

float angleVisee, angleVisee1;
float angle, angle1;
float Xjoy0 = 0, Yjoy0 = 0, Ujoy0 = 0, Vjoy0 = 0, Zjoy0 = 0; //J1
float Xjoy1 = 0, Yjoy1 = 0, Ujoy1 = 0, Vjoy1 = 0, Zjoy1 = 0; //J2

int squareSpeed = 3;

float JoySpeed = 0.1f;
bool shoot = false;

RectangleShape *initRecShape(float x, float y) {
	auto _rectangle = new RectangleShape(Vector2f(x, y));
	return _rectangle;
}

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


static std::vector<Entity*> meuble;
static std::vector<Proj*> _proj;




static void initChar()
{
#pragma region initChar1
	rec = new RectangleShape(Vector2f(16, 16));
	rec->setOrigin(8, 8);
	rec->setPosition(shPos.x = 400, shPos.y = 400);
	rec->setFillColor(sf::Color(0xFF95D0ff));
	rec->setOutlineColor(sf::Color(0xFFBB4Dff));
	rec->setOutlineThickness(2);

	canon = new RectangleShape(Vector2f(8, 24));
	canon->setOrigin(4, 4);
	canon->setPosition(shPos.x = 400, shPos.y = 400);
	canon->setRotation(90);
	canon->setFillColor(sf::Color(0x4EEB83ff));
	canon->setOutlineColor(sf::Color(0x000000ff));
	canon->setOutlineThickness(1);
#pragma endregion
	
#pragma region initChar2
	rec2 = new RectangleShape(Vector2f(16, 16));
	rec2->setOrigin(8, 8);
	rec2->setPosition(shPos.x = 600, shPos.y = 600);
	rec2->setFillColor(sf::Color::Red);
	rec2->setOutlineColor(sf::Color(0xFFBB4Dff));
	rec2->setOutlineThickness(2);

	canon2 = new RectangleShape(Vector2f(8, 24));
	canon2->setOrigin(4, 4);
	canon2->setPosition(shPos.x = 600, shPos.y = 600);
	canon2->setRotation(90);
	canon2->setFillColor(sf::Color::Blue);
	canon2->setOutlineColor(sf::Color(0x000000ff));
	canon2->setOutlineThickness(1);
#pragma endregion
	/*circ = new CircleShape(8.f);
	circ->setOrigin(-80, -80);
	circ->setPosition(shPos.x = 500, shPos.y = 400);
	circ->setFillColor(sf::Color(0x4EEB83ff));
	circ->setOutlineColor(sf::Color(0x000000ff));
	circ->setOutlineThickness(1);*/

	
}

static void drawChar(sf::RenderWindow &win, int player)
{
	/*if (rec == nullptr) rec = new sf::RectangleShape(Vector2f(16, 16));
	rec->setOrigin(16, 16);
	rec->setFillColor(sf::Color(0xFF95D0ff));
	rec->setOutlineColor(sf::Color(0xFFBB4Dff));
	rec->setOutlineThickness(2);*/
	

	/*if (circ == nullptr) circ = new sf::CircleShape(8.f);
	circ->setOrigin(rec->getPosition().x, rec->getPosition().y);
	circ->setFillColor(sf::Color(0x4EEB83ff));
	circ->setOutlineColor(sf::Color(0x000000ff));
	circ->setOutlineThickness(1);*/
	//win.draw(*circ);

	player == 0 ? win.draw(*rec), win.draw(*canon) : win.draw(*rec2), win.draw(*canon2);
	/*win.draw(*rec);
	win.draw(*canon);*/
	
}

static void initEntities() {
	auto meuble1 = new Entity(initRecShape(80.0f,80.0f), Vector2f(0,0));
	//meuble1->sprite->setOrigin(4, 4);
	meuble1->sprite->setFillColor(sf::Color(0xEB78FFff));	
	meuble.push_back(meuble1);

	auto meuble2 = new Entity(initRecShape(80.0f, 80.0f), Vector2f(800, 500));
	//meuble2->sprite->setOrigin(4, 4);
	meuble2->sprite->setFillColor(sf::Color(0xEB78FFff));
	meuble.push_back(meuble2);

	auto meuble3 = new Entity(initRecShape(80.0f, 80.0f),Vector2f(100,100));
	//meuble3->sprite->setOrigin(4, 4);
	meuble3->sprite->setFillColor(sf::Color(0xEB78FFff));
	meuble.push_back(meuble3);

	
}

static void drawEntities(sf::RenderWindow &win) {

	for (int i = 0; i <meuble.size(); i++) {
		meuble[i]->_draw(win);		
	}	

	for (int i = 0; i < _proj.size(); i++) _proj[i]->_draw(win);
}

void launchProj(sf::RenderWindow &win, int player) {

	auto proj = new Proj(initRecShape(4.0f,4.0f), Vector2f(rec->getPosition().x, rec->getPosition().y), angle, true);
	proj->sprite->setOrigin(2, 4);
	proj->sprite->setRotation(angle * 180 / 3.14159265359);
	_proj.push_back(proj);
	shoot = false;
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
	
	int every = 0;	

	initChar();
	initEntities();


	while (window.isOpen())  // on passe tout le temps
	{
		sf::Event event; 
		frameStart = clock.getElapsedTime();		
		window.setMouseCursorVisible(false);

		

		if (every == 0)
		{
			myFPScounter.setString("FPS : " + std::to_string(fps[(step - 1) % 4]));					
		
		}
		while (window.pollEvent(event))  //met l'évènement en premier de la queue
		{			
			
			switch (event.type)
			{

			case sf::Event::JoystickMoved:
				if (event.joystickMove.joystickId == 0){
					if (event.joystickMove.axis == sf::Joystick::X)
					{
						Xjoy0 = event.joystickMove.position;					
					}
					if (event.joystickMove.axis == sf::Joystick::Y) {												
						Yjoy0 = event.joystickMove.position;
					}
					if (event.joystickMove.axis == sf::Joystick::U)
					{
						Ujoy0 = event.joystickMove.position;
					}
					if (event.joystickMove.axis == sf::Joystick::V)
					{
						Vjoy0 = event.joystickMove.position;
					}
					if (event.joystickMove.axis == sf::Joystick::Z) {
						Zjoy0 = event.joystickMove.position;
					}
				}

				/*if (event.joystickMove.joystickId == 1) {
					if (event.joystickMove.axis == sf::Joystick::X)
					{
						Xjoy1 = event.joystickMove.position;
					}
					if (event.joystickMove.axis == sf::Joystick::Y) {
						Yjoy1 = event.joystickMove.position;
					}
					if (event.joystickMove.axis == sf::Joystick::U)
					{
						Ujoy1 = event.joystickMove.position;
					}
					if (event.joystickMove.axis == sf::Joystick::V)
					{
						Vjoy1 = event.joystickMove.position;
					}
					if (event.joystickMove.axis == sf::Joystick::Z) {
						Zjoy1 = event.joystickMove.position;
					}
				}*/
		
				break;

			

			case sf::Event::KeyPressed:						
				
				/*if (event.key.code == sf::Keyboard::Q )
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
				}*/
				break;

			case sf::Event::KeyReleased:
				
				break;

			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}

			float lastRot = canon->getRotation();
#pragma region deadzone

			if (Xjoy0 > 15 || Xjoy0 < -15) 
				shPos.x += Xjoy0 * JoySpeed;			

			if (Yjoy0 > 15 || Yjoy0 < -15)
				shPos.y += Yjoy0 * JoySpeed;

			if (Ujoy0 > 50 || Ujoy0 < -50 || Vjoy0 > 50 || Vjoy0 < -50) {	
				angle = atan2(Vjoy0, Ujoy0);
				angleVisee = atan2(Ujoy0, Vjoy0) * 180 / 3.14159265359;
			}
			else if (Ujoy0 == 0 || Vjoy0 == 0)
			{
				angleVisee = lastRot;
			}

			if (Zjoy0 > 80 || Zjoy0 < -80 && Zjoy0 != 100 && Zjoy0 != -100)
			{
				if (shoot == true)
					launchProj(window, 0);
			}
			
			if (Zjoy0 < 25 && Zjoy0 > -25) shoot = true;

			////////////////////////////////////

			/*if (Xjoy1 > 15 || Xjoy1 < -15)
				shPos.x += Xjoy1 * JoySpeed;

			if (Yjoy1 > 15 || Yjoy1 < -15)
				shPos.y += Yjoy1 * JoySpeed;

			if (Ujoy1 > 50 || Ujoy1 < -50 || Vjoy1 > 50 || Vjoy1 < -50) {
				angle1 = atan2(Vjoy1, Ujoy1);
				angleVisee1 = atan2(Ujoy1, Vjoy1) * 180 / 3.14159265359;
			}
			else if (Ujoy1 == 0 || Vjoy1 == 0)
			{
				angleVisee1 = lastRot;
			}

			if (Zjoy1 > 80 || Zjoy1 < -80 && Zjoy1 != 100 && Zjoy1 != -100)
			{
				if (shoot == true)
					launchProj(window, 1);
			}

			if (Zjoy1 < 25 && Zjoy1 > -25) shoot = true;*/
							

#pragma endregion			
			
			Vector2f lastGoodPos = rec->getPosition();			
		
			rec->setPosition(shPos);					

			canon->setPosition(shPos);
			canon->setRotation(-angleVisee);


			for (Entity * ent : meuble)
			{
				if (rec->getGlobalBounds().intersects(ent->sprite->getGlobalBounds()) == true) {
					JoySpeed = 0.f;
					shPos.x = lastGoodPos.x;
					shPos.y = lastGoodPos.y;
					break;
				}
				else
					JoySpeed = 0.1f;

			}
		}


		window.clear(); // nettoie la fenêtre
		
		window.draw(myFPScounter); // on demande le dessin d'une forme
		
		for (int i = 0; i < _proj.size(); i++)
		{	
			if (_proj[i]->isProj)
			{	
				_proj[i]->move();
			}			
			for (int j = 0; j < meuble.size(); j++) {

				if (i != j && _proj[i]->box.intersects(meuble[j]->box))
				{
					printf("coll");
					_proj[i]->coll(meuble[j]);
				}
			}
		}


		for (int i = 0; i < 2; i++)
			drawChar(window, i);
		
		drawEntities(window);			
		
	

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
