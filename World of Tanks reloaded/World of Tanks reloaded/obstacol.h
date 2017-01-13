#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;


class obstacol
{
public:
	obstacol()
	{

	}

	obstacol(string imageName)
	{
		currentHealth = 80;
		if (!crateTexture.loadFromFile(imageName))
			cerr << "Error" << endl;
		for (int i = 0; i < 100; i++)
			crateSprite[i].setTexture(crateTexture);
	}
	bool checkIfIntersect(Sprite entity,)
	{
		return (crateSprite[1].getGlobalBounds().intersects(entity.getGlobalBounds()));
	}
	int getHealth() {
		return currentHealth;
	}
private:
	int currentHealth;
	Sprite crateSprite[100];
	Texture crateTexture;
};

