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
		currentHealth = 100;
		maxHealth = 100;
		//speed = 0.5;//0.7;//0.05;
		speed = 0.9;//0.7;
		if (!playerTexture.loadFromFile(imageName))
			cerr << "Error" << endl;
		playerTexture.setSmooth(true);
		playerSprite.setTexture(playerTexture);
		playerSprite.move(Vector2f(40, 700));
	}
	bool checkIfIntersect(Sprite entity)
	{
		return (playerSprite.getGlobalBounds().intersects(entity.getGlobalBounds()));
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
	void movePlayer(char direction, int nr, Sprite obstacol[100])
	{
		//cazul tanc cu tunul in susul ecranului
		if (direction == 'u')
		{
			float newSpeed = rand() % 1000; //marsarier
			newSpeed /= 100000;
			playerSprite.move(sin(playerSprite.getRotation()*3.14159265 / 180)*-(speed+newSpeed), cos(playerSprite.getRotation()*3.14159265 / 180) * (speed+newSpeed));
			for(int i=0; i<=nr; i++)
				if (playerSprite.getGlobalBounds().intersects(obstacol[i].getGlobalBounds()))
				{
					playerSprite.rotate(speed);
					playerSprite.rotate(speed);
					playerSprite.move(sin(playerSprite.getRotation()*3.14159265 / 180) * (speed + newSpeed), cos(playerSprite.getRotation()*3.14159265 / 180)*-(speed + newSpeed));
					break;
				}

		}
		else
			if (direction == 'd') //merge in sus
			{
				float newSpeed = rand() % 1000;
				newSpeed /= 100000;
				playerSprite.move(sin(playerSprite.getRotation()*3.14159265 / 180) * (speed+newSpeed), cos(playerSprite.getRotation()*3.14159265 / 180)*-(speed+ newSpeed));
				for (int i = 0; i <= nr; i++)
					if (playerSprite.getGlobalBounds().intersects(obstacol[i].getGlobalBounds()))
					{
						playerSprite.rotate(-speed);
						playerSprite.rotate(-speed);
						playerSprite.move(sin(playerSprite.getRotation()*3.14159265 / 180)*-(speed + newSpeed), cos(playerSprite.getRotation()*3.14159265 / 180) * (speed + newSpeed));
						break;
					}
			}
			else
				if (direction == 'l') //merge in dreapta
				{
					playerSprite.rotate(speed);
					for (int i = 0; i <= nr; i++)
						if (playerSprite.getGlobalBounds().intersects(obstacol[i].getGlobalBounds()))
						{
							playerSprite.rotate(-speed);
							playerSprite.rotate(-speed);
							playerSprite.move(sin(playerSprite.getRotation()*3.14159265 / 180) * (speed), cos(playerSprite.getRotation()*3.14159265 / 180)*-(speed));
							playerSprite.move(sin(playerSprite.getRotation()*3.14159265 / 180) * (speed), cos(playerSprite.getRotation()*3.14159265 / 180)*-(speed));
							break;
						}

				}
				else
					if (direction == 'r')
					{
						playerSprite.rotate(-speed);
						for (int i = 0; i <= nr; i++)
							if (playerSprite.getGlobalBounds().intersects(obstacol[i].getGlobalBounds()))
							{

								playerSprite.rotate(speed);
								playerSprite.rotate(speed);
								playerSprite.move(sin(playerSprite.getRotation()*3.14159265 / 180) * (speed), cos(playerSprite.getRotation()*3.14159265 / 180)*-(speed));
								break;
							}
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
	float getSpeed()
	{
		return speed;
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
	void updateHealth()
	{
		if (!(currentHealth + rand() % 26 + 5 > maxHealth))
			currentHealth += rand() % 26 + 5;
		else
			currentHealth = maxHealth;
	}
	void lessHealth()
	{
		currentHealth -= rand() % 26 + 5;
		if (currentHealth <= 0)
			alive = false;
	} 
	bool checkIfAlive()
	{
		return alive;
	}
	void updateSpeed()
	{
		if (speed <= 0.2)
			speed += 0.03;
		cout << speed << endl;
	}
	void restart()
	{
		playerSprite.setPosition(Vector2f(40, 700));
		currentHealth = 100;
		speed = 0.05;
		playerSprite.setRotation(0);
	}
	void goodPoint(float &x, float &y)
	{
		int r = playerSprite.getGlobalBounds().height / 2;
		float xA = playerSprite.getPosition().x;
		float yA = playerSprite.getPosition().y;
		double rotation = playerSprite.getRotation();

		float cosT = cos(rotation * 3.14159265 / 180.0);
		float c = r * abs(cosT);
		if (0 <= rotation && rotation <= 90 || 270 <= rotation && rotation < 360)
		{
			y = yA - c;
		}
		else
		{
			y = yA + c;
		}
		x = sqrt(r * r - (yA - y) * (yA - y)) + xA;
		if (rotation > 180)
		{
			x = xA - sqrt(r * r - (yA - y) * (yA - y));
		}
		else if (rotation == 90)
		{
			x = xA + r;
			y = yA;
		}
		else if (rotation == 270)
		{
			y = yA;
			x = xA + r;
		}
	}
private:
	Texture playerTexture;
	Sprite playerSprite;
	int currentHealth;
	int maxHealth;
	Time lastHit;
	float speed;
	bool alive = true;
}; 