#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <math.h>
#include "Player.h"

using namespace sf;
using namespace std;
class Bullet
{
private:

	// Where is the bullet?
	Vector2f m_Position;

	// What each bullet looks like
	RectangleShape m_BulletShape;

	// Is this bullet currently whizzing through the air
	bool m_InFlight = false;

	// How fast does a bullet travel?
	float m_BulletSpeed = 1000;

	/* What fraction of 1 pixel does the bullet travel,
	Horizontally and vertically each frame?
	 These values will be derived from m_BulletSpeed*/
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	// Some boundaries so the bullet doesn't fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

public:

	Bullet()
	{
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
	void shoot(float startX, float startY, float targetX, float targetY)
	{
		// Launch a new bullet
		// Keep track of the bullet
		m_InFlight = true;
		m_Position.x = startX;
		m_Position.y = startY;
		// Calculate the gradient of the flight path
		float gradient = (startX - targetX) / (startY - targetY);
		// Any gradient less than 1 needs to be negative
		if (gradient < 0)
		{
			gradient *= -1;
		}

		// Calculate the ratio between x and y
		float ratioXY = m_BulletSpeed / (1 + gradient);

		// Set the "speed" horizontally and vertically
		m_BulletDistanceY = ratioXY;
		m_BulletDistanceX = ratioXY * gradient;

		// Point the bullet in the right direction
		if (targetX < startX)
		{
			m_BulletDistanceX *= -1;
		}
		if (targetY < startY)
		{
			m_BulletDistanceY *= -1;
		}

		// Set a max range of 1000 pixels
		float range = 1000;
		m_MinX = startX - range;
		m_MaxX = startX + range;
		m_MinY = startY - range;
		m_MaxY = startY + range;

		// Position the bullet ready to be drawn
		m_BulletShape.setPosition(m_Position);
	}
	FloatRect getPosition()
	{
		// Tell the calling code where the bullet is in the world
		return m_BulletShape.getGlobalBounds();
	}
	RectangleShape getShape()
	{
		// Return the actual shape (for drawing)
		return m_BulletShape;
	}
	void update(float elapsedTime)
	{
		// Update the bullet each frame
		// Update the bullet position variables
		m_Position.x += m_BulletDistanceX * elapsedTime;
		m_Position.y += m_BulletDistanceY * elapsedTime;
		// Move the bullet
		m_BulletShape.setPosition(m_Position);
		// Has the bullet gone out of range?
		if (m_Position.x < m_MinX || m_Position.x > m_MaxX ||
			m_Position.y < m_MinY || m_Position.y > m_MaxY)
		{
			m_InFlight = false;
		}
	}
};