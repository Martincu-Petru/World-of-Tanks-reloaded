#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <math.h>
#include "Player.h"
#include "bullet.h"

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
		ai_EntitySprite.move(Vector2f(20, 20));
	}
	void draw_ai_Entity(RenderWindow &screen)
	{
		ai_EntitySprite.setOrigin(ai_EntitySprite.getTexture()->getSize().x*0.5, ai_EntitySprite.getTexture()->getSize().y*0.5);
		ai_EntitySprite.setScale(0.25f, 0.25f);
		screen.draw(ai_EntitySprite);
	}
	float AI_X()
	{
		return ai_EntitySprite.getPosition().x;
	}
	float AI_Y()
	{
		return ai_EntitySprite.getPosition().y;
	}
	//AM PUS IN COMENTARIU TEMPORAR PANA REUSESC SA REZOLV CU GLOANTELE. APOI MA VOI OCUPA SI DE ACESTE ERORI

	void BuildPathToTarget(float tankX, float tankY)
	{
		float pathRow[800]; 
		float pathCol[800];
		unsigned int kMaxPathLength = 800;

		//coordinates of the path
		float pathRowTarget = tankX, pathColTarget = tankY;

		//coordinates of the end of it
		float endRow = tankX, endCol = tankY;

		//where the AI unit is
		float row = AI_X(), col = AI_Y();

		//WHY DO WE HAVE THESE?
		int nextCol = col;
		int nextRow = row;

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

		if (deltaCol > deltaRow) // pentru cazul simplu in care tancurile sunt la locurile lor, pathCol[currentStep]=va ajunge sa contina o valoare negativa
			//verifica algoritmul din carte
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
private:
	Texture ai_EntityTexture;
	Sprite ai_EntitySprite;
};