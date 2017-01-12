#include "menu_exit.h"
#include <iostream>

using namespace std;


menu_exit::menu_exit()
{
	if (!textStyle.loadFromFile("Font.ttf"))
		cout << "Error loading font!";

	optiunea[0].setFont(textStyle);
	optiunea[0].setFillColor(Color::White);
	optiunea[0].setString("Are you sure you want to exit?");
	optiunea[0].setPosition(Vector2f(1366 / 4, 768 / 2 - 100));

	optiunea[1].setFont(textStyle);
	optiunea[1].setFillColor(Color::White);
	optiunea[1].setString("Yes");
	optiunea[1].setPosition(Vector2f(1366 / 4, 768 / 2 +100));

	optiunea[2].setFont(textStyle);
	optiunea[2].setFillColor(Color::Red);
	optiunea[2].setString("No");
	optiunea[2].setPosition(Vector2f(1366 / 4 * 3, 768 / 2 + 100));

	itemCurent = 0;
}


menu_exit::~menu_exit()
{
}

void menu_exit::draw(RenderWindow &screen)
{
	for (int i = 0; i < NO_MAX_ITEME; i++)
		screen.draw(optiunea[i]);
}

void menu_exit::moveLeft()
{
	if (itemCurent == 1)
	{
		optiunea[itemCurent].setFillColor(Color::White);
		itemCurent--;
		optiunea[itemCurent].setFillColor(Color::Red);
	}
}

void menu_exit::moveRight()
{
	if (itemCurent == 0)
	{
		optiunea[itemCurent].setFillColor(Color::White);
		itemCurent++;
		optiunea[itemCurent].setFillColor(Color::Red);
	}
}