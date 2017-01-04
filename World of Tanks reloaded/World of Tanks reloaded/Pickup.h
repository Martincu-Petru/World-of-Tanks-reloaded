#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Pickup
{
private:

	//const int START_WAIT_TIME = 10;
	//const int START_SECONDS_TO_LIVE = 5;
	// The sprite that represents this pickup
	Sprite m_Sprite;
	// How much is this pickup worth?
	int m_Value;
	// What type of pickup is this?
	// 1 = health, 2 = ammo
	int m_Type;
	// Handle spawning and disappearing
	//bool m_Spawned;
	//float m_SecondsSinceSpawn;
	//float m_SecondsSinceDeSpawn;
	//float m_SecondsToLive;
	//float m_SecondsToWait;
	// Public prototypes go here
public:

	Pickup(int type)
	{
		// Store the type of this pickup
		m_Type = type;
		// Associate the texture with the sprite
		if (m_Type == 1)
		{
			Sprite m_Sprite;
			Texture health;
			health.loadFromFile("health.png");
			m_Sprite.setTexture(health);
		}
		else
		{
			Sprite m_Sprite;
			Texture ammo;
			ammo.loadFromFile("ammo.png");
			m_Sprite.setTexture(ammo);
		}
		//m_Sprite.setOrigin(25, 25);
		//m_SecondsToLive = START_SECONDS_TO_LIVE;
	//	m_SecondsToWait = START_WAIT_TIME;
//		spawn();
	}
	void spawn()
	{
		// Spawn at a random location
		srand((int)time(0) / m_Type);
		int x = (rand() % 1366);
		srand((int)time(0) * m_Type);
		int y = (rand() % 768);
		//m_SecondsSinceSpawn = 0;
		//m_Spawned = true;
		m_Sprite.setPosition(x, y);
		cout << x << " " << y << endl;
	}
	Sprite getSprite()
	{
		return m_Sprite;
	}
	//bool isSpawned()
	//{
	//	return m_Spawned;
	//}
	//void update(float elapsedTime)
	//{
	//	if (m_Spawned)
	//	{
	//		m_SecondsSinceSpawn += elapsedTime;
	//		cout << elapsedTime << endl;
	//	}
	//	else
	//	{
	//		m_SecondsSinceDeSpawn += elapsedTime;
	//	}
	//	// Do we need to hide a pickup?
	//	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	//	{
	//		// Remove the pickup and put it somewhere else
	//		m_Spawned = false;
	//		m_SecondsSinceDeSpawn = 0;
	//	}
	//	// Do we need to spawn a pickup
	//	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	//	{
	//		// spawn the pickup and reset the timer
	//		spawn();
	//	}
	//}
};