#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <random>
#include "Player.h"
#include <iostream>

using namespace sf;
using namespace std;

int main()
{

	RenderWindow mainScreen(VideoMode(1366, 768), "World of Tanks reloaded", Style::Fullscreen);
	mainScreen.setKeyRepeatEnabled(true);
	Player mainTank("E-100.png");

	Event Event;

	Clock tictoc;

	Texture healthBarTexture;
	healthBarTexture.loadFromFile("HP.png");
	Sprite HP;
	HP.setTexture(healthBarTexture);
	HP.setPosition(1000, 20);
	HP.setScale(0.4f, 0.4f);

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

	RectangleShape healthBar;
	healthBar.setFillColor(Color(120,201,32));
	healthBar.setPosition(1070, 30);

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
			healthBar.setSize(Vector2f(mainTank.getHealth()*2.6, 30));
			if (Event.type == Event::EventType::Closed)
				mainScreen.close();
			if (Keyboard::isKeyPressed(Keyboard::S))
				mainTank.movePlayer('u', 0.75); //era 1.5 peste tot dar tancul se misca prea repede
			else if (Keyboard::isKeyPressed(Keyboard::D))
				mainTank.movePlayer('l', 0.75);
			else if (Keyboard::isKeyPressed(Keyboard::A))
				mainTank.movePlayer('r', 0.75);
			else if (Keyboard::isKeyPressed(Keyboard::W))
				mainTank.movePlayer('d', 0.75);

		}
		mainScreen.clear();
		mainScreen.draw(spriteBackground);
		mainTank.drawPlayer(mainScreen);
		mainScreen.draw(plane);
		mainScreen.draw(plane2);
		mainScreen.draw(healthBar);
		mainScreen.draw(HP);
		mainScreen.display();
	}
}
