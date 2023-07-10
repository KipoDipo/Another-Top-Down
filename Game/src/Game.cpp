#include "Game.h"
#include <Entities/All.h>
#include <Utilities/All.h>
#include <Animation/All.h>
#include <UI/All.h>
#include <Particles/ParticleGenerator.h>

using namespace sf;
using namespace std;

vector<shared_ptr<Level>> Game::levels;
size_t Game::currentLevel = 0;
UI Game::ui;
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
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void Game::Init()
{
	srand((unsigned int)time(0));

	SingleAnimator atkAnims("ball/ball", 30);

	AnimateAnimator playerAnims(
		"player_up/player",
		"player_down/player",
		"player_left/player",
		"player_right/player",
		"player_down/player",
		12
	);
	AnimateAnimator enemyAnims("enemy/enemy", 12);
	BinaryAnimator solidAnims("solid/solid", 14);
	BinaryAnimator groundAnims("tiles", 14);

	BinaryAnimator sparkAnims("spark/spark", 10);
	sparkAnims.getSprite().setOrigin((Vector2f)sparkAnims.getSprite().getTexture()->getSize() / 2.f);

	BinaryAnimator guideAnims("guide", 1);

	RandomAnimator playerDeath({
			Animator::load("ball/ball", 10)
		});

	RandomAnimator enemyDeath({
			Animator::load("enemy/particles/var0/chunk", 8, true),
			Animator::load("enemy/particles/var1/chunk", 8, true)
		});

	shared_ptr<Level> testLevel = make_shared<Level>();

	testLevel->setPlayer({ 250, 250 }, 300.f, playerAnims, playerDeath, atkAnims);
	//Game::ui.setPlayer(Level::getPlayer());

	testLevel->addHostile({ 180, 30 }, rand() % 20 + 20.f, enemyAnims, enemyDeath);
	testLevel->addHostile({ 230, 100 }, rand() % 20 + 20.f, enemyAnims, enemyDeath);
	testLevel->addHostile({ 260, 60 }, rand() % 20 + 20.f, enemyAnims, enemyDeath);


	testLevel->addSolid({ 50, 0 }, solidAnims);
	testLevel->addSolid({ 50, 50 }, solidAnims);
	testLevel->addSolid({ 50, 100 }, solidAnims);
	testLevel->addSolid({ 50, 150 }, solidAnims);
	testLevel->addSolid({ 00, 200 }, solidAnims);
	testLevel->addSolid({ -50, 200 }, solidAnims);
	testLevel->addSolid({ -100, 200 }, solidAnims);


	for (int i = -3; i < 10; i++)
		for (int j = -3; j < 10; j++)
			testLevel->addGround({ j * 50.f, i * 50.f }, groundAnims);

	testLevel->addDecoration({ 0, 0 }, guideAnims);
	testLevel->addDecoration({ 0, 0 }, sparkAnims);

	testLevel->create();
	levels.push_back(testLevel);
	smoothCamera = Level::getPlayer().getCenter();

	shared_ptr<Health> uiHealth = make_shared<Health>(
		Vector2f(10, 10),
		Level::getPlayer(),
		BinarySmartAnimator(
			"health/full/anim", 30,
			"health/full/static", 30, true
		),
		SingleAnimator(
			"health/empty/anim", 15
		)
	);
	shared_ptr<FPSCounter> uiFps = make_shared<FPSCounter>("res/fonts/Pixeled.ttf", Vector2f(5, 50));

	Game::ui.addElement(uiHealth);
	Game::ui.addElement(uiFps);
}

void Game::Update()
{
	levels[currentLevel]->update();
	ui.update();
}

void Game::Draw()
{
	window.clear(Color(30, 20, 30));

	smoothCamera += ((Level::getPlayer().getCenter() - smoothCamera) * 2.f) * DeltaTime::get();

	View smoothView(Utils::roundedBySubdivions(smoothCamera, (int)zoom), (Vector2f)window.getSize() / zoom);
	window.setView(smoothView);

	window.draw(*levels[currentLevel]);
	window.draw(ui);

	window.display();
}
