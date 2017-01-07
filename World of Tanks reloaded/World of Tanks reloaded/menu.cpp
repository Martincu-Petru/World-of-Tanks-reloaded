#include "menu.h"
#include <iostream>

using namespace std;


menu::menu()
{
	if (!textStyle.loadFromFile("Font.ttf"))
		cout << "Error loading font!";

	optiunea[0].setFont(textStyle);
	optiunea[0].setFillColor(Color::Red);
	optiunea[0].setString("Play");
	optiunea[0].setPosition(Vector2f(1366 / 3+100, 768 / 5 * 1+200));

	optiunea[1].setFont(textStyle);
	optiunea[1].setFillColor(Color::White);
	optiunea[1].setString("Options");
	optiunea[1].setPosition(Vector2f(1366 / 3+100, 768 / 5 * 1.5+200));

	optiunea[2].setFont(textStyle);
	optiunea[2].setFillColor(Color::White);
	optiunea[2].setString("How to play?");
	optiunea[2].setPosition(Vector2f(1366 / 3+100, 768 / 5 * 2+200));

	optiunea[3].setFont(textStyle);
	optiunea[3].setFillColor(Color::White);
	optiunea[3].setString("Exit");
	optiunea[3].setPosition(Vector2f(1366 / 3+100, 768 / 5 * 2.5+200));

	itemCurent = 0;
}

menu::~menu()
{
}

void menu::draw(RenderWindow &screen)
{
	//Texture menuTexture;
	//Sprite menuBackground;
	//menuTexture.loadFromFile("menu.png");
	//menuBackground.setTexture(menuTexture);
	////menuBackground.setPosition(0, 0);
	for (int i = 0; i < NO_MAX_ITEME; i++)
		screen.draw(optiunea[i]);
}

void menu::moveUp()
{
	if (itemCurent - 1 >= 0)
	{
		optiunea[itemCurent].setFillColor(Color::White);
		itemCurent--;
		optiunea[itemCurent].setFillColor(Color::Red);
	}
}

void menu::moveDown()
{
	if (itemCurent + 1 < NO_MAX_ITEME)
	{
		optiunea[itemCurent].setFillColor(Color::White);
		itemCurent++;
		optiunea[itemCurent].setFillColor(Color::Red);
	}
}