#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <math.h>

using namespace sf;
using namespace std;

class Player
{
public:
	Player()
	{
		//Default constructor
	}
	Player(string imageName)
	{
		if (!playerTexture.loadFromFile(imageName))
			cerr << "Error" << endl;
		playerSprite.setTexture(playerTexture);
	}
	void drawPlayer(RenderWindow &screen)
	{
		playerSprite.setOrigin(playerSprite.getTexture()->getSize().x*0.5, playerSprite.getTexture()->getSize().y*0.5);
		playerSprite.setScale(0.25f, 0.25f);
		screen.draw(playerSprite);
	}
	void movePlayer(char direction, float moveSpeed)
	{
		if (direction == 'u')
		{
			playerSprite.move(sin(playerSprite.getRotation()*3.14159265 / 180)*-3, cos(playerSprite.getRotation()*3.14159265 / 180) * 3);
		}
		else
			if (direction == 'd')
			{
				playerSprite.move(sin(playerSprite.getRotation()*3.14159265 / 180) * 3, cos(playerSprite.getRotation()*3.14159265 / 180)*-3);
			}
			else
				if (direction == 'l')
				{
					playerSprite.rotate(1);
				}
				else
					if (direction == 'r')
					{
						playerSprite.rotate(-1);
					}
	}
private:
	Texture playerTexture;
	Sprite playerSprite;
};