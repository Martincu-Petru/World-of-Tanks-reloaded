#pragma once
#include <SFML\Graphics.hpp>
class explosion
{
public:
	bool animation(unsigned int a)
	{
		if(a >= 1 && a < 30)
		{
			explosionTexture.loadFromFile("e1.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 30 && a < 60)
		{
			explosionTexture.loadFromFile("e2.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 60 && a < 90)
		{
			explosionTexture.loadFromFile("e3.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 90 && a < 120)
		{
			explosionTexture.loadFromFile("e4.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 120 && a < 150)
		{
			explosionTexture.loadFromFile("e5.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 150 && a < 180)
		{
			explosionTexture.loadFromFile("e6.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 180 && a < 210)
		{
			explosionTexture.loadFromFile("e7.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 210 && a < 240) 
		{
			explosionTexture.loadFromFile("e8.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 240 && a < 270)
		{
			explosionTexture.loadFromFile("e9.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 270 && a < 300)
		{
			explosionTexture.loadFromFile("e10.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 300 && a < 330)
		{
			explosionTexture.loadFromFile("e11.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 330 && a < 360)
		{
			explosionTexture.loadFromFile("e12.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else
		{
			return false;
		}
	}
	void drawExplosion(RenderWindow &screen, bool ok, float x, float y)
	{
		if (ok)
		{
			explosionSprite.setScale(0.9f, 0.9f);
			explosionSprite.setPosition(x, y);
			screen.draw(explosionSprite);
		}
	}
private:
	Sprite explosionSprite;
	Texture explosionTexture;
};