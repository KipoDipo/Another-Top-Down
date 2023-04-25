#include "Game.h"
#include "Entities/All.h"
#include "Utilities/All.h"
#include "Animation/Animation.h"

using namespace sf;
using namespace std;

RenderWindow Game::window;
vector<Level*> Game::levels;

void Game::Start(unsigned width, unsigned height, std::string title)
{
	window.create(sf::VideoMode(width, height), title);
	// * Initialize * //
	Font font;
	font.loadFromFile("res/fonts/Pixeled.ttf");
	Text loading("Loading...", font, 50);
	loading.setFillColor(Color::Black);
	loading.setOrigin(loading.getGlobalBounds().width / 2, loading.getGlobalBounds().height / 2);
	loading.setPosition((Vector2f)window.getSize() / 2.f);
	window.clear(Color::White);
	window.draw(loading);
	window.display();
	Init();
	DeltaTime::reset();
	while (window.isOpen())
	{
		// * Dispatch Events * //
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		// * Loop * //
		Update();
		Draw();
		DeltaTime::reset();
	}
}


// all of this needs to be out of here
Vector2f smoothCamera;
float zoom = 2.f;

Text text;
Font font;
Clock mclock;
float sumFps = 0;
int frames = 0;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void Game::Init()
{
	font.loadFromFile("res\\fonts\\Pixeled.ttf");

	text.setFont(font);
	text.setFillColor(Color::White);
	text.setCharacterSize(25);
	text.setString("FPS: wait");


	srand(time(0));
	Animations playerAnims;
	Animations enemyAnims;
	
	Animations otherAnims;

	playerAnims.add("player_idle/player", 0.1f, "player_idle");
	enemyAnims.add("enemy", 1.f, 0);
	
	otherAnims.add("ball", 1.f);
	otherAnims.add("defaultGround", 1.f, 1);
	otherAnims.add("solid/solid", 0.08f, 0);
	otherAnims.add("guide", 1.f);
	otherAnims.add("spark/spark", 0.1f, "spark");

	Level* testLevel = new Level();

	testLevel->setPlayer(Vector2f(250, 250), 300.f, playerAnims.get("player_idle"), otherAnims.get("ball"));

	testLevel->addHostile(Vector2f(180, 30), rand() % 20 + 20, enemyAnims.get(0));
	testLevel->addHostile(Vector2f(230, 100), rand() % 20 + 20, enemyAnims.get(0));
	testLevel->addHostile(Vector2f(260, 60), rand() % 20 + 20, enemyAnims.get(0));

	testLevel->addSolid(Vector2f(50, 0), otherAnims.get(0));
	testLevel->addSolid(Vector2f(50, 50), otherAnims.get(0));
	testLevel->addSolid(Vector2f(50, 100), otherAnims.get(0));
	testLevel->addSolid(Vector2f(50, 150), otherAnims.get(0));
	testLevel->addSolid(Vector2f(00, 200), otherAnims.get(0));
	testLevel->addSolid(Vector2f(-50, 200), otherAnims.get(0));
	testLevel->addSolid(Vector2f(-100, 200), otherAnims.get(0));

	for (int i = -3; i < 10; i++)
		for (int j = -3; j < 10; j++)
			testLevel->addGround(Vector2f(j * 50, i * 50), otherAnims.get(1));

	testLevel->addDecoration(Vector2f(0, 0), otherAnims.get("spark"));

	levels.push_back(testLevel);
	levels[levels.size() - 1]->create();

	smoothCamera = levels[levels.size() - 1]->getPlayer().getCenter();
}

void Game::Update()
{
	levels[0]->update();
}

void Game::Draw()
{



	window.clear(Color(30, 20, 30));

	smoothCamera += ((levels[0]->getPlayer().getCenter() - smoothCamera) * 2.f) * DeltaTime::get();
	View smoothView(Utils::roundedBySubdivions(smoothCamera, (int)zoom), (Vector2f)window.getSize() / zoom);
	window.setView(smoothView);



	window.draw(*levels[0]);

	// lord forgive me for this
	window.setView(window.getDefaultView());
	{
		window.draw(text);
		if (mclock.getElapsedTime().asSeconds() > 0.5f)
		{
			mclock.restart();
			text.setString("FPS: " + std::to_string((int)(sumFps / frames)));
			sumFps = frames = 0;
		}
		else
		{
			sumFps += 1.f / DeltaTime::get();
			frames++;
		}
		text.setPosition(Vector2f(5, 10));
	}
	window.setView(smoothView);


	window.display();
}
