#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <math.h>
#include "Player.h"


using namespace sf;
using namespace std;

class ai_Entity
{
public:
	ai_Entity()
	{
		//Default constructor
	}
	ai_Entity(string imageName)
	{
		if (!ai_EntityTexture.loadFromFile(imageName))
			cerr << "Error" << endl;
		ai_EntityTexture.setSmooth(true);
		ai_EntitySprite.setTexture(ai_EntityTexture);
		ai_EntitySprite.move(Vector2f(40, 700));
	}
	void draw_ai_Entity(RenderWindow &screen)
	{
		ai_EntitySprite.setOrigin(ai_EntitySprite.getTexture()->getSize().x*0.5, ai_EntitySprite.getTexture()->getSize().y*0.5);
		ai_EntitySprite.setScale(0.25f, 0.25f);
		screen.draw(ai_EntitySprite);
	}

	//AM PUS IN COMENTARIU TEMPORAR PANA REUSESC SA REZOLV CU GLOANTELE. APOI MA VOI OCUPA SI DE ACESTE ERORI
	/*
	void BuildPathToTarget(void)
	{
		int pathRow[1000]; int pathCol[1000], kMaxPathLength = 1000;
		int pathRowTarget = playerSprite, pathColTarget = playerSprite.getPosition().y;

		int endRow = playerSprite.getPosition().x, endCol = playerSprite.getPosition().y;

		int row = ai_EntitySprite.getPosition().x, col = ai_EntitySprite.getPosition().y;

		int nextCol = ai_EntitySprite.getPosition().y;
		int nextRow = ai_EntitySprite.getPosition().x;

		int deltaRow = endRow - row, deltaCol = endCol - col;
		int stepCol, stepRow;

		int currentStep, fraction;

		for (currentStep = 0; currentStep < kMaxPathLength; currentStep++)
		{
			pathRow[currentStep] = -1;
			pathCol[currentStep] = -1;
		}
		currentStep = 0;
		//pathRowTarget = playerSprite.getPosition().x;
		//pathColTarget = playerSprite.getPosition().y;

		if (deltaRow < 0)
			stepRow = -1;
		else stepRow = 1;

		if (deltaCol < 0)
			stepCol = -1;
		else stepCol = 1;

		deltaRow = abs(deltaRow * 2);
		deltaCol = abs(deltaCol * 2);

		pathRow[currentStep] = nextRow;
		pathCol[currentStep] = nextCol;
		currentStep++;

		if (deltaCol > deltaRow)
		{
			fraction = deltaRow * 2 - deltaCol;
			while (nextCol != endCol)
			{
				if (fraction >= 0)
				{
					nextRow = nextRow + stepRow;
					fraction = fraction - deltaCol;
				}
				nextCol = nextCol + stepCol;
				fraction = fraction + deltaRow;
				pathRow[currentStep] = nextRow;
				pathCol[currentStep] = nextCol;
				currentStep++;
			}
		}
		else
		{
			fraction = deltaCol * 2 - deltaRow;
			while (nextRow != endRow)
			{
				if (fraction >= 0)
				{
					nextCol = nextCol + stepCol;
					fraction = fraction - deltaRow;
				}
				nextRow = nextRow + stepRow;
				fraction = fraction + deltaCol;
				pathRow[currentStep] = nextRow;
				pathCol[currentStep] = nextCol;
				currentStep++;
			}
		}


		if (ai_EntitySprite.getPosition().y + ai_EntitySprite.getGlobalBounds().height*0.5 > VideoMode::getDesktopMode().height)
			ai_EntitySprite.setPosition(Vector2f(ai_EntitySprite.getPosition().x, VideoMode::getDesktopMode().height - ai_EntitySprite.getGlobalBounds().height*0.5));

		if (ai_EntitySprite.getPosition().x + ai_EntitySprite.getGlobalBounds().width*0.5 > VideoMode::getDesktopMode().width)
			ai_EntitySprite.setPosition(VideoMode::getDesktopMode().width - ai_EntitySprite.getGlobalBounds().width*0.5, ai_EntitySprite.getPosition().y);

		if (ai_EntitySprite.getPosition().y - ai_EntitySprite.getGlobalBounds().height*0.5 < 0)
			ai_EntitySprite.setPosition(Vector2f(ai_EntitySprite.getPosition().x, ai_EntitySprite.getGlobalBounds().height*0.5));

		if (ai_EntitySprite.getPosition().x - ai_EntitySprite.getGlobalBounds().width*0.5 < 0)
			ai_EntitySprite.setPosition(Vector2f(ai_EntitySprite.getGlobalBounds().width*0.5, ai_EntitySprite.getPosition().y));

	}
	*/

	/*
	void move_ai_Entity(char direction, float moveSpeed)
	{
		if (direction == 'u')
		{
			ai_EntitySprite.move(sin(ai_EntitySprite.getRotation()*3.14159265 / 180)*-3, cos(ai_EntitySprite.getRotation()*3.14159265 / 180) * 3);
		}
		else
			if (direction == 'd')
			{
				ai_EntitySprite.move(sin(ai_EntitySprite.getRotation()*3.14159265 / 180) * 3, cos(ai_EntitySprite.getRotation()*3.14159265 / 180)*-3);
			}
			else
				if (direction == 'l')
				{
					ai_EntitySprite.rotate(1);
				}
				else
					if (direction == 'r')
					{
						ai_EntitySprite.rotate(-1);
					}
		if (ai_EntitySprite.getPosition().y + ai_EntitySprite.getGlobalBounds().height*0.5 > VideoMode::getDesktopMode().height)
			ai_EntitySprite.setPosition(Vector2f(ai_EntitySprite.getPosition().x, VideoMode::getDesktopMode().height - ai_EntitySprite.getGlobalBounds().height*0.5));

		if (ai_EntitySprite.getPosition().x + ai_EntitySprite.getGlobalBounds().width*0.5 > VideoMode::getDesktopMode().width)
			ai_EntitySprite.setPosition(VideoMode::getDesktopMode().width - ai_EntitySprite.getGlobalBounds().width*0.5, ai_EntitySprite.getPosition().y);

		if (ai_EntitySprite.getPosition().y - ai_EntitySprite.getGlobalBounds().height*0.5 < 0)
			ai_EntitySprite.setPosition(Vector2f(ai_EntitySprite.getPosition().x, ai_EntitySprite.getGlobalBounds().height*0.5));

		if (ai_EntitySprite.getPosition().x - ai_EntitySprite.getGlobalBounds().width*0.5 < 0)
			ai_EntitySprite.setPosition(Vector2f(ai_EntitySprite.getGlobalBounds().width*0.5, ai_EntitySprite.getPosition().y));
	}*/
private:
	Texture ai_EntityTexture;
	Sprite ai_EntitySprite;
};