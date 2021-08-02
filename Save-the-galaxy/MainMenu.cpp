#include "MainMenu.h"


MainMenu::MainMenu(float width, float height)
{

	if (!font.loadFromFile("Fonts\\ariblk.ttf")) {
		cout << "No font is here";
	}
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::White);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(50);
	mainMenu[0].setPosition(310, 100);

	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("Multiplayer");
	mainMenu[1].setCharacterSize(50);
	mainMenu[1].setPosition(280, 200);

	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setString("Option");
	mainMenu[2].setCharacterSize(50);
	mainMenu[2].setPosition(280, 300);

	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(Color::White);
	mainMenu[3].setString("About");
	mainMenu[3].setCharacterSize(50);
	mainMenu[3].setPosition(290, 400);

	mainMenu[4].setFont(font);
	mainMenu[4].setFillColor(Color::White);
	mainMenu[4].setString("Exit");
	mainMenu[4].setCharacterSize(50);
	mainMenu[4].setPosition(320, 500);

	MainMenuSelected = -1;
}
MainMenu::~MainMenu()
{

}
void MainMenu::draw(RenderWindow& window)
{
	for (int i = 0; i < Max_main_menu; ++i) {
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp()
{
	if (MainMenuSelected - 1 >= 0)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected--;
		if (MainMenuSelected == -1)
		{
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}
void MainMenu::MoveDown() {
	if (MainMenuSelected + 1 <= Max_main_menu)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected++;
		if (MainMenuSelected == 5)
		{
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}

