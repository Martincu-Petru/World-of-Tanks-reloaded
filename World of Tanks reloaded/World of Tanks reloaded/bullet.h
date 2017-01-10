#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <math.h>
#include "Player.h"

# define M_PI  3.14159265358979323846
using namespace sf;
using namespace std;
class Bullet
{
private:

	// Where is the bullet?
	Vector2f m_Position;

	// What each bullet looks like
	//RectangleShape m_BulletShape;
	Sprite bullet;
	// Is this bullet currently whizzing through the air
	bool m_InFlight = false;

	// How fast does a bullet travel?
	float m_BulletSpeed = 50;

	/* What fraction of 1 pixel does the bullet travel,
	Horizontally and vertically each frame?
	These values will be derived from m_BulletSpeed*/
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	// Some boundaries so the bullet doesn't fly forever
	unsigned int m_MaxX;
	unsigned int m_MinX;
	unsigned int m_MaxY;
	unsigned int m_MinY;

public:

	Bullet()
	{
		//m_BulletShape.setSize(Vector2f(3, 5));
		//Sprite bullet;
		Texture bulletTexture;
		bulletTexture.loadFromFile("bullet.png");
		bullet.setTexture(bulletTexture);
		bullet.scale(0.03f, 0.03f);
		// The constructor
	}
	void stop()
	{
		// Stop the bullet
		m_InFlight = false;
	}
	bool isInFlight()
	{
		// Returns the value of m_InFlight
		return m_InFlight;
	}
	void shoot(float startX, float startY, float targetX, float targetY, float rotation)
	{
		// Launch a new bullet
		// Keep track of the bullet
		bullet.setRotation(rotation);
		m_InFlight = true;
		m_Position.x = startX;
		m_Position.y = startY;
		// Calculate the gradient of the flight path
		float gradient = 0;
		if (startY != targetY)
		{
			gradient = (startX - targetX) / (startY - targetY);

			// Any gradient less than zero needs to be negative
			if (gradient < 0)
			{
				gradient = -gradient;
			}
		}
		// Calculate the ratio between x and y
		float ratioXY = m_BulletSpeed / (1 + gradient); //m_BulletSpeed = 50;

														// Set the "speed" horizontally and vertically
		m_BulletDistanceY = ratioXY;
		m_BulletDistanceX = ratioXY * gradient;

		// Point the bullet in the right direction
		if (targetX < startX)
		{
			m_BulletDistanceX = -m_BulletDistanceX;
		}
		if (targetY < startY)
		{
			m_BulletDistanceY = -m_BulletDistanceY;
		}

		m_MinX = 0;
		m_MaxX = VideoMode::getDesktopMode().width;
		m_MinY = 0;
		m_MaxY = VideoMode::getDesktopMode().height;

		// Position the bullet ready to be drawn
		//m_BulletShape.setPosition(m_Position);
		bullet.setPosition(m_Position);
	}
	FloatRect getPosition()
	{
		// Tell the calling code where the bullet is in the world
		return bullet.getGlobalBounds();
	}
	Sprite getShape()
	{
		// Return the actual shape (for drawing)
		return bullet;
	}
	void update(float elapsedTime)
	{
		// Update the bullet each frame
		// Update the bullet position variables
		m_Position.x += m_BulletDistanceX * elapsedTime;
		m_Position.y += m_BulletDistanceY * elapsedTime;

		// Move the bullet
		bullet.setPosition(m_Position);

		// Has the bullet gone out of range?
		if (m_Position.x < m_MinX || m_Position.x > m_MaxX || m_Position.y < m_MinY || m_Position.y > m_MaxY)
		{
			stop();
		}
	}
	void thirdPoint(float xA, float yA, double rotation, double &xC, double &yC, unsigned int xMax, unsigned int yMax)
	{
		xC = 0;
		yC = 0;
		double cosalpha;
		double alpha = 0, b, c, xV1, yV1, xV2, yV2, beta, auxiliar;
		if (0 < rotation && rotation < 90)
		{

			cosalpha = yA / (sqrt((xMax - xA) * (xMax - xA) + yA * yA));

			if (cosalpha > 1)
			{
				while (cosalpha > 1)
				{
					cosalpha = cosalpha - 2 * M_PI;
				}
			}
			alpha = cos(rotation * M_PI / 180.0);


			if (alpha > cosalpha)
			{
				beta = rotation;
				c = yA * yA;
				b = c / cos(beta * M_PI / 180.0);
				xC = sqrt(b - c) + xA;
				yC = 0;
				if (xC < xA)
				{
					auxiliar = xA - xC;
					xC = xA + auxiliar;
				}
			}
			else
			{
				beta = 90 - rotation;
				c = (xMax - xA) * (xMax - xA);
				b = c / cos(beta * M_PI / 180.0);
				xC = xMax;
				yC = sqrt(b - c) + yA;
				if (yC > yA)
				{
					auxiliar = yC - yA;
					yC = yA - auxiliar;
				}
			}
		}
		else if (rotation == 90)
		{
			xC = xMax;
			yC = yA;
		}
		else if (90 < rotation && rotation < 180)
		{
			xV1 = xMax - xA;
			yV1 = yA - yA;

			xV2 = xMax - xA;
			yV2 = yMax - yA;

			cosalpha = (xV1 * xV2 + yV1 * yV2) / ((sqrt(xV1 * xV1 + yV1 * yV1)) + (sqrt(xV2 * xV2 + yV2 * yV2)));
			if (cosalpha < -1)
			{
				while (cosalpha < -1)
				{
					cosalpha += 2 * M_PI;
				}
			}
			alpha = cos(rotation * M_PI / 180.0);

			if (alpha > cosalpha)
			{
				beta = rotation - 90;
				c = (xMax - xA) * (xMax - xA);
				b = c / cos(beta * M_PI / 180.0);
				xC = xMax;
				yC = sqrt(b - c) + yA;
				if (yC < yA)
				{
					auxiliar = yA - yC;
					yC = yA + auxiliar;
				}
			}
			else
			{
				beta = 180 - rotation;
				c = (yMax - yA) * (yMax - yA);
				b = c / cos(beta * M_PI / 180.0);
				xC = sqrt(b - c) + xA;
				yC = yMax;
				if (xC < xA)
				{
					auxiliar = xA - xC;
					xC = xA + auxiliar;
				}
			}
		}
		else if (rotation == 180)
		{
			xC = xA;
			yC = yMax;
		}
		else if (180 < rotation && rotation < 270)
		{
			xV1 = xA - xA;
			yV1 = yMax - yA;

			xV2 = 0 - xA;
			yV2 = yMax - yA;

			cosalpha = (xV1 * xV2 + yV1 * yV2) / ((sqrt(xV1 * xV1 + yV1 * yV1)) + (sqrt(xV2 * xV2 + yV2 * yV2)));
			if (cosalpha < -1)
			{
				while (cosalpha < -1)
				{
					cosalpha += 2 * M_PI;
				}
			}
			alpha = cos(rotation * M_PI / 180.0);

			if (alpha < cosalpha)
			{
				beta = rotation - 180;
				c = (yMax - yA) * (yMax - yA);
				b = c / cos(beta * M_PI / 180.0);
				xC = sqrt(b - c) + xA;
				yC = yMax;
				if (xC > xA)
				{
					auxiliar = xC - xA;
					xC = xA - auxiliar;
				}
			}
			else
			{
				beta = 270 - rotation;
				c = xA * xA;
				b = c / cos(beta * M_PI / 180.0);
				xC = 0;
				yC = sqrt(b - c) + yA;
				if (yC < yA)
				{
					auxiliar = yA - yC;
					yC = yA + auxiliar;
				}
			}
		}
		else if (rotation == 270)
		{
			xC = 0;
			yC = yA;
		}
		else if (270 < rotation && rotation < 360)
		{
			xV1 = 0 - xA;
			yV1 = yA - yA;

			xV2 = 0 - xA;
			yV2 = 0 - yA;

			cosalpha = (xV1 * xV2 + yV1 * yV2) / ((sqrt(xV1 * xV1 + yV1 * yV1)) + (sqrt(xV2 * xV2 + yV2 * yV2)));

			if (cosalpha > 1)
			{
				while (cosalpha > 1)
				{
					cosalpha -= 2 * M_PI;
				}
			}
			alpha = cos(rotation * M_PI / 180.0);

			if (alpha < cosalpha)
			{
				beta = rotation - 270;
				c = xA * xA;
				b = c / cos(beta * M_PI / 180.0);
				xC = 0;
				yC = sqrt(b - c) + yA;
				if (yC > yA)
				{
					auxiliar = yC - yA;
					yC = yA - auxiliar;
				}
			}
			else
			{
				beta = 360 - rotation;
				c = yA * yA;
				b = c / cos(beta * M_PI / 180.0);
				xC = sqrt(b - c) + xA;
				yC = 0;
				if (xC > xA)
				{
					auxiliar = xC - xA;
					xC = xA - auxiliar;
				}
			}
		}
		else
		{
			xC = xA;
			yC = 0;
		}
	}
	void setBulletRotation(float rotation)
	{
		bullet.setRotation(rotation);
	}
};