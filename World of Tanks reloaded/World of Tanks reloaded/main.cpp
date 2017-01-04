#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <random>
#include "Player.h"
#include <iostream>
#include "bullet.h"
#include <sstream> //#include "ai_Entity.h"
#include "Pickup.h"
using namespace sf;
using namespace std;

int main()
{

	RenderWindow mainScreen(VideoMode(1366, 768), "World of Tanks reloaded", Style::Fullscreen);
	mainScreen.setKeyRepeatEnabled(true);
	Player mainTank("E-100.png");

	//from here

	//ai_Entity mainAI("E-100.png");

	// 100 bullets should do
	Bullet bullets[100];
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1;

	// When was the fire button last pressed?
	Time lastPressed;
	Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;

	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Make a decimal fraction of 1 from the delta time
	Time dt;
	float dtAsSeconds = dt.asSeconds();

	//to here

	
	//Pickup ammoPickup(2);

	Event Event;
	Clock tictoc, elapsed;;
	Texture healthBarTexture, textureBackground, stone, planeTexture, plane2Texture;
	Sprite HP, spriteBackground, stone0, plane, plane2;
	RectangleShape healthBar, healthBarEmpty;
	Text healthLevel;
	Font fontHealth;
	bool planeActive = false, plane2Active = false;
	float planeSpeed = 0.0f, plane2Speed = 0.0f;
	int health = mainTank.getHealth();

	healthBarTexture.loadFromFile("HP.png");
	planeTexture.loadFromFile("Ao192.png");
	textureBackground.loadFromFile("intro.jpg");
	stone.loadFromFile("stone.png");
	plane2Texture.loadFromFile("Bf110e.png");
	fontHealth.loadFromFile("Font.ttf");


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

	Pickup healthPickup(1);

	healthPickup.spawn();
	//ammoPickup.spawn();

	while (mainScreen.isOpen()){

		healthLevel.setPosition(1017, 65);
		Time dt = tictoc.restart(); //Timpul dintre 2 treceri


		if (!planeActive)
		{
			srand((int)time(0));
			planeSpeed = rand() % 200 + 200;
			srand((int)time(0) * 10);
			float height = rand() % 500 + 100;
			plane.setPosition(1400, height);
			if (rand() % 10 == 9) //Sansele sunt 1 din 7 ca avionul sa fie spawn-at din nou
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
			if (rand() % 7 == 0) //Sansele sunt 1 din 7 ca avionul sa fie spawn-at din nou
				plane2Active = true;
		}
		else
		{
			plane2.setPosition(plane2.getPosition().x + (plane2Speed * dt.asSeconds()), plane2.getPosition().y);
			if (plane2.getPosition().x > 1400)
				plane2Active = false;
		}

		while (mainScreen.pollEvent(Event)) 
		{
			healthBar.setSize(Vector2f(mainTank.getHealth()*2.6, 30));
			//mainAI.BuildPathToTarget();
			if (Event.type == Event::EventType::Closed)
				mainScreen.close();
			if (Keyboard::isKeyPressed(Keyboard::S))
				mainTank.movePlayer('u', 0.75); 
			else if (Keyboard::isKeyPressed(Keyboard::D))
				mainTank.movePlayer('l', 0.75);
			else if (Keyboard::isKeyPressed(Keyboard::A))
				mainTank.movePlayer('r', 0.75);
			else if (Keyboard::isKeyPressed(Keyboard::W))
				mainTank.movePlayer('d', 0.75);

			//from here
			// Fire a bullet
			int ok = 0;
			if (Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds()> 1000 / fireRate && bulletsInClip > 0)
				{
					// Pass the center of the player and the center of the crosshair to the shoot function
					bullets[currentBullet].shoot( mainTank.getXorigin() , mainTank.getYorigin() , mouseWorldPosition.x , mouseWorldPosition.y );
					currentBullet++;
					if (currentBullet > 99)
					{
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;
					bulletsInClip--;
				}
			}// End fire a bullet

			 // Update any bullets that are in-flight
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					bullets[i].update(dtAsSeconds);
				}
			}
			//to here
		}

		mainScreen.clear();
		mainScreen.draw(spriteBackground);
		stringstream ss;
		ss << "Integrity: " << mainTank.getHealth();
		healthLevel.setString(ss.str());
		mainTank.drawPlayer(mainScreen);
		/*if (healthPickup.isSpawned())
		{
			mainScreen.draw(healthPickup.getSprite());
		}
		if (ammoPickup.isSpawned())
		{
			mainScreen.draw(ammoPickup.getSprite());
		}*/

		mainScreen.draw(healthPickup.getSprite());
		//mainScreen.draw(ammoPickup.getSprite());

		//mainScreen.draw(stone0);
		mainScreen.draw(plane);
		mainScreen.draw(plane2);
		mainScreen.draw(healthLevel);
		mainScreen.draw(healthBarEmpty);
		mainScreen.draw(healthBar);
		mainScreen.draw(HP);
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight())
			{
				mainScreen.draw(bullets[i].getShape());
			}
		}
		mainScreen.display();
	}
}
