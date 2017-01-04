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
		currentHealth = 45;
		maxHealth = 100;
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
		return playerSprite.getPosition().x;
	}
	float getYorigin()
	{
		return playerSprite.getPosition().y;
	}
	void movePlayer(char direction, float moveSpeed)
	{
		if (direction == 'u')
		{
			playerSprite.move(sin(playerSprite.getRotation()*3.14159265 / 180)*-moveSpeed, cos(playerSprite.getRotation()*3.14159265 / 180) * moveSpeed);
		}
		else
			if (direction == 'd')
			{
				playerSprite.move(sin(playerSprite.getRotation()*3.14159265 / 180) * moveSpeed, cos(playerSprite.getRotation()*3.14159265 / 180)*-moveSpeed);
			}
			else
				if (direction == 'l')
				{
					playerSprite.rotate(moveSpeed-0.25);
				}
				else
					if (direction == 'r')
					{
						playerSprite.rotate(-moveSpeed+0.25);
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
	int getHealth() {
		return currentHealth;
	}
	Time getLastHitTime() {
		return lastHit;
	}
	bool hit(Time timeHit)
	{
		if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > 200)
		{
			lastHit = timeHit;
			currentHealth -= 10;
			return true;
		}
		else
		{
			return false;
		}
	}
	unsigned int xMaxim()
	{
		return VideoMode::getDesktopMode().width;
	}
	unsigned int yMaxim()
	{
		return VideoMode::getDesktopMode().height;
	}
	float rotationOfPlayer()
	{
		return playerSprite.getRotation();
	}
private:
	Texture playerTexture;
	Sprite playerSprite;
	int currentHealth;
	int maxHealth;
	Time lastHit;
}; 