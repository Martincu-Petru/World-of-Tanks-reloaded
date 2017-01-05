#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <random>
#include "Player.h"
#include <iostream>
#include "bullet.h"
#include <sstream> 
#include "ai_Entity.h"
#include "AI_Chaser.h"
#include <stdlib.h>
using namespace sf;
using namespace std;

int main()
{
	RenderWindow mainScreen(VideoMode(1366, 768), "World of Tanks reloaded", Style::Fullscreen);
	Player mainTank("E-100.png");

	ai_Entity mainAI("Ferdinand.png");
	AI_Chaser chaser("E-1002.png");
	float rotationNeeded = 270;
	// 2 bullets should do
	Bullet bullets[2];
	int currentBullet = 0, i;
	
	Event Event;
	Clock tictoc, elapsed;;
	Texture healthBarTexture, textureBackground, stone, planeTexture, plane2Texture, healthTexture, speedTexture, ammoTexture;
	Sprite HP, spriteBackground, stone0, plane, plane2, healthSprite, ammoSprite, speedSprite;
	RectangleShape healthBar, healthBarEmpty;
	Text healthLevel, SpeedTank;
	Font fontHealth;
	bool planeActive = false, plane2Active = false, ammoSpawned=false, speedSpawned=false, healthSpawned=false;
	float planeSpeed = 0.0f, plane2Speed = 0.0f;
	int health = mainTank.getHealth();
	Clock clock, ammoClock, speedClock, healthClock, timeGone, ammoDespawnClock, speedDespawnClock, healthDespawnClock;


	mainScreen.setKeyRepeatEnabled(true);

	healthTexture.loadFromFile("health.png");
	speedTexture.loadFromFile("speed.png");
	ammoTexture.loadFromFile("ammo.png");
	healthBarTexture.loadFromFile("HP.png");
	planeTexture.loadFromFile("Ao192.png");
	textureBackground.loadFromFile("intro.jpg");
	stone.loadFromFile("stone.png");
	plane2Texture.loadFromFile("Bf110e.png");
	fontHealth.loadFromFile("Font.ttf");

	healthSprite.setTexture(healthTexture);
	ammoSprite.setTexture(ammoTexture);
	speedSprite.setTexture(speedTexture);
	HP.setTexture(healthBarTexture);
	spriteBackground.setTexture(textureBackground);
	stone0.setTexture(stone);
	plane.setTexture(planeTexture);
	plane2.setTexture(plane2Texture);


	HP.setPosition(1000, 20);
	stone0.setPosition(100, 550);
	spriteBackground.setPosition(0, 0);
	healthBar.setPosition(1070, 30);
	plane2.scale(0.3f, 0.3f);
	healthBarEmpty.setPosition(1070, 30);


	healthSprite.setScale(0.2f, 0.2f);
	ammoSprite.setScale(0.1f, 0.1f);
	speedSprite.setScale(0.15f, 0.15f);

	HP.setScale(0.4f, 0.4f); 
	plane.scale(0.3f, 0.3f);

	planeTexture.setSmooth(true);
	plane2Texture.setSmooth(true);

	healthBar.setFillColor(Color(120,201,32));

	healthBarEmpty.setFillColor(Color(255, 0, 0, 200));
	healthBarEmpty.setSize(Vector2f(260, 30));

	healthLevel.setFont(fontHealth);
	healthLevel.setCharacterSize(30);
	healthLevel.setFillColor(Color::White);
	SpeedTank.setFont(fontHealth);
	SpeedTank.setCharacterSize(30);
	SpeedTank.setFillColor(Color::White);


	while (mainScreen.isOpen()){
		healthLevel.setPosition(1017, 65);
		SpeedTank.setPosition(1017, 100);

		Time dt = clock.restart(), speedSinceSpawn=speedClock.getElapsedTime(),
			healthSinceSpawn= healthClock.getElapsedTime(), ammoSinceSpawn = ammoClock.getElapsedTime();
		Time ammoSinceDespawn=ammoDespawnClock.getElapsedTime(), healthSinceDespawn=healthDespawnClock.getElapsedTime(), speedSinceDespawn=speedDespawnClock.getElapsedTime();
		if (!planeActive)
		{
			srand((int)time(0));
			planeSpeed = rand() % 200 + 200;
			srand((int)time(0) * 10);
			float height = rand() % 500 + 100;
			plane.setPosition(1400, height);
			if (rand() % 10 == 9)
				planeActive = true;
		}
		else
		{
			plane.setPosition(plane.getPosition().x - (planeSpeed * dt.asSeconds()), plane.getPosition().y);
			if (plane.getPosition().x < -200)
				planeActive = false;
		}

		if (!plane2Active)
		{
			srand((int)time(0));
			plane2Speed = rand() % 200 + 200;
			srand((int)time(0) * 10);
			float height2 = rand() % 500 + 100;
			plane2.setPosition(-1400, height2);
			if (rand() % 7 == 0)
				plane2Active = true;
		}
		else
		{
			plane2.setPosition(plane2.getPosition().x + (plane2Speed * dt.asSeconds()), plane2.getPosition().y);
			if (plane2.getPosition().x > 1400)
				plane2Active = false;
		}
		if (!ammoSpawned && ammoSinceDespawn.asSeconds()>2)
		{
			srand(time(0)*ammoSinceDespawn.asSeconds());
			int x = rand() % 1200 + 100;
			srand(time(0)*ammoSinceDespawn.asSeconds()+3.14);
			int y = rand() % 500 + 10;
			ammoSprite.setPosition(x, y);
			if (!(healthSpawned == true && abs(x - healthSprite.getPosition().x) < 300 || abs(x - speedSprite.getPosition().x) < 300 && speedSpawned == true))
			{
				ammoSpawned = true;
				ammoClock.restart();
			}
		}
		if (!healthSpawned && healthSinceDespawn.asSeconds()>3)
		{
			srand(time(0)*healthSinceDespawn.asSeconds());
			int x = rand() % 1200 + 100;
			srand(time(0)*healthSinceDespawn.asSeconds()+3.14);
			int y = rand() % 500 + 10;
			healthSprite.setPosition(x, y);
			if (!(ammoSpawned == true && abs(x - ammoSprite.getPosition().x) < 300 || abs(x - speedSprite.getPosition().x) < 300 && speedSpawned == true))
			{
				healthSpawned = true;
				healthClock.restart();
			}


		}
		if (!speedSpawned && speedSinceDespawn.asSeconds()>1)
		{
			srand(time(0)*speedSinceDespawn.asSeconds());
			int x = rand() % 1200 + 100;
			srand(time(0)*speedSinceDespawn.asSeconds()+3.14);
			int y = rand() % 500 + 10;
			speedSprite.setPosition(x, y);
			if (!(ammoSpawned == true && abs(x - ammoSprite.getPosition().x) < 300 || abs(x - healthSprite.getPosition().x) < 300 && healthSpawned == true))
			{
				speedSpawned = true;
				speedClock.restart();
			}
		}

		float tankSpeed=0;

			healthBar.setSize(Vector2f(mainTank.getHealth()*2.6, 30));

			//mainAI.BuildPathToTarget(mainTank.getXorigin(), mainTank.getYorigin());

			//first we have to handle the player's input
			if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
			{
			//	cout << endl << " DA " << endl;
				mainTank.movePlayer('u'); //era 1.5 peste tot dar tancul se misca prea repede
				tankSpeed = rand() % 1000;
				tankSpeed /= 1000;
				tankSpeed = tankSpeed-mainTank.getSpeed()*300;
				srand(time(0));
				tankSpeed += rand() % 5;
			}
			else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
			{
				mainTank.movePlayer('l');
			}
			else if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
			{
				mainTank.movePlayer('r');
			}
			else if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
			{
				mainTank.movePlayer('d');
				tankSpeed = rand() % 1000;
				tankSpeed /= 1000;
				tankSpeed = tankSpeed+mainTank.getSpeed()*300;
				srand(time(0));
				tankSpeed += rand() % 5;
			}

			// Fire a bullet
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				if (bullets[currentBullet].isInFlight() != true)
				{

					//the next section will calculate the direction in which the bullet is fired
					double xOrigin;
					double yOrigin;
					double rotation = (double)mainTank.rotationOfPlayer();
					unsigned int X = mainTank.xMaxim();
					unsigned int Y = mainTank.yMaxim();
					float tankX = mainTank.getXorigin();
					float tankY = mainTank.getYorigin();
					bullets[currentBullet].thirdPoint(tankX, tankY, rotation, xOrigin, yOrigin, X, Y);

					bullets[currentBullet].shoot(tankX, tankY, xOrigin, yOrigin);
					currentBullet++;
					if (currentBullet > 1)
					{
						currentBullet = 0;
					}
				}

			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				mainScreen.close();
			}
			//from here
			float xA = mainTank.getXorigin();
			float yA = mainTank.getYorigin();
			float chaserRotation = chaser.rotationOfChaser();
			float radius = chaser.circleR(xA, yA);
			double L = chaser.squareL(radius);
			double xNextPoint, xChaser = chaser.getXorigin();
			double yNextpoint, yChaser = chaser.getYorigin();
			chaser.nextPointCoordinates(L, xNextPoint, yNextpoint);
			if (chaserRotation < rotationNeeded && !chaser.isInMotion())
			{
				chaser.moveChaser('l', 1.5);
			}
			else if (chaserRotation == rotationNeeded && xNextPoint<xChaser && yNextpoint >= yChaser)
			{
				chaser.doNotRotate();
				chaser.moveChaser('d', 1.5);
			}


			float rot = mainTank.rotationOfPlayer();
			//cout << " coordonate xA yA " << xA << " " << yA << endl;
			//cout << "raza cercului : " << radius << endl;
			//cout << "lungimea laturii patratului : " << L << endl;
			//cout << "rotatie : " << chaserRotation << " " << rot << endl << endl;
			//to here for chaser


			// Actualizarea pt bullets in-flight
			for (i = 0; i < 2; i++)
			{
				if (bullets[i].isInFlight())
				{
					bullets[i].update(0.250);
				}
			}

		mainScreen.clear();
		mainScreen.draw(spriteBackground);
		stringstream string1, string2;
		string1 << "Integrity: " << mainTank.getHealth();
		healthLevel.setString(string1.str());
		string2 << "Speed: " << tankSpeed;
		SpeedTank.setString(string2.str());
		mainTank.drawPlayer(mainScreen);
		mainScreen.draw(stone0);
		mainScreen.draw(plane);
		mainScreen.draw(plane2);
		mainScreen.draw(healthLevel);
		mainScreen.draw(SpeedTank);
		mainScreen.draw(healthBarEmpty);
		mainScreen.draw(healthBar);
		mainScreen.draw(HP);
		if (ammoSinceSpawn.asSeconds() > 3 && ammoSpawned==true)
		{
			ammoDespawnClock.restart();
			ammoSpawned = false;
		}
		if (healthSinceSpawn.asSeconds() > 4 && healthSpawned==true)
		{
			healthDespawnClock.restart();
			healthSpawned = false;
		}
		if (speedSinceSpawn.asSeconds() > 20 && speedSpawned==true)
		{
			speedDespawnClock.restart();
			speedSpawned = false;
		}
		if (mainTank.checkIfIntersect(ammoSprite))
		{
			ammoSpawned = false;
			ammoDespawnClock.restart();
		}
		if (mainTank.checkIfIntersect(healthSprite) && healthSpawned)
		{
			mainTank.updateHealth();
			healthSpawned = false;
			healthDespawnClock.restart();
		}
		if (mainTank.checkIfIntersect(speedSprite) && speedSpawned)
		{
			mainTank.updateSpeed();
			speedSpawned = false;
			speedDespawnClock.restart();
		}
		if(ammoSpawned)
			mainScreen.draw(ammoSprite);
		if (healthSpawned)
			mainScreen.draw(healthSprite);
		if (speedSpawned)
			mainScreen.draw(speedSprite);

		for (i = 0; i < 2; ++i)
		{
			if (bullets[i].isInFlight())
			{
				mainScreen.draw(bullets[i].getShape());
			}
		}
		mainAI.draw_ai_Entity(mainScreen);
		chaser.drawAI_Chaser(mainScreen);
		mainScreen.display();
	}
}
