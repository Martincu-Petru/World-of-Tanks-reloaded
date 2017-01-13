#pragma once
#include <iostream>
#include <math.h>
#include <SFML\Graphics.hpp>
#include "bullet.h"
#include "Player.h"
#include <stdlib.h>
# define M_PI  3.14159265358979323846

using namespace std;
using namespace sf;

class AI_Chaser
{
private:
	//don't know how to do with the chaser's shape
	Texture AI_ChaserTexture;
	Sprite AI_ChaserSprite;

	bool inMotion = false;

public:
	AI_Chaser()
	{
		// The constructor
	}
	AI_Chaser(string imageName, int ok)
	{
		//currentHealth = 100;
		//maxHealth = 100;
		if (!AI_ChaserTexture.loadFromFile(imageName))
			cerr << "Error" << endl;
		AI_ChaserTexture.setSmooth(true);
		AI_ChaserSprite.setTexture(AI_ChaserTexture);
		if (ok == 1)
		{
			AI_ChaserSprite.move(Vector2f(1000, 257.164));
			AI_ChaserSprite.setRotation(180);
		}
		else if (ok == 2)
		{
			AI_ChaserSprite.move(Vector2f(1000, 800));
			AI_ChaserSprite.setRotation(270);
		}
		else if (ok == 3)
		{
			AI_ChaserSprite.move(Vector2f(800, 600));
			AI_ChaserSprite.setRotation(90);
		}
	}
	void drawAI_Chaser(RenderWindow &screen, int ok)
	{
		AI_ChaserSprite.setOrigin(AI_ChaserSprite.getTexture()->getSize().x*0.5, AI_ChaserSprite.getTexture()->getSize().y*0.5);
		if (ok == 1)
		{
			AI_ChaserSprite.setScale(0.25f, 0.25f);
		}
		else if (ok == 2)
		{
			AI_ChaserSprite.setScale(0.15f, 0.15f);
		}
		else if (ok == 3)
		{
			AI_ChaserSprite.setScale(0.15f, 0.15f);
		}
		screen.draw(AI_ChaserSprite);
	}
	bool InSight(Player tank)
	{
		/*
		return true; if the tank is in the sight of the tank
		return false; otherwise
		What does it mean to be in sight? 
		it means the chaser can reach the tank in a straight line in a well defined range of pixels eg. 500
		*/
		return true;
	}
	float getXorigin()
	{
		return AI_ChaserSprite.getPosition().x;
	}
	float getYorigin()
	{
		return AI_ChaserSprite.getPosition().y;
	}
	float circleR(float xA, float yA)
	{
		float xB = AI_ChaserSprite.getPosition().x;
		float yB = AI_ChaserSprite.getPosition().y;

		return ((sqrt(pow(xB - xA, 2) + pow(yB - yA, 2))) / 2);
	}
	double squareL(float R)
	{
		return (R * sqrt(2));
	}
	float rotationOfChaser()
	{
		return AI_ChaserSprite.getRotation();
	}
	void moveChaser(char direction, float moveSpeed, int nr, Sprite obstacol[100])
	{
		if (direction == 'u')
		{
			AI_ChaserSprite.move(sin(AI_ChaserSprite.getRotation() * M_PI / 180.0) * -moveSpeed, cos(AI_ChaserSprite.getRotation() * M_PI / 180.0) * moveSpeed);
		}
		else
			if (direction == 'd')
			{
				AI_ChaserSprite.move(sin(AI_ChaserSprite.getRotation() * M_PI / 180.0) * moveSpeed, cos(AI_ChaserSprite.getRotation()* M_PI / 180.0) * -moveSpeed);
			}
			else
				if (direction == 'l')
				{
					AI_ChaserSprite.rotate(moveSpeed - 0.25);
				}
				else
					if (direction == 'r')
					{
						AI_ChaserSprite.rotate(-moveSpeed + 0.25);
					}
		/*if (direction == 'u')
		{
			float newSpeed = rand() % 1000; //marsarier
			newSpeed /= 100000;
			AI_ChaserSprite.move(sin(AI_ChaserSprite.getRotation()*3.14159265 / 180)*-(speed + newSpeed), cos(AI_ChaserSprite.getRotation()*3.14159265 / 180) * (speed + newSpeed));
			for (int i = 0; i <= nr; i++)
			{
				if (AI_ChaserSprite.getGlobalBounds().intersects(obstacol[i].getGlobalBounds()) && AI_ChaserSprite.getRotation() >= 270)
				{

					if (AI_ChaserSprite.getPosition().x < obstacol[i].getPosition().x) {
						AI_ChaserSprite.rotate(speed);
						AI_ChaserSprite.rotate(speed);
						AI_ChaserSprite.move(sin(AI_ChaserSprite.getRotation()*3.14159265 / 180) * (speed + newSpeed), cos(AI_ChaserSprite.getRotation()*3.14159265 / 180)*-(speed + newSpeed));
						break;
					}
					else
					{
						AI_ChaserSprite.rotate(-speed);
						AI_ChaserSprite.rotate(-speed);
						AI_ChaserSprite.move(sin(AI_ChaserSprite.getRotation()*3.14159265 / 180) * (speed + newSpeed), cos(AI_ChaserSprite.getRotation()*3.14159265 / 180)*-(speed + newSpeed));
						break;
					}
				}
			}

		}
		else
			if (direction == 'd') //merge in sus
			{
				float newSpeed = rand() % 1000;
				newSpeed /= 100000;
				AI_ChaserSprite.move(sin(AI_ChaserSprite.getRotation()*3.14159265 / 180) * (speed + newSpeed), cos(AI_ChaserSprite.getRotation()*3.14159265 / 180)*-(speed + newSpeed));
				for (int i = 0; i <= nr; i++)
					if (AI_ChaserSprite.getGlobalBounds().intersects(obstacol[i].getGlobalBounds()))
					{
						AI_ChaserSprite.rotate(-speed);
						AI_ChaserSprite.rotate(-speed);
						AI_ChaserSprite.move(sin(AI_ChaserSprite.getRotation()*3.14159265 / 180)*-(speed + newSpeed), cos(AI_ChaserSprite.getRotation()*3.14159265 / 180) * (speed + newSpeed));
						break;
					}
			}
			else
				if (direction == 'l') //merge in dreapta
				{
					AI_ChaserSprite.rotate(speed);
					for (int i = 0; i <= nr; i++)
						if (AI_ChaserSprite.getGlobalBounds().intersects(obstacol[i].getGlobalBounds()))
						{
							AI_ChaserSprite.rotate(-speed);
							AI_ChaserSprite.rotate(-speed);
							AI_ChaserSprite.move(sin(AI_ChaserSprite.getRotation()*3.14159265 / 180) * (speed), cos(AI_ChaserSprite.getRotation()*3.14159265 / 180)*-(speed));
							AI_ChaserSprite.move(sin(AI_ChaserSprite.getRotation()*3.14159265 / 180) * (speed), cos(AI_ChaserSprite.getRotation()*3.14159265 / 180)*-(speed));
							break;
						}

				}
				else
					if (direction == 'r')
					{
						AI_ChaserSprite.rotate(-speed);
						for (int i = 0; i <= nr; i++)
							if (AI_ChaserSprite.getGlobalBounds().intersects(obstacol[i].getGlobalBounds()))
							{

								AI_ChaserSprite.rotate(speed);
								AI_ChaserSprite.rotate(speed);
								AI_ChaserSprite.move(sin(AI_ChaserSprite.getRotation()*3.14159265 / 180) * (speed), cos(AI_ChaserSprite.getRotation()*3.14159265 / 180)*-(speed));
								break;
							}
					}*/
		if (AI_ChaserSprite.getPosition().y + AI_ChaserSprite.getGlobalBounds().height * 0.5 > VideoMode::getDesktopMode().height)
		{
			AI_ChaserSprite.setPosition(Vector2f(AI_ChaserSprite.getPosition().x, VideoMode::getDesktopMode().height - AI_ChaserSprite.getGlobalBounds().height*0.5));
		}
		if (AI_ChaserSprite.getPosition().x + AI_ChaserSprite.getGlobalBounds().width*0.5 > VideoMode::getDesktopMode().width)
		{
			AI_ChaserSprite.setPosition(VideoMode::getDesktopMode().width - AI_ChaserSprite.getGlobalBounds().width*0.5, AI_ChaserSprite.getPosition().y);
		}
		if (AI_ChaserSprite.getPosition().y - AI_ChaserSprite.getGlobalBounds().height*0.5 < 0)
		{
			AI_ChaserSprite.setPosition(Vector2f(AI_ChaserSprite.getPosition().x, AI_ChaserSprite.getGlobalBounds().height*0.5));
		}
		if (AI_ChaserSprite.getPosition().x - AI_ChaserSprite.getGlobalBounds().width*0.5 < 0)
		{
			AI_ChaserSprite.setPosition(Vector2f(AI_ChaserSprite.getGlobalBounds().width*0.5, AI_ChaserSprite.getPosition().y));

		}
	}
	bool isInMotion()
	{
		return inMotion;
	}
	void doNotRotate()
	{
		inMotion = true;
	}
	void rotate()
	{
		inMotion = false;
	}
	void goodPoint(float &x, float &y)
	{
		int r = AI_ChaserSprite.getGlobalBounds().height / 2;
		float xA = AI_ChaserSprite.getPosition().x;
		float yA = AI_ChaserSprite.getPosition().y;
		double rotation = AI_ChaserSprite.getRotation();

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
	double rotationNeeded(float xA, float yA)
	{
		float xC = AI_ChaserSprite.getPosition().x;
		float yC = AI_ChaserSprite.getPosition().y;
		double cosa = abs(yA - yC) / sqrt(pow(xC - xA, 2) + pow(yC - yA, 2));
		double a = acos(cosa);
		a = a * 180.0 / M_PI;
		if (xC < xA && yC < yA)
		{
			a = 180 - a;
		}
		else if (xC > xA && yC < yA)
		{
			a = 180 + a;
		}
		else if (xC > xA && yC > yA)
		{
			a = 360 - a;
		}
		return a;
	}
	float pathToPlayer(float xA, float yA)
	{
		float xC = AI_ChaserSprite.getPosition().x;
		float yC = AI_ChaserSprite.getPosition().y;

		return sqrt(abs(xC - xA) + abs(yC - yA));
	}
	bool checkIfIntersect(Sprite entity)
	{
		return (AI_ChaserSprite.getGlobalBounds().intersects(entity.getGlobalBounds()));
		//return (AI_ChaserSprite.getGlobalBounds().intersects())
	}
	void restart(int ok)
	{
		if (ok == 1)
		{
			AI_ChaserSprite.move(Vector2f(1000, 257.164));
			AI_ChaserSprite.setRotation(180);
		}
		else if (ok == 2)
		{
			AI_ChaserSprite.move(Vector2f(1000, 800));
			AI_ChaserSprite.setRotation(270);
		}
	}
};