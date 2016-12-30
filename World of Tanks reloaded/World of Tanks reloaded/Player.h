#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

float rotation;

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
			playerSprite.move(0, -moveSpeed);
		else
			if (direction == 'd')
				playerSprite.move(0, moveSpeed);
			else
				if (direction == 'l')
				{
					playerSprite.rotate(1);
					//playerSprite.move(-moveSpeed, 0);
				}
				else
					if (direction == 'r')
					{
						playerSprite.rotate(-1);
						//playerSprite.move(moveSpeed, 0);
					}
	}
private:

	Texture playerTexture;
	Sprite playerSprite;
};