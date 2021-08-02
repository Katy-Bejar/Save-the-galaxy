#pragma once

#include<map>
#include<string>
#include<sstream>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include"Player2.h"

class Game
{
private:
	//Window
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	unsigned points;

	//Player
	Player* player;
	Player2* playertwo;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//player two
	sf::RectangleShape playerHpBar2;
	sf::RectangleShape playerHpBarBack2;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI(int controller);
	void initWorld();
	void initSystems();

	void initPlayer(int controller);
	void initPlayer2();
	void initEnemies();


public:
	Game(int controller);
	virtual ~Game();

	//Functions
	void run();
	void run2();

	void updatePollEvents();
	void updateInput();
	void updateInput2();
	void updateGUI();
	void updateGUI2();
	void updateWorld();
	void updateCollision();
	void updateCollision2();
	void updateBullets();
	void updateEnemies();
	void updateEnemies2();
	void updateCombat();
	void update();
	void update2();

	void renderGUI();
	void renderWorld();
	void render();
	void render2();
};
