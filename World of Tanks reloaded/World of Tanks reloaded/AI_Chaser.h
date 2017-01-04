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
	AI_Chaser(string imageName)
	{
		//currentHealth = 100;
		//maxHealth = 100;
		if (!AI_ChaserTexture.loadFromFile(imageName))
			cerr << "Error" << endl;
		AI_ChaserTexture.setSmooth(true);
		AI_ChaserSprite.setTexture(AI_ChaserTexture);
		AI_ChaserSprite.move(Vector2f(1000, 80));
	}
	void drawAI_Chaser(RenderWindow &screen)
	{
		AI_ChaserSprite.setOrigin(AI_ChaserSprite.getTexture()->getSize().x*0.5, AI_ChaserSprite.getTexture()->getSize().y*0.5);
		AI_ChaserSprite.setScale(0.25f, 0.25f);
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
	void moveChaser(char direction, float moveSpeed)
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
					//cout << endl << " NUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU " << endl;
					AI_ChaserSprite.rotate(moveSpeed - 0.25);
				}
				else
					if (direction == 'r')
					{
						AI_ChaserSprite.rotate(-moveSpeed + 0.25);
					}
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
	void nextPointCoordinates(double L, double &xNextPoint, double &yNextPoint)
	{
		float x, y;
		x = AI_ChaserSprite.getPosition().x;
		y = AI_ChaserSprite.getPosition().y;

		xNextPoint = x - L;
		yNextPoint = y;

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
	double cosForRotation(float xA, float yA, float r)
	{
		float xC = AI_ChaserSprite.getPosition().x;
		float yC = AI_ChaserSprite.getPosition().y;

		if ((xC < xA && yC >= yA) || (xC >= xA && yC > yA))
		{
			return ((yC - yA) / (r * 2));
		}
		else
		{
			return ((yA - yC) / (r * 2));
		}
	}
	float rotationNeeded(float xA, float yA, double cosepsilum)
	{
		//this function calculates the rotation needed for the AI to be directed towards the player
		float xC = AI_ChaserSprite.getPosition().x;
		float yC = AI_ChaserSprite.getPosition().y;
		
		
		if (xC < xA && yC > yA)
		{
			if (cosepsilum < -1)
			{
				while (cosepsilum < -1)
				{
					cosepsilum = cosepsilum + 2 * M_PI;
				}
			}
			else if (cosepsilum > 1)
			{
				while (cosepsilum > 1)
				{
					cosepsilum = cosepsilum - 2 * M_PI;
				}
			}

			//return acos(cosepsilum)/180.0 * M_PI;
		}
		else if (xC < xA && yC == yA)
		{
			return 90;
		}
		else if (xC < xA && yC < yA)
		{
			cosepsilum = -cosepsilum - 1;
			if (cosepsilum < -1)
			{
				while (cosepsilum < -1)
				{
					cosepsilum = cosepsilum + 2 * M_PI;
				}
			}
			else if (cosepsilum > 1)
			{
				while (cosepsilum > 1)
				{
					cosepsilum = cosepsilum - 2 * M_PI;
				}
			}

			//return acos((180 - cosepsilum) * M_PI / 180.0) / 180.0 * M_PI;
		}
		else if (xC == xA && yC < yA)
		{
			return 180;
		}
		else if (xC > xA && yC < yA)
		{
			cosepsilum = cosepsilum - 1;
			if (cosepsilum < -1)
			{
				while (cosepsilum < -1)
				{
					cosepsilum = cosepsilum + 2 * M_PI;
				}
			}
			else if (cosepsilum > 1)
			{
				while (cosepsilum > 1)
				{
					cosepsilum = cosepsilum - 2 * M_PI;
				}
			}
			//return acos((180 + cosepsilum) * M_PI / 180.0) / 180.0 * M_PI;
		}
		else if (xC > xA && yC == yA)
		{
			return 270;
		}
		else if (xC > xA && yC > yA)
		{
			if (cosepsilum < -1)
			{
				while (cosepsilum < -1)
				{
					cosepsilum = cosepsilum + 2 * M_PI;
				}
			}
			else if (cosepsilum > 1)
			{
				while (cosepsilum > 1)
				{
					cosepsilum = cosepsilum - 2 * M_PI;
				}
			}
			//return 270 + cosepsilum;
		}
		else
		{
			return 0;
		}
		return acos(cosepsilum) / 180.0 * M_PI;
	}
};