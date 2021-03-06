// Cours4_SFML.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Lib.hpp"

using namespace sf;

Vector2f f1;
Vector2f f2;
Vector2f f3;
Vector2f f4;
Vector2f f5;
Vector2f f6;
Vector2f f7;
Vector2f f8;

static RectangleShape *rec = nullptr;
static Vector2f shPos;
static Vector2f shDir;

static sf::Shader * simpleshader = nullptr;
static sf::Shader * redshader = nullptr;
static sf::Shader * blurshader = nullptr;
static sf::Shader * bloomshader = nullptr;

static sf::Texture * whitetext = nullptr;
static sf::Texture * texture = nullptr;

const int squareSpeed = 3;

static sf::Transform s_Initial;
static std::vector<sf::Transform> s_Trs;

static bool _changeColor = false;
class Turtle : public sf::ConvexShape
{
public:

	sf::Transform m_Trs;

	Turtle() : sf::ConvexShape(3) {
		setFillColor(sf::Color(0xCCFFDEff));
		setOutlineThickness(2);
		setOutlineColor(sf::Color(0xFF0200ff));

		setPoint(0, Vector2f(0, -24));
		setPoint(1, Vector2f(-16, 16));
		setPoint(2, Vector2f(16, 16));
	}
	void setTransform(sf::Transform trs) {
		m_Trs = trs;
	}
};

static std::vector<Turtle*> _turtle;

float lerp(float a, float b, float r) {
	return a + (b - a) * r;
}

float rd() {
	return 1.0 * rand() / RAND_MAX;
}

sf::Color hsv(int hue, float sat, float val)
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
}


void drawCurve(sf::RenderWindow &win, float now)
{
	sf::VertexArray va(sf::LineStrip);
	sf::Color red = sf::Color::Red;
	sf::Color blue = sf::Color::Blue;
	float nb = 100.0f;
	float stride = 1200.0 / nb;

	int ofsX = 0;

	//X = 0 1 2 3 4 5 6 

	//X mod 2

	//0 1 0 1 0 1 0 1

	/*if (fmodf(now, 2.0) <= 1.0 ){
		red.a = 0;
	}*/
	//// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f 
	

	for (int i = 0; i < nb + now * 10; ++i) {
		double ratio = 1.0 * i / nb;
		double x = ofsX + stride * i;
		double y = 400;
		sf::Color c;

		//c = i % 2 == 0 ? blue : red;

		c = hsv(ratio * 360, 0.8, 0.8);
		
		y += sin(ratio*8.0 + now * 3.0) * 120;

		sf::Vertex vertex(Vector2f (x-now*10, y), c);

		va.append(vertex);
	}
	win.draw(va);
}


void drawCatmull(sf::RenderWindow &win, float now) {
	sf::VertexArray va(sf::LineStrip);
	sf::Color red = sf::Color::Red;
	sf::Color blue = sf::Color::Blue;

	sf::CircleShape pastille(16.f);
	pastille.setOrigin(Vector2f(16, 16));
	pastille.setFillColor(sf::Color(0xFFFFFF00));
	pastille.setOutlineThickness(2);
	pastille.setOutlineColor(sf::Color::Red);

	
	int nb = 320;
	float stride = 1280.0 / nb;
	

	std::vector<Vector2f> points;

	for (int j = 0; j < 8; ++j) {
		/*Vector2f v(j * 100, j * 100);
		if (j == 0)v.x += 100;
		if (j == 3)v.x += 200;
		points.push_back(v);*/			
	}

	points.push_back(f1);
	points.push_back(f2);
	points.push_back(f3);
	points.push_back(f4);
	points.push_back(f5);
	points.push_back(f6);
	points.push_back(f7);
	points.push_back(f8);
	

	for (int i = 0; i < nb + 1; ++i) {
		double ratio = 1.0 * i / nb;
		double x = 0.0;
		double y = 0.0;
		sf::Color c = hsv(ratio * 360, 0.8, 0.8);

		Vector2f pos = Lib::plot2(ratio, points);
		x = pos.x;
		y = pos.y;

		sf::Vertex vertex(Vector2f(x, y), c);
		va.append(vertex);		

		
	}

	Vector2f pos = Lib::plot2(fmodf(now,3.0)/3.0, points);
	pastille.setPosition(pos.x, pos.y);

	win.draw(va);
	win.draw(pastille);
}

static void initRec()
{
	rec = new RectangleShape(Vector2f(16, 16));
	rec->setOrigin(16, 16);
	rec->setPosition(shPos.x = 400, shPos.y = 400);
	rec->setFillColor(sf::Color(0xFF95D0ff));
	rec->setOutlineColor(sf::Color(0xFFBB4Dff));
	rec->setOutlineThickness(2);
}

static void drawMovingRec(sf::RenderWindow &win)
{
	if (rec == nullptr) rec = new sf::RectangleShape(Vector2f(16, 16));
	rec->setOrigin(16, 16);
	rec->setFillColor(sf::Color(0xFF95D0ff));
	rec->setOutlineColor(sf::Color(0xFFBB4Dff));
	rec->setOutlineThickness(2);
	win.draw(*rec);
}

static void startTransform() {
	s_Initial = Transform::Identity;
	s_Initial.translate(600, 360);
	s_Initial.rotate(90);
}

static void translateX(float dx) {
	sf::Transform res;
	res.translate(dx, 0);
	s_Trs.push_back(res);
}

static void translateY(float dy) {
	sf::Transform res;
	res.translate(0, dy);
	s_Trs.push_back(res);
}

static void rotate(float degrees) {
	sf::Transform res;
	res.rotate(degrees);
	s_Trs.push_back(res);
}

static void scaleXY(float dx, float dy) {
	sf::Transform res;
	res.scale(dx, dy);
	s_Trs.push_back(res);
}

static void scaleXY(float dxy) {
	sf::Transform res;
	res.scale(dxy, dxy);
	s_Trs.push_back(res);
}

static void scaleX(float dx) {
	sf::Transform res;
	res.scale(dx, 0);
	s_Trs.push_back(res);
}

static void scaleY(float dy) {
	sf::Transform res;
	res.scale(0, dy);
	s_Trs.push_back(res);
}


static void computeTransform(sf::Transform & results, int step =-1) {
	sf::Transform inter;

	inter.combine(s_Initial);

	if (step <= -1) {
		for (sf::Transform t : s_Trs) {
			inter = inter.combine(t);
		}
	}
	else {
		step--;
		for (sf::Transform t : s_Trs) {
			inter = inter.combine(t);
			if (step <= 0)break;
		}
	}
	results = inter;
}

void plotTurtle()
{
	sf::Transform cur;
	computeTransform(cur, s_Trs.size() - 1);
	Turtle* t = new Turtle();
	t->setTransform(cur);
	t->setFillColor(_changeColor == true ? Color(0xFF0000ff) : Color(0x0116FFff));
	_changeColor = !_changeColor;
	_turtle.push_back(t);	
}


bool startsWith(const char * s0, const char * s1) {
	if (*s0 == 0 && *s1 != 0)
		return false;
	if (*s1 == 0)
		return true;
	if (*s0 != *s1)
		return false;
	else
		return startsWith(s0 + 1, s1 + 1);
}

enum TurtleCommand {
	AV,
	REC,
	GROSSI,
	RET,
	L45,
	R45,
	COLOR_R,
	COLOR_B,
};
static std::vector<TurtleCommand> cmd;

static char data[1024];
static void readScript() {
	FILE * f = nullptr;
	auto err = fopen_s(&f,"res/scriptTortue.txt", "r");
	if (f != nullptr) {
		memset(data, 0, 1024);
		fread(data, 2014, 1, f);
		printf("read file %s\n", data);
		fclose(f);
	}
	else {
		printf("cannot read txt file");
	}

	char *cur = data;
	bool doContinue = true;
	while (doContinue)
	{
		if (*cur == 0 || cur ==nullptr) break;
		else {
			if (startsWith(cur, "AV")) {
				cmd.push_back(AV);
			}
			if (startsWith(cur, "REC")) {
				cmd.push_back(REC);
			}
			if (startsWith(cur, "GROSSI")) {
				cmd.push_back(GROSSI);
			}

			if (startsWith(cur, "RET")) {
				cmd.push_back(RET);
			}

			if (startsWith(cur, "L45")) {
				cmd.push_back(L45);
			}
			if (startsWith(cur, "R45")) {
				cmd.push_back(R45);
			}
			if (startsWith(cur, "CR")) {
				cmd.push_back(COLOR_R);
			}
			if (startsWith(cur, "CB")) {
				cmd.push_back(COLOR_B);
			}
			cur = strstr(cur, " ");
			if (!cur) {
				break;
			}
			else cur++;
		}
	}
}

