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
#include "menu.h"
using namespace sf;
using namespace std;

void moveUp(int &itemCurent, Text optiunea[4], int nrOptiuni)
{
	if (itemCurent - 1 >= 0)
	{
		optiunea[itemCurent].setFillColor(Color::White);
		itemCurent--;
		optiunea[itemCurent].setFillColor(Color::Red);
	}
}

void moveDown(int &itemCurent, Text optiunea[4], int nrOptiuni)
{
	if (itemCurent + 1 < nrOptiuni)
	{
		optiunea[itemCurent].setFillColor(Color::White);
		itemCurent++;
		optiunea[itemCurent].setFillColor(Color::Red);
	}
}

Font textStyle;
Text optiunea[4], optiuneaExit[3], optiuneaResume[3];

void moveLeft(int &itemCurentExit, Text optiuneaExit[3])
{
	if (itemCurentExit == 2)
	{
		optiuneaExit[itemCurentExit].setFillColor(Color::White);
		itemCurentExit--;
		optiuneaExit[itemCurentExit].setFillColor(Color::Red);
	}
}

void moveRight(int &itemCurentExit, Text optiuneaExit[3])
{
	if (itemCurentExit == 1)
	{
		optiuneaExit[itemCurentExit].setFillColor(Color::White);
		itemCurentExit++;
		optiuneaExit[itemCurentExit].setFillColor(Color::Red);
	}
}

void setOptionsExit()
{
	if (!textStyle.loadFromFile("Font.ttf"))
		cout << "Error loading font!";

	optiuneaExit[0].setFont(textStyle);
	optiuneaExit[0].setFillColor(Color::White);
	optiuneaExit[0].setString("Are you sure you want to exit?");
	optiuneaExit[0].setPosition(Vector2f(1366 / 4 + 100, 768 / 2 - 100));

	optiuneaExit[1].setFont(textStyle);
	optiuneaExit[1].setFillColor(Color::White);
	optiuneaExit[1].setString("Yes");
	optiuneaExit[1].setPosition(Vector2f(1366 / 4, 768 / 2 + 100));

	optiuneaExit[2].setFont(textStyle);
	optiuneaExit[2].setFillColor(Color::Red);
	optiuneaExit[2].setString("No");
	optiuneaExit[2].setPosition(Vector2f(1366 / 4 * 3, 768 / 2 + 100));
}

void setOptions()
{
	if (!textStyle.loadFromFile("Font.ttf"))
		cout << "Error loading font!";

	optiunea[0].setFont(textStyle);
	optiunea[0].setFillColor(Color::Red);
	optiunea[0].setString("Play");
	optiunea[0].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 1 + 200));

	optiunea[1].setFont(textStyle);
	optiunea[1].setFillColor(Color::White);
	optiunea[1].setString("Options");
	optiunea[1].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 1.5 + 200));

	optiunea[2].setFont(textStyle);
	optiunea[2].setFillColor(Color::White);
	optiunea[2].setString("How to play?");
	optiunea[2].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 2 + 200));

	optiunea[3].setFont(textStyle);
	optiunea[3].setFillColor(Color::White);
	optiunea[3].setString("Exit");
	optiunea[3].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 2.5 + 200));
}

void resumeGame()
{
	if (!textStyle.loadFromFile("Font.ttf"))
		cout << "Error loading font!";

	optiuneaResume[0].setFont(textStyle);
	optiuneaResume[0].setFillColor(Color::Red);
	optiuneaResume[0].setString("Resume game");
	optiuneaResume[0].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 1 + 200));

	optiuneaResume[1].setFont(textStyle);
	optiuneaResume[1].setFillColor(Color::White);
	optiuneaResume[1].setString("New game");
	optiuneaResume[1].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 1.5 + 200));

	optiuneaResume[2].setFont(textStyle);
	optiuneaResume[2].setFillColor(Color::White);
	optiuneaResume[2].setString("Back to menu");
	optiuneaResume[2].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 2 + 200));
}

