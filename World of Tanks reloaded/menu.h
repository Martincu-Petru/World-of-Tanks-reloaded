#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;
#define NO_MAX_ITEME 4

class menu
{
public:
	menu();
	~menu();
	void draw(RenderWindow &menuScreen);
	void moveUp();
	void moveDown();
	int getPressedItem() { return itemCurent; }
private:
	int itemCurent;
	Font textStyle;
	Text optiunea[NO_MAX_ITEME];
};