int main()
{
	std::cout << "Hello World!\n";
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;

	sf::RenderWindow window(sf::VideoMode(1240, 720), "SFML works!", sf::Style::Default, settings); //taille de la fenêtre
	window.setVerticalSyncEnabled(true);
	sf::CircleShape shape(200.f);  //forme
	shape.setFillColor(sf::Color(0xFF8C71ff));  //couleur
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color(0xE8AE5Aff));

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

	if (!sf::Shader::isAvailable()) printf("no shader");

	simpleshader = new Shader();
	if (!simpleshader->loadFromFile("res/simple.vert", "res/simple.frag")) printf("unable to load shaders");

	whitetext = new Texture();
	if (!whitetext->create(1, 1)) printf("tex crea failed");
	whitetext->setSmooth(true);
	unsigned int col = 0xfffffffff;
	whitetext->update((const sf::Uint8*)&col, 1, 1, 0, 0);

	//if (!redshader->loadFromFile("res/red.frag") printf("unable to load shaders"));

	// Chargement à partir d'un fichier sur le disque

	if (!MyFont.loadFromFile("arial.ttf"))
	{
		// Erreur...
	}

	sf::Text myFPScounter;
	myFPScounter.setFont(MyFont);
	sf::Text myMousePos;
	myMousePos.setFont(MyFont);

	sf::Mouse myMouse;
	
	int every = 0;	

	initRec();
	readScript();


	while (window.isOpen())  // on passe tout le temps
	{
		sf::Event event; 
		frameStart = clock.getElapsedTime();
		
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
				if (event.key.code == sf::Keyboard::E)
				{
					printf("react time enter : %f\n", displayDuration.asMilliseconds());
					sf::String text("bjr");
				}
				if (event.key.code == sf::Keyboard::C)
				{
					printf("curTime : %f\n", frameStart.asSeconds());
				}
				if (event.key.code == sf::Keyboard::F)
				{
					printf("fps %f\n", 0.25f*(fps[0] + fps[1] + fps[2] + fps[3])); //moyenne des 4 derniers fps
				}

				if (event.key.code == sf::Keyboard::P)
				{
						printf("instant fps %f\n", fps[(step - 1) % 4]);  //fps instantané
				}

				
				if (event.key.code == sf::Keyboard::Left)
				{
					shPos.x -= squareSpeed;
					shDir.x = -1;
					shDir.y = 0;
				}
				if (event.key.code == sf::Keyboard::Right) {
					shPos.x += squareSpeed;
					shDir.x = 1;
					shDir.y = 0;
				}
				if (event.key.code == sf::Keyboard::Up) {
					shPos.y -= squareSpeed;
					shDir.x = 0;
					shDir.y = -1;
				}
				if (event.key.code == sf::Keyboard::Down) {
					shPos.y += squareSpeed;
					shDir.x = 0;
					shDir.y = 1;
				}

				
				break;

			case sf::Event::KeyReleased: {
				if (event.key.code == sf::Keyboard::Space) {
					startTransform();

					sf::Transform trs;
					computeTransform(trs);

					for (Turtle*t : _turtle) delete t;
					_turtle.clear();

					Turtle* t = new Turtle();
					t->setTransform(trs);
					_turtle.push_back(t);
				}

				auto delta = 32;

				if (event.key.code == sf::Keyboard::Up) { translateY(-delta);	   plotTurtle(); }
				if (event.key.code == sf::Keyboard::Down) { translateY(delta);	   plotTurtle(); }

				if (event.key.code == sf::Keyboard::Left) { rotate(-45);			   plotTurtle(); }
				if (event.key.code == sf::Keyboard::Right) { rotate(45);			   plotTurtle(); }

				if (event.key.code == sf::Keyboard::Add) { scaleXY(2.0);			   plotTurtle(); }
				if (event.key.code == sf::Keyboard::Subtract) { scaleXY(0.5);			   plotTurtle(); }

				if (event.key.code == sf::Keyboard::F2) {
					for (TurtleCommand tc : cmd) {
						switch (tc)
						{
						case AV:
							translateY(-delta);	   plotTurtle();
							break;
						case REC:
							translateY(delta);	   plotTurtle();
							break;
						case GROSSI:
							scaleXY(10.0);			   plotTurtle();
							break;

						case RET:
							scaleXY(0.1);			   plotTurtle();
							break;

						case L45:
							rotate(-45);			   plotTurtle();
							break;
						case R45:
							rotate(45);			   plotTurtle();
							break;
						case COLOR_B:
								   plotTurtle();
							break;
						case COLOR_R:
								   plotTurtle();
							break;

						default:
							break;
						}

					}
				}

				break; 
			}
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}

			rec->setPosition(shPos);
		}


		window.clear(); // nettoie la fenêtre
		
		window.draw(myFPScounter); // on demande le dessin d'une forme
		/*window.draw(myMousePos);
		drawMovingRec(window);
		drawCurve(window, clock.getElapsedTime().asSeconds());
		drawCatmull(window, clock.getElapsedTime().asSeconds());*/

		/*sf::RectangleShape sh(Vector2f(64, 64));
		sh.setPosition(50, 50);
		sh.setTexture(whitetext);
		simpleshader->setUniform("time", clock.getElapsedTime().asSeconds());
		window.draw(sh, simpleshader);*/

		for (Turtle*t : _turtle) {
			RenderStates rs;
			rs.transform = t->m_Trs;
			window.draw(*t,rs);
		}
	
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
