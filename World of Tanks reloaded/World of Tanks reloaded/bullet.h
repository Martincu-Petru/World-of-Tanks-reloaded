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
		float AB, AC;
		double cosbeta, beta, alpha, cosalpha;
		if (0 < rotation && rotation < 90)
		{
			AB = yA;
			AC = sqrt(pow(xMax - xA, 2) + yA * yA);
			cosbeta = AB / AC;
			beta = cosbeta * 180.0 / M_PI;
			if (rotation < beta)
			{
				alpha = rotation;
				cosalpha = cos(alpha * M_PI / 180.0);
				xC = yA * tan(alpha * M_PI / 180.0) + xA;
				yC = 0;
			}
			else
			{
				alpha = 90 - rotation;
				yC = (xMax - xA) * tan(alpha * M_PI / 180.0) + yA;
				xC = xMax;
				if (yC > yA)
				{
					float auxiliar = yC - yA;
					yC = yA - auxiliar;
				}
			}
		}
		else if (90 < rotation && rotation < 180)
		{
			AB = xMax - xA;
			AC = sqrt(pow(xMax - xA, 2) + pow(yMax - yA, 2));
			cosbeta = AB / AC;
			beta = cosbeta * 180.0 / M_PI;
			if (rotation - 90 < beta)
			{
				alpha = rotation - 90;
				yC = (xMax - xA) * tan(alpha * M_PI / 180.0) + yA;
				xC = xMax;
			}
			else
			{
				alpha = 180 - rotation;
				xC = (yMax - yA) * tan(alpha * M_PI / 180.0) + xA;
				yC = yMax;
			}
		}
		else if (180 < rotation && rotation < 270)
		{
			AB = yMax - yA;
			AC = sqrt(xA * xA + pow(yMax - yA, 2));
			cosbeta = AB / AC;
			beta = cosbeta * 180.0 / M_PI;
			if (rotation - 180 < beta)
			{
				alpha = rotation - 180;
				xC = (yMax - yA) * tan(alpha * M_PI / 180.0) + xA;
				yC = yMax;
				if (xC > xA)
				{
					float auxiliar = xC - xA;
					xC = xA - auxiliar;
				}
			}
			else
			{
				alpha = 270 - rotation;
				yC = xA * tan(alpha * M_PI / 180.0) + yA;
				xC = 0;
			}
		}
		else if (rotation > 270)
		{
			AB = xA;
			AC = sqrt(xA * xA + yA * yA);
			cosbeta = AB / AC;
			beta = cosbeta * 180.0 / M_PI;
			if (rotation - 270 < beta)
			{
				alpha = rotation - 270;
				yC = xA * tan(alpha * M_PI / 180.0) + yA;
				xC = 0;
				if (yC > yA)
				{
					float auxiliar = yC - yA;
					yC = yA - auxiliar;
				}
			}
			else
			{
				alpha = 360 - rotation;
				xC = yA * tan(alpha * M_PI / 180.0) + xA;
				yC = 0;
				if (xC > xA)
				{
					float auxiliar = xC - xA;
					xC = xA - auxiliar;
				}
			}
		}
		else if (rotation == 0 || rotation == 360)
		{
			xC = xA;
			yC = 0;
		}
		else if (rotation == 90)
		{
			xC = xMax;
			yC = yA;
		}
		else if (rotation == 180)
		{
			xC = xA;
			yC = yMax;
		}
		else if (rotation == 270)
		{
			xC = 0;
			yC = yA;
		}
	}
	void setBulletRotation(float rotation)
	{
		bullet.setRotation(rotation);
	}
	bool intersect(Sprite obstacle[100], int nr)
	{
		for (int i = 0; i <= nr; i++)
		{
			if (bullet.getGlobalBounds().intersects(obstacle[i].getGlobalBounds()))
			{
				return true;
			}
		}
		return false;
	}
};