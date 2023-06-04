#include "Game.h"
#include <Entities/All.h>
#include <Utilities/All.h>

using namespace sf;
using namespace std;

vector<unique_ptr<Level>> Game::levels;
RenderWindow Game::window;

void Game::Start(unsigned width, unsigned height, const string& title)
{
	window.create(VideoMode(width, height), title);
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
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
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
	srand((unsigned int)time(0));

	font.loadFromFile("res\\fonts\\Pixeled.ttf");

	text.setFont(font);
	text.setFillColor(Color::White);
	text.setCharacterSize(25);
	text.setPosition(Vector2f(5, 10));
	text.setString("FPS: wait");

	GenericAnimator atkAnims("ball/ball", 30);
	AnimateAnimator playerAnims(
		"player_up/player", 
		"player_down/player",
		"player_left/player",
		"player_right/player",
		"player_down/player",
		12
	);
	AnimateAnimator enemyAnims("enemy", 12);
	InanimateAnimator solidAnims("solid/solid", 14);
	InanimateAnimator groundAnims("tiles", 1);
	
	InanimateAnimator sparkAnims("spark/spark", 10);
	sparkAnims.getSprite().setOrigin((Vector2f)sparkAnims.getSprite().getTexture()->getSize() / 2.f);

	InanimateAnimator guideAnims("guide", 1);

	GenericAnimator playerDeath("ball/ball", 10);
	GenericAnimator enemyDeath("ball/ball", 60);

	unique_ptr<Level> testLevel = make_unique<Level>();

	testLevel->setPlayer(Vector2f(250, 250), 300.f, playerAnims, playerDeath, atkAnims);
	
	testLevel->addHostile(Vector2f(180, 30), rand() % 20 + 20.f, enemyAnims, enemyDeath);
	testLevel->addHostile(Vector2f(230, 100), rand() % 20 + 20.f, enemyAnims, enemyDeath);
	testLevel->addHostile(Vector2f(260, 60), rand() % 20 + 20.f, enemyAnims, enemyDeath);


	testLevel->addSolid(Vector2f(50, 0), solidAnims);
	testLevel->addSolid(Vector2f(50, 50), solidAnims);
	testLevel->addSolid(Vector2f(50, 100), solidAnims);
	testLevel->addSolid(Vector2f(50, 150), solidAnims);
	testLevel->addSolid(Vector2f(00, 200), solidAnims);
	testLevel->addSolid(Vector2f(-50, 200), solidAnims);
	testLevel->addSolid(Vector2f(-100, 200), solidAnims);

	for (int i = -3; i < 10; i++)
		for (int j = -3; j < 10; j++)
			testLevel->addGround(Vector2f(j * 50.f, i * 50.f), groundAnims);

	testLevel->addDecoration(Vector2f(0, 0), guideAnims);
	testLevel->addDecoration(Vector2f(0, 0), sparkAnims);

	//for (int i = -3; i < 10; i++)
	//	for (int j = -3; j < 10; j++)
	//		if (rand() % 5 == 0)
	//			testLevel->addDecoration(Vector2f(j * 50.f, i * 50.f), sparkAnims);
	testLevel->create();
	levels.push_back(move(testLevel));
	smoothCamera = levels[levels.size() - 1]->getPlayer().getCenter();
	mclock.restart();
}
//GenericAnimator a("ball/ball", 30);
void Game::Update()
{
	//levels[0]->addParticles(ParticleGenerator::explosion(a, { 300,300 }, 100, 100, 10));
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
			text.setString("FPS: " + to_string((int)(sumFps / frames)));
			sumFps = 0;
			frames = 0;
		}
		else
		{
			sumFps += 1.f / DeltaTime::get();
			frames++;
		}
	}
	window.setView(smoothView);


	window.display();
}
