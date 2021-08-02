#include "Game.h"

//Private functions
//Inicializa la pantalla
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "SaveTheGalaxyFromCOVID-19", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

//Carga la textura de la municion
void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGUI(int controller)
{
	//Load font
	if (!this->font.loadFromFile("Fonts/arialbd.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	this->pointText.setPosition(360.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(80);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//Init player GUI Barra de vida player
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
	if (controller == 1) {
		
		//barra de vida player2
		this->playerHpBar2.setSize(sf::Vector2f(300.f, 25.f));
		this->playerHpBar2.setFillColor(sf::Color::Blue);
		this->playerHpBar2.setPosition(sf::Vector2f(480.f, 20.f));

		this->playerHpBarBack2 = this->playerHpBar2;
		this->playerHpBarBack2.setFillColor(sf::Color(25, 25, 25, 200));
	}
}
void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/fondo_juego.jpeg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer(int controller)
{
	this->player = new Player();
	this->player->setPosition(200, 500);
	if (controller == 1) {
		this->playertwo = new Player2();
		this->playertwo->setPosition(350, 450);
	}
}


void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

//Con/Des
Game::Game(int controller)
{
	this->initWindow();
	this->initTextures();
	this->initGUI(controller);
	this->initWorld();
	this->initSystems();

	this->initPlayer(controller);
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->playertwo;
	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
}

//Functions

//Mientras que el player tenga una vida >0 el juego seguira ejecutandose
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if (this->player->getHp() > 0)
			this->update();

		this->render();
	}
}

//Mientras que un player tenga una vida >0 el juego seguira ejecutandose
void Game::run2()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if (this->player->getHp() > 0 || this->playertwo->getHp() > 0)
			this->update2();

		this->render2();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f,
				this->player->getPos().y,
				0.f,
				-1.f,
				5.f
			)
		);
	}

}

void Game::updateInput2()
{
	//Move player1
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f,
				this->player->getPos().y,
				0.f,
				-1.f,
				5.f
			)
		);
	}
	//Move player2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		this->playertwo->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		this->playertwo->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		this->playertwo->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		this->playertwo->move(0.f, 1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && this->playertwo->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->playertwo->getPos().x + this->player->getBounds().width / 2.f,
				this->playertwo->getPos().y,
				0.f,
				-1.f,
				5.f
			)
		);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateGUI2()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));

	float hpPercent2 = static_cast<float>(this->playertwo->getHp()) / this->playertwo->getHpMax();
	this->playerHpBar2.setSize(sf::Vector2f(300.f * hpPercent2, this->playerHpBar2.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{	
	//Player su Hp>0 se redirecciona a la posicion 1000,1000
	if (this->player->getHp() <= 0)
	{
		this->player->setPosition(1000.f, 1000.f);
	}
	//Left world collision
	else if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 400)
	{
		this->player->setPosition(this->player->getBounds().left, 400);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}

	
	
}

void Game::updateCollision2()
{	
	//Player su Hp>0 se redirecciona a la posicion 1000,1000
	if (this->player->getHp() <= 0)
	{
		this->player->setPosition(1000.f, 1000.f);
	}
	//Left world collision
	else if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 400)
	{
		this->player->setPosition(this->player->getBounds().left, 400);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}

	////Player2 su Hp>0 se redirecciona a la posicion 1000,1000
	if (this->playertwo->getHp() <= 0) {
		this->playertwo->setPosition(1000.f, 1000.f);
	}
	//Left world collision
	else if (this->playertwo->getBounds().left <= 0.f)
	{
		this->playertwo->setPosition(0.f, this->playertwo->getBounds().top);
	}

	//Right world collison
	else if (this->playertwo->getBounds().left + this->playertwo->getBounds().width >= this->window->getSize().x)
	{
		this->playertwo->setPosition(this->window->getSize().x - this->playertwo->getBounds().width, this->playertwo->getBounds().top);
	}

	//Top world collision
	if (this->playertwo->getBounds().top < 400)
	{
		this->playertwo->setPosition(this->playertwo->getBounds().left, 400);
	}
	//Bottom world collision
	else if (this->playertwo->getBounds().top + this->playertwo->getBounds().height >= this->window->getSize().y)
	{
		this->playertwo->setPosition(this->playertwo->getBounds().left, this->window->getSize().y - this->playertwo->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//Enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}

		++counter;
	}
}

void Game::updateEnemies2()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//JUGABILIDAD COMPARTIDA DONDE LOS SI UNO ES ATACADO POR EL VIRUS CONTAGIA AL OTRO
		else if (enemy->getBounds().intersects(this->player->getBounds()) || enemy->getBounds().intersects(this->playertwo->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			this->playertwo->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//JUGABILIDAD INDEPENDIENTE
		/*else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		else if (enemy->getBounds().intersects(this->playertwo->getBounds()))
		{
			this->playertwo->loseHp(this->enemies.at(counter)->getDamage());

			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		*/
		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();

	this->updateWorld();
}

void Game::update2()
{
	this->updateInput2();

	this->player->update();
	
	this->playertwo->update();
	
	this->updateCollision2();

	this->updateBullets();

	this->updateEnemies2();

	this->updateCombat();

	this->updateGUI2();

	this->updateWorld();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);

	this->window->draw(this->playerHpBarBack2);
	this->window->draw(this->playerHpBar2);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0)
		this->window->draw(this->gameOverText);

	this->window->display();
}

void Game::render2()
{
	this->window->clear();

	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);
	this->playertwo->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0 && this->playertwo->getHp() <= 0)
		this->window->draw(this->gameOverText);

	this->window->display();
}