int main()
{
	setOptions();
	setOptionsExit();
	resumeGame();

	RenderWindow mainScreen(VideoMode(1366, 768), "World of Tanks reloaded", Style::Fullscreen);
	Player mainTank("E-100.png");

	ai_Entity mainAI("Ferdinand.png");
	AI_Chaser chaser("E-1002.png");
	//---------------------------------------------------------------------------------------------------------------
	float tankX = mainTank.getXorigin();
	float tankY = mainTank.getYorigin();
	float rotationNeeded = chaser.rotationNeeded(tankX, tankY);
	float path;
	int ok = 1, okayGo = 0;
	Bullet chaserBullets[3];
	int chaserCurrentBullet = 0, j;
	srand(time(NULL));
	//---------------------------------------------------------------------------------------------------------------
	//this does not change
	int playerNumberBullets = 1;
	double xOrigin;
	double yOrigin;
	float chaserX;
	float chaserY;
	unsigned int X = mainTank.xMaxim();
	unsigned int Y = mainTank.yMaxim();


	// 2 bullets should do
	Bullet bullets[10];
	int currentBullet = 0, i;

	Event Event;
	Texture healthBarTexture, textureBackground, stone, planeTexture, plane2Texture, healthTexture, speedTexture, ammoTexture, menuTexture, menuBackgroundExitTexture, ResumeTexture;
	Sprite HP, spriteBackground, stone0, plane, plane2, healthSprite, ammoSprite, speedSprite, menuBackground, menuExitBackground, resumeBackground;
	RectangleShape healthBar, healthBarEmpty;
	Text healthLevel, SpeedTank;
	Font fontHealth;
	bool planeActive = false, plane2Active = false, ammoSpawned = false, speedSpawned = false, healthSpawned = false;
	float planeSpeed = 0.0f, plane2Speed = 0.0f, TIMP=0, ammoSinceDespawn=0, healthSinceDespawn=0, speedSinceDespawn=0, ammoSinceSpawn=0, healthSinceSpawn=0, speedSinceSpawn=0;
	int health = mainTank.getHealth(), itemCurent = 0, itemCurentExit = 2, itemCurentResume=0;


	mainScreen.setKeyRepeatEnabled(true);

	ResumeTexture.loadFromFile("menu.png");
	menuBackgroundExitTexture.loadFromFile("menu_exit.png");
	menuTexture.loadFromFile("menu.png");
	healthTexture.loadFromFile("health.png");
	speedTexture.loadFromFile("speed.png");
	ammoTexture.loadFromFile("ammo.png");
	healthBarTexture.loadFromFile("HP.png");
	planeTexture.loadFromFile("Ao192.png");
	textureBackground.loadFromFile("intro.jpg");
	stone.loadFromFile("stone.png");
	plane2Texture.loadFromFile("Bf110e.png");
	fontHealth.loadFromFile("Font.ttf");

	resumeBackground.setTexture(ResumeTexture);
	menuExitBackground.setTexture(menuBackgroundExitTexture);
	menuBackground.setTexture(menuTexture);
	healthSprite.setTexture(healthTexture);
	ammoSprite.setTexture(ammoTexture);
	speedSprite.setTexture(speedTexture);
	HP.setTexture(healthBarTexture);
	spriteBackground.setTexture(textureBackground);
	stone0.setTexture(stone);
	plane.setTexture(planeTexture);
	plane2.setTexture(plane2Texture);

	resumeBackground.setPosition(0, 0);
	menuBackground.setPosition(0, 0);
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

	healthBar.setFillColor(Color(120, 201, 32));

	healthBarEmpty.setFillColor(Color(255, 0, 0, 200));
	healthBarEmpty.setSize(Vector2f(260, 30));

	healthLevel.setFont(fontHealth);
	healthLevel.setCharacterSize(30);
	healthLevel.setFillColor(Color::White);
	SpeedTank.setFont(fontHealth);
	SpeedTank.setCharacterSize(30);
	SpeedTank.setFillColor(Color::White);

	menu meniu;

	Clock timeGone;
	int opt = 1;
	while (mainScreen.isOpen()) {

		if (opt == 1) {

			sf::Event menuEvent;
			while (mainScreen.pollEvent(menuEvent))
			{
				switch (menuEvent.type)
				{
				case Event::KeyPressed:
					switch (menuEvent.key.code)
					{
					case::Keyboard::Up:
						moveUp(itemCurent, optiunea, 4);
						break;
					case::Keyboard::Down:
						moveDown(itemCurent, optiunea, 4);
						break;
					case::Keyboard::Return:
						switch (itemCurent)
						{
						case 0:
							opt = 2;
							break;
						case 3:
							opt = 4;
							break;
						}
						break;
					}
					break;
				case sf::Event::Closed:
					mainScreen.close();
					break;
				}
			}

			mainScreen.clear();
			mainScreen.draw(menuBackground);
			for (int i = 0; i < 4; i++)
				mainScreen.draw(optiunea[i]);
			mainScreen.display();
		}
		else
			if (opt == 2)
			{
				sf::Event menuEvent;
				while (mainScreen.pollEvent(menuEvent))
				{
					switch (menuEvent.type)
					{
					case Event::KeyPressed:
						switch (menuEvent.key.code)
						{
						case::Keyboard::Up:
							moveUp(itemCurentResume, optiuneaResume, 3);
							break;
						case::Keyboard::Down:
							moveDown(itemCurentResume, optiuneaResume, 3);
							break;
						case::Keyboard::Return:
							switch (itemCurentResume)
							{
							case 0:
								opt = 3;
								break;
							case 1:
								opt = 5;
								break;
							case 2:
								opt = 1;
								break;
							}
							break;
						}
						break;
					case sf::Event::Closed:
						mainScreen.close();
						break;
					}
				}
				mainScreen.clear();
				mainScreen.draw(resumeBackground);
				for (int i = 0; i < 3; i++)
					mainScreen.draw(optiuneaResume[i]);
				mainScreen.display();
			}
			else
				if (opt == 5)
				{

					ammoSinceDespawn = 0;
					ammoSinceSpawn = 0;
					healthSinceSpawn = 0;
					healthSinceDespawn = 0;
					speedSinceSpawn = 0;
					speedSinceDespawn = 0;
					ammoSpawned = false;
					speedSpawned = false;
					healthSpawned = false;
					plane2Active = false;
					planeActive = false;
					mainTank.restart();
					opt = 3;
				}
				else
			if (opt == 3)
			{
				healthLevel.setPosition(1017, 65);
				SpeedTank.setPosition(1017, 100);

				Time dt=timeGone.restart();

				if(dt.asSeconds()<1)
					TIMP = dt.asSeconds();
				if (!ammoSpawned)
					ammoSinceDespawn += TIMP;
				if (!speedSpawned)
					speedSinceDespawn += TIMP;
				if (!healthSpawned)
					healthSinceDespawn += TIMP;

				if (ammoSpawned)
					ammoSinceSpawn += TIMP;
				if (speedSpawned)
					speedSinceSpawn += TIMP;
				if (healthSpawned)
					healthSinceSpawn += TIMP;

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
					plane.setPosition(plane.getPosition().x - (planeSpeed * TIMP), plane.getPosition().y);
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
				if(opt==3)plane2.setPosition(plane2.getPosition().x + (plane2Speed * TIMP), plane2.getPosition().y);
					if (plane2.getPosition().x > 1400)
						plane2Active = false;
				}
				if (!ammoSpawned && ammoSinceDespawn > 5)
				{
					srand(time(0)*ammoSinceDespawn);
					int x = rand() % 1200 + 100;
					srand(time(0)*ammoSinceDespawn + 3.14);
					int y = rand() % 500 + 10;
					ammoSprite.setPosition(x, y);
					if (!(healthSpawned == true && abs(x - healthSprite.getPosition().x) < 300 || abs(x - speedSprite.getPosition().x) < 300 && speedSpawned == true))
					{
						ammoSpawned = true;
						ammoSinceSpawn = 0;
					}
				}
				if (!healthSpawned && healthSinceDespawn > 6)
				{
					srand(time(0)*healthSinceDespawn);
					int x = rand() % 1200 + 100;
					srand(time(0)*healthSinceDespawn + 3.14);
					int y = rand() % 500 + 10;
					healthSprite.setPosition(x, y);
					if (!(ammoSpawned == true && abs(x - ammoSprite.getPosition().x) < 300 || abs(x - speedSprite.getPosition().x) < 300 && speedSpawned == true))
					{
						healthSpawned = true;
						healthSinceSpawn = 0;
					}


				}
				if (!speedSpawned && speedSinceDespawn > 4)
				{
					srand(time(0)*speedSinceDespawn);
					int x = rand() % 1200 + 100;
					srand(time(0)*speedSinceDespawn + 3.14);
					int y = rand() % 500 + 10;
					speedSprite.setPosition(x, y);
					if (!(ammoSpawned == true && abs(x - ammoSprite.getPosition().x) < 300 || abs(x - healthSprite.getPosition().x) < 300 && healthSpawned == true))
					{
						speedSpawned = true;
						speedSinceSpawn = 0;
					}
				}

				float tankSpeed = 0;

				healthBar.setSize(Vector2f(mainTank.getHealth()*2.6, 30));

				//mainAI.BuildPathToTarget(mainTank.getXorigin(), mainTank.getYorigin());

				//first we have to handle the player's input
				if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
				{
					//	cout << endl << " DA " << endl;
					mainTank.movePlayer('u'); //era 1.5 peste tot dar tancul se misca prea repede
					tankSpeed = rand() % 1000;
					tankSpeed /= 1000;
					tankSpeed = tankSpeed - mainTank.getSpeed() * 300;
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
					tankSpeed = tankSpeed + mainTank.getSpeed() * 300;
					srand(time(0));
					tankSpeed += rand() % 5;
				}

				// Fire a bullet
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					if (bullets[currentBullet].isInFlight() != true)
					{
						float tankXX;
						float tankYY;
						mainTank.goodPoint(tankXX, tankYY);
						double rotation = (double)mainTank.rotationOfPlayer();
						bullets[currentBullet].thirdPoint(tankXX, tankYY, rotation, xOrigin, yOrigin, X, Y);

						bullets[currentBullet].shoot(tankXX, tankYY, xOrigin, yOrigin);
						currentBullet++;
						if (currentBullet >= playerNumberBullets)
						{
							currentBullet = 0;
						}
					}

				}

				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					opt = 1;
				}






				double chaserRotation = (double)chaser.rotationOfChaser();
				//cout << "chaser rotation : " << chaserRotation << endl;
				//cout << "rotation needed : " << rotationNeeded << endl << endl;
				if (!chaser.isInMotion())
				{
					double A, D;
					if (chaserRotation > rotationNeeded && okayGo == 0)
					{
						A = chaserRotation - rotationNeeded;
						D = 360 - A;
					}
					else if (chaserRotation < rotationNeeded && okayGo == 0)
					{
						D = rotationNeeded - chaserRotation;
						A = 360 - D;
					}
					if (A > D && !okayGo)
					{
						okayGo = 1;
					}
					else if (A < D && !okayGo)
					{
						okayGo = 2;
					}
					//cout << okayGo << " : okayGo" << endl;
					if (okayGo == 1)
					{
						chaser.moveChaser('l', 2);
						chaser.rotate();
					}
					else if (okayGo == 2)
					{
						chaser.moveChaser('r', 2);
						chaser.rotate();
					}
				}
				if (abs(chaserRotation - rotationNeeded) < 1.2 && !chaser.isInMotion())
				{
					//cout << "STOP ROTATING, YOU'RE ANNOYING ME! " << endl;
					chaser.doNotRotate();
					okayGo = 0;
					/*cout << "coordinates of the tank, which didn't move AT ALL: " << tankX << "  " << tankY << endl;
					cout << "coordinates of the CHASER, which should be where I put it " << chaser.getXorigin() << "  " << chaser.getYorigin() << endl;
					cout << "chaser Rotation when it should stop " << chaserRotation << endl;
					cout << "the rotation needed when it shoult stop " << rotationNeeded << endl;
					cout << "the calculated path ";*/
					path = chaser.pathToPlayer(tankX, tankY);
					//cout << path << "   and then   ";
					//cout << path << endl;
				}
				if (chaser.isInMotion() && path != 0)
				{
					chaser.moveChaser('d', 2);
					path--;
					//cout << "the decreasing path : " << path << endl;
				}
				if (path < 0)
				{
					chaser.rotate();
					rotationNeeded = chaser.rotationNeeded(tankX, tankY);
				}



				
				//chaser fires (or not)
				int x = rand() % 10;
				if (x % 3 == 0)
				{
					//x = rand() % 100;
					if (chaserBullets[chaserCurrentBullet].isInFlight() != true)// && x % 7 == 0)
					{
						//the next section will calculate the direction in which the bullet is fired
						float chaserXX = chaser.getXorigin();
						float chaserYY = chaser.getYorigin();
						chaser.goodPoint(chaserXX, chaserYY);
						double rotation = (double)chaser.rotationOfChaser();
						chaserBullets[chaserCurrentBullet].thirdPoint(chaserXX, chaserYY, chaserRotation, xOrigin, yOrigin, X, Y);
						chaserBullets[chaserCurrentBullet].shoot(chaserXX, chaserYY, xOrigin, yOrigin);
						chaserCurrentBullet++;
						if (chaserCurrentBullet > 1)
						{
							chaserCurrentBullet = 0;
						}
					}
				}
				// Actualizarea pt bullets in-flight
				for (i = 0; i < playerNumberBullets; i++)
				{
					if (bullets[i].isInFlight())
					{
						bullets[i].update(0.2);
					}
				}
				//CHASER BULLETS UPDATE MOVEMENT -------------------------------------
				for (j = 0; j < 2; j++)
				{
					if (chaserBullets[j].isInFlight())
					{
						chaserBullets[j].update(0.250);
					}
				}

				mainScreen.clear();
				mainScreen.draw(spriteBackground);
				stringstream string1, string2;
				string1 << "Integrity: " << mainTank.getHealth();
				healthLevel.setString(string1.str());
				string2 << "Speed: " << tankSpeed << " KM/H";
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
				if (ammoSinceSpawn > 6 && ammoSpawned == true)
				{
					ammoSinceDespawn = 0;
					ammoSpawned = false;
				}
				if (healthSinceSpawn > 7 && healthSpawned == true)
				{
					healthSinceDespawn = 0;
					healthSpawned = false;
				}
				if (speedSinceSpawn > 5 && speedSpawned == true)
				{
					speedSinceDespawn = 0;
					speedSpawned = false;
				}
				if (mainTank.checkIfIntersect(ammoSprite))
				{
					ammoSpawned = false;
					if(playerNumberBullets < 9)
						playerNumberBullets++;
					ammoSinceDespawn = 0;
				}
				if (mainTank.checkIfIntersect(healthSprite) && healthSpawned)
				{
					mainTank.updateHealth();
					healthSpawned = false;
					healthSinceDespawn = 0;
				}
				if (mainTank.checkIfIntersect(speedSprite) && speedSpawned)
				{
					mainTank.updateSpeed();
					speedSpawned = false;
					speedSinceDespawn = 0;
				}
				if (ammoSpawned)
					mainScreen.draw(ammoSprite);
				if (healthSpawned)
					mainScreen.draw(healthSprite);
				if (speedSpawned)
					mainScreen.draw(speedSprite);

				for (i = 0; i < playerNumberBullets; ++i)
				{
					if (bullets[i].isInFlight())
					{
						mainScreen.draw(bullets[i].getShape());
					}
				}
				//CHASER BULLETS DRAW ON MAIN SCREEN ------------------------
				for (j = 0; j < 1; ++j)
				{
					if (chaserBullets[j].isInFlight())
					{
						mainScreen.draw(chaserBullets[j].getShape());
					}
				}
				mainAI.draw_ai_Entity(mainScreen);
				chaser.drawAI_Chaser(mainScreen);
				mainScreen.display();
			}
			else
				if (opt == 4)
				{
					sf::Event menuEvent;
					while (mainScreen.pollEvent(menuEvent))
						switch (menuEvent.type)
						{
						case Event::KeyPressed:
							switch (menuEvent.key.code)
							{
							case::Keyboard::Left:
								moveLeft(itemCurentExit, optiuneaExit);
								break;
							case::Keyboard::Right:
								moveRight(itemCurentExit, optiuneaExit);
								break;
							case::Keyboard::Return:
								switch (itemCurentExit)
								{
								case 1:
									return 0;
									break;
								case 2:
									opt = 1;
									break;
								}
								break;
							}
							break;
						}
					mainScreen.clear();
					mainScreen.draw(menuExitBackground);
					for (int i = 0; i < 3; i++)
						mainScreen.draw(optiuneaExit[i]);
					mainScreen.display();
				}
	}

}
