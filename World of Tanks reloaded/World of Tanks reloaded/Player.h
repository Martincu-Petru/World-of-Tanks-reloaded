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
		playerTexture.setSmooth(true);
		playerSprite.setTexture(playerTexture);
		playerSprite.move(Vector2f(40, 700));
	}
	void drawPlayer(RenderWindow &screen)
	{
		playerSprite.setOrigin(playerSprite.getTexture()->getSize().x*0.5, playerSprite.getTexture()->getSize().y*0.5);
		playerSprite.setScale(0.25f, 0.25f);
		screen.draw(playerSprite);
	}
	float getXorigin()
	{
		return playerSprite.getOrigin().x;
	}
	float getYorigin()
	{
		return playerSprite.getOrigin().y; 
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
		if (playerSprite.getPosition().y + playerSprite.getGlobalBounds().height*0.5 > VideoMode::getDesktopMode().height)
			playerSprite.setPosition(Vector2f(playerSprite.getPosition().x, VideoMode::getDesktopMode().height - playerSprite.getGlobalBounds().height*0.5));

		if (playerSprite.getPosition().x + playerSprite.getGlobalBounds().width*0.5 > VideoMode::getDesktopMode().width)
			playerSprite.setPosition(VideoMode::getDesktopMode().width - playerSprite.getGlobalBounds().width*0.5, playerSprite.getPosition().y);

		if (playerSprite.getPosition().y - playerSprite.getGlobalBounds().height*0.5 < 0)
			playerSprite.setPosition(Vector2f(playerSprite.getPosition().x, playerSprite.getGlobalBounds().height*0.5));

		if (playerSprite.getPosition().x - playerSprite.getGlobalBounds().width*0.5 < 0)
			playerSprite.setPosition(Vector2f(playerSprite.getGlobalBounds().width*0.5, playerSprite.getPosition().y));
	}
private:
	Texture playerTexture;
	Sprite playerSprite;
};