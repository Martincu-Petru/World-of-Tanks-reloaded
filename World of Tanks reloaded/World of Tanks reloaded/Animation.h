#pragma once
#include <SFML\Graphics.hpp>
class explosion
{
public:
	bool animation(unsigned int a)
	{
		if(a >= 1 && a < 20)
		{
			explosionTexture.loadFromFile("e1.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 20 && a < 40)
		{
			explosionTexture.loadFromFile("e2.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 40 && a < 60)
		{
			explosionTexture.loadFromFile("e3.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 60 && a < 80)
		{
			explosionTexture.loadFromFile("e4.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 80 && a < 100)
		{
			explosionTexture.loadFromFile("e5.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 100 && a < 120)
		{
			explosionTexture.loadFromFile("e6.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 120 && a < 140)
		{
			explosionTexture.loadFromFile("e7.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 140 && a < 160) 
		{
			explosionTexture.loadFromFile("e8.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 160 && a < 180)
		{
			explosionTexture.loadFromFile("e9.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 180 && a < 200)
		{
			explosionTexture.loadFromFile("e10.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 200 && a < 220)
		{
			explosionTexture.loadFromFile("e11.png");
			explosionSprite.setTexture(explosionTexture);
			return true;
		}
		else if (a >= 220 && a < 240)
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