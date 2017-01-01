#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <random>
#include "Player.h"
#include "bullet.h"
//#include "ai_Entity.h"
;
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

	Event Event;

	Clock tictoc;

	Texture textureBackground;
	textureBackground.loadFromFile("intro.jpg");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	Texture planeTexture;
	planeTexture.loadFromFile("Ao192.png");
	planeTexture.setSmooth(true);
	Sprite plane;
	plane.setTexture(planeTexture);
	plane.scale(0.3f, 0.3f);
	bool planeActive = false;
	float planeSpeed = 0.0f;

	Texture plane2Texture;
	plane2Texture.loadFromFile("Bf110e.png");
	plane2Texture.setSmooth(true);
	Sprite plane2;
	plane2.setTexture(plane2Texture);
	plane2.scale(0.3f, 0.3f);
	bool plane2Active = false;
	float plane2Speed = 0.0f;



	while (mainScreen.isOpen())
	{
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
			//mainAI.BuildPathToTarget();

			if (Event.type == Event::EventType::Closed)
				mainScreen.close();
			if (Keyboard::isKeyPressed(Keyboard::S))
				mainTank.movePlayer('u', 1.5); //era 0.5 peste tot dar tancul se misca prea incet
			else if (Keyboard::isKeyPressed(Keyboard::D))
				mainTank.movePlayer('l', 1.5);
			else if (Keyboard::isKeyPressed(Keyboard::A))
				mainTank.movePlayer('r', 1.5);
			else if (Keyboard::isKeyPressed(Keyboard::W))
				mainTank.movePlayer('d', 1.5);

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
		mainTank.drawPlayer(mainScreen);
		mainScreen.draw(plane);
		mainScreen.draw(plane2);
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
