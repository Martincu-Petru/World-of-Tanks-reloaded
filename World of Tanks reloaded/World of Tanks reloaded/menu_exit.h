#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;
#define NO_MAX_ITEME 2

class menu_exit
{
public:
	menu_exit();
	~menu_exit();
	void draw(RenderWindow &menuScreen);
	void moveLeft();
	void moveRight();
	int getPressedItem() { return itemCurent; }
private:
	int itemCurent;
	Font textStyle;
	Text optiunea[NO_MAX_ITEME];
};

