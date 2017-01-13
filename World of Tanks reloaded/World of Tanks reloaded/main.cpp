#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <random>
#include "Player.h"
#include <iostream>
#include "bullet.h"
#include <sstream> 
#include "ai_Entity.h"
#include "AI_Chaser.h"
//#include <stdlib.h>
#include <fstream>
#include "Animation.h"
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
Text optiunea[4], optiuneaExit[3], optiuneaResume[3], optiuneaDif[4], optiuneaOpt[5];

bool matrix[14][23], matrix2[14][23], matrix3[14][23];

void citire(int harta)
{
	ifstream fi;
	fi.open("mat.in");
	for (int i = 0; i < 14; i++)
		for (int j = 0; j < 23; j++)
			fi >> matrix[i][j];
	fi.close();
	fi.open("mat2.in");
	for (int i = 0; i < 14; i++)
		for (int j = 0; j < 23; j++)
			fi >> matrix2[i][j];
	fi.close();
	fi.open("mat3.in");
	for (int i = 0; i < 14; i++)
		for (int j = 0; j < 23; j++)
			fi >> matrix3[i][j];
	fi.close();

}

void setOptionsDif()
{
	if (!textStyle.loadFromFile("Font.ttf"))
		cout << "Error loading font!";

	optiuneaDif[0].setFont(textStyle);
	optiuneaDif[0].setFillColor(Color::White);
	optiuneaDif[0].setString("Chose map");
	optiuneaDif[0].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 1 + 70));

	optiuneaDif[1].setFont(textStyle);
	optiuneaDif[1].setFillColor(Color::Red);
	optiuneaDif[1].setString("Malinovka");
	optiuneaDif[1].setPosition(Vector2f(1366 / 4-100, 768/3*2));

	optiuneaDif[2].setFont(textStyle);
	optiuneaDif[2].setFillColor(Color::White);
	optiuneaDif[2].setString("Siegefield");
	optiuneaDif[2].setPosition(Vector2f(1366 / 4*2 - 100, 768 / 3 * 2));

	optiuneaDif[3].setFont(textStyle);
	optiuneaDif[3].setFillColor(Color::White);
	optiuneaDif[3].setString("Stalingrad");
	optiuneaDif[3].setPosition(Vector2f(1366 / 4*3 - 100, 768 / 3 * 2));

}

void setOptionsOpt()
{
	if (!textStyle.loadFromFile("Font.ttf"))
		cout << "Error loading font!";

	optiuneaOpt[0].setFont(textStyle);
	optiuneaOpt[0].setFillColor(Color::White);
	optiuneaOpt[0].setString("Difficulty");
	optiuneaOpt[0].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 1 + 125));

	optiuneaOpt[1].setFont(textStyle);
	optiuneaOpt[1].setFillColor(Color::Red);
	optiuneaOpt[1].setString("Easy");
	optiuneaOpt[1].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 1.5 + 125));

	optiuneaOpt[2].setFont(textStyle);
	optiuneaOpt[2].setFillColor(Color::White);
	optiuneaOpt[2].setString("Medium");
	optiuneaOpt[2].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 2 + 125));

	optiuneaOpt[3].setFont(textStyle);
	optiuneaOpt[3].setFillColor(Color::White);
	optiuneaOpt[3].setString("Hard");
	optiuneaOpt[3].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 2.5 + 125));

	optiuneaOpt[4].setFont(textStyle);
	optiuneaOpt[4].setFillColor(Color::White);
	optiuneaOpt[4].setString("Back to menu");
	optiuneaOpt[4].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 3 + 125));
}

void moveLeft(int &itemCurentExit, Text optiuneaExit[3], int type)
{
	if (type == 1) {
		if (itemCurentExit == 2)
		{
			optiuneaExit[itemCurentExit].setFillColor(Color::White);
			itemCurentExit--;
			optiuneaExit[itemCurentExit].setFillColor(Color::Red);
		}
	}
	else
	{
		if (itemCurentExit > 1)
		{
			optiuneaDif[itemCurentExit].setFillColor(Color::White);
			itemCurentExit--;
			optiuneaDif[itemCurentExit].setFillColor(Color::Red);
		}
	}
}

void moveRight(int &itemCurentExit, Text optiuneaExit[3], int type)
{
	if (type == 1) {
		if (itemCurentExit == 1)
		{
			optiuneaExit[itemCurentExit].setFillColor(Color::White);
			itemCurentExit++;
			optiuneaExit[itemCurentExit].setFillColor(Color::Red);
		}
	}
	else
	{
		if (itemCurentExit < 3)
		{
			optiuneaDif[itemCurentExit].setFillColor(Color::White);
			itemCurentExit++;
			optiuneaDif[itemCurentExit].setFillColor(Color::Red);
		}
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
	setOptionsOpt();
	resumeGame();
	setOptionsDif();
	RenderWindow mainScreen(VideoMode(1366, 768), "World of Tanks reloaded", Style::Fullscreen);
	Player mainTank("E-100.png");
	Player secondTank("T34.png");

	//ai_Entity mainAI("Ferdinand.png");
	AI_Chaser chaser("E-1002.png", 1);
	AI_Chaser chaser2("T-59.png", 2);
	//---------------------------------------------------------------------------------------------------------------
	float tankX = mainTank.getXorigin();
	float tankY = mainTank.getYorigin();
	float rotationNeeded = chaser.rotationNeeded(tankX, tankY);
	float path, changePath;
	int ok = 1, okayGo = 0;
	Bullet chaserBullets[3];
	int chaserCurrentBullet = 0, j;
	int chaserLife = 3;
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
	//----------------------------------------------------FOR THE SECOND CHASER HEEEEEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE-----------------------------------
	float chaser2X, chaser2Y, chaser2Rotation = chaser2.rotationOfChaser(), rotationNeeded2 = chaser2.rotationNeeded(tankX, tankY);
	int variabila, okayGo2 = 0;
	Bullet chaser2Bullets[3];
	int chaser2CurrentBullet = 0, k;
	int chaser2Life = 5;
	//------------------------------------------------------------------------------------------------------------------------------------------------
	bool c1Dead = false, c2Dead = false;
	unsigned int explosionAnimation = 0, explosionAnimation2 = 0, explosionAnimationTank = 0;
	explosion explosion;
	Text gameStatus;
	Bullet bullets[10];
	int currentBullet = 0, i;

	Event Event;
	Texture healthBarTexture, textureBackground,  planeTexture, plane2Texture, healthTexture, speedTexture, ammoTexture, menuTexture, menuBackgroundExitTexture, ResumeTexture;
	Sprite HP, spriteBackground, stone0, plane, plane2, healthSprite, ammoSprite, speedSprite, menuBackground, menuExitBackground, resumeBackground;
	RectangleShape healthBar, healthBarEmpty;
	Text healthLevel, SpeedTank;
	Font fontHealth;
	bool planeActive = false, plane2Active = false, ammoSpawned = false, speedSpawned = false, healthSpawned = false;
	float planeSpeed = 0.0f, plane2Speed = 0.0f, TIMP=0, ammoSinceDespawn=0, healthSinceDespawn=0, speedSinceDespawn=0, ammoSinceSpawn=0, healthSinceSpawn=0, speedSinceSpawn=0;
	int health = mainTank.getHealth(), itemCurent = 0, itemCurentExit = 2, itemCurentResume=0, itemCurentDif = 1, itemCurentOpt=1;
	Sprite map1, map2, map3;
	Texture map1t, map2t, map3t;
	map1t.loadFromFile("map_no_1.png");
	map2t.loadFromFile("map_no_2.png");
	map3t.loadFromFile("map_no_3.png");
	map1.setTexture(map1t);
	map2.setTexture(map2t);
	map3.setTexture(map3t);
	
	map1.setScale(0.2f, 0.2f);
	map2.setScale(0.2f, 0.2f);
	map3.setScale(0.2f, 0.2f);


	map1.setPosition(1366 / 4 - 160, 768 / 3+50);
	map2.setPosition(1366 / 4 * 2 - 160, 768 / 3 + 50);
	map3.setPosition(1366 / 4 * 3 - 160, 768 / 3 + 50);


	mainScreen.setKeyRepeatEnabled(true);

	ResumeTexture.loadFromFile("menu.png");
	menuBackgroundExitTexture.loadFromFile("menu_exit.png");
	menuTexture.loadFromFile("menu.png");
	healthTexture.loadFromFile("health.png");
	speedTexture.loadFromFile("speed.png");
	ammoTexture.loadFromFile("ammo.png");
	healthBarTexture.loadFromFile("HP.png");
	planeTexture.loadFromFile("Ao192.png");
	plane2Texture.loadFromFile("Bf110e.png");
	fontHealth.loadFromFile("Font.ttf");

	resumeBackground.setTexture(ResumeTexture);
	menuExitBackground.setTexture(menuBackgroundExitTexture);
	menuBackground.setTexture(menuTexture);
	healthSprite.setTexture(healthTexture);
	ammoSprite.setTexture(ammoTexture);
	speedSprite.setTexture(speedTexture);
	HP.setTexture(healthBarTexture);
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

	gameStatus.setFont(fontHealth);
	gameStatus.setCharacterSize(100);
	gameStatus.setFillColor(Color::White);

	Clock timeGone;
	int opt = 1;
	int harta = 1;
	textureBackground.loadFromFile("map_no_1_bg.jpg");
	spriteBackground.setTexture(textureBackground);
	citire(harta);

	Texture CrateTexture;
	if (harta == 1)
		CrateTexture.loadFromFile("crate.png");
	else
		if (harta == 2)
			CrateTexture.loadFromFile("crate_2.png");
		else
			if (harta == 3)
				CrateTexture.loadFromFile("crate_3.png");
	Sprite obstacol[100];

	for (int i = 0; i < 100; i++)
	{
		obstacol[i].scale(Vector2f(0.3, 0.3));
		obstacol[i].setTexture(CrateTexture);
	}


	int nr = -1;
	for (int i = 0; i<14; i++)
		for (int j = 0; j<23; j++)
			if (matrix[i][j])
				obstacol[++nr].setPosition(Vector2f(j * 60, i * 60));
	while (mainScreen.isOpen()) {
		mainScreen.setMouseCursorVisible(false);
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
						case 1:
							opt = 21;
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
			if (opt == 21)
		{
				sf::Event menuEvent;
				while (mainScreen.pollEvent(menuEvent))
				{
					switch (menuEvent.type)
					{
					case Event::KeyPressed:
						switch (menuEvent.key.code)
						{
						case::Keyboard::Left:
							if(itemCurentDif>1)
								moveLeft(itemCurentDif, optiuneaDif, 2);
							break;
						case::Keyboard::Right:
							if(itemCurentDif<3)
								moveRight(itemCurentDif, optiuneaDif, 2);
							break;
						case::Keyboard::Return:
							switch (itemCurentDif)
							{
							case 1:
								harta=1;
								textureBackground.loadFromFile("map_no_1_bg.jpg");
								spriteBackground.setTexture(textureBackground);
								if (harta == 1)
									CrateTexture.loadFromFile("crate.png");
								else
									if (harta == 2)
										CrateTexture.loadFromFile("crate_2.png");
									else
										if (harta == 3)
											CrateTexture.loadFromFile("crate_3.png");
								nr = -1;
								for (int i = 0; i<14; i++)
									for (int j = 0; j<23; j++)
										if (matrix[i][j])
											obstacol[++nr].setPosition(Vector2f(j * 60, i * 60));
								for (int i = 0; i < 100; i++)
								{
									obstacol[i].setTexture(CrateTexture);
								}

								opt = 1;
								break;
							case 2:
								harta=2;
								textureBackground.loadFromFile("map_no_2_bg.png");
								spriteBackground.setTexture(textureBackground);
								if (harta == 1)
									CrateTexture.loadFromFile("crate.png");
								else
									if (harta == 2)
										CrateTexture.loadFromFile("crate_2.png");
									else
										if (harta == 3)
											CrateTexture.loadFromFile("crate_3.png");
								nr = -1;
								for (int i = 0; i<14; i++)
									for (int j = 0; j<23; j++)
										if (matrix2[i][j])
											obstacol[++nr].setPosition(Vector2f(j * 60, i * 60));
								for (int i = 0; i < 100; i++)
								{
									obstacol[i].setTexture(CrateTexture);
								}

								opt = 1;
								break;
							case 3:
								harta=3;
								textureBackground.loadFromFile("map_no_3_bg.png");
								spriteBackground.setTexture(textureBackground);
								if (harta == 1)
									CrateTexture.loadFromFile("crate.png");
								else
									if (harta == 2)
										CrateTexture.loadFromFile("crate_2.png");
									else
										if (harta == 3)
											CrateTexture.loadFromFile("crate_3.png");
								nr = -1;
								for (int i = 0; i<14; i++)
									for (int j = 0; j<23; j++)
										if (matrix3[i][j])
											obstacol[++nr].setPosition(Vector2f(j * 60, i * 60));
								for (int i = 0; i < 100; i++)
								{
									obstacol[i].setTexture(CrateTexture);
								}

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
				mainScreen.draw(menuExitBackground);
				mainScreen.draw(map1);
				mainScreen.draw(map2);
				mainScreen.draw(map3);
				for (int i = 0; i < 4; i++)
					mainScreen.draw(optiuneaDif[i]);
				mainScreen.display();
		}
		else if (opt == 7)
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
						if (itemCurentOpt>1)
							moveUp(itemCurentOpt, optiuneaOpt, 5);
						break;
					case::Keyboard::Down:
						moveDown(itemCurentOpt, optiuneaOpt, 5);
						break;
					case::Keyboard::Return:
						switch (itemCurentOpt)
						{
							break;
						case 1:
							opt = 5;
							break;
						case 2:
							opt = 50;
							break;
						case 3:
							opt = 100;
							break;
						case 4:
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
			for (int i = 0; i < 5; i++)
				mainScreen.draw(optiuneaOpt[i]);
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
								opt = 7;
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
				if (mainTank.checkIfAlive())
				{
					//first we have to handle the player's input
					if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
					{
						//	cout << endl << " DA " << endl;
						mainTank.movePlayer('u', nr, obstacol); //era 1.5 peste tot dar tancul se misca prea repede
						tankSpeed = rand() % 1000;
						tankSpeed /= 1000;
						tankSpeed = tankSpeed - mainTank.getSpeed() * 300;
						srand(time(0));
						tankSpeed += rand() % 5;
					}
					else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
					{
						mainTank.movePlayer('l', nr, obstacol);
					}
					else if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
					{
						mainTank.movePlayer('r', nr, obstacol);
					}
					else if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
					{
						mainTank.movePlayer('d', nr, obstacol);
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

							bullets[currentBullet].shoot(tankXX, tankYY, xOrigin, yOrigin, rotation);
							currentBullet++;
							if (currentBullet >= playerNumberBullets)
							{
								currentBullet = 0;
							}
						}

					}
					tankX = mainTank.getXorigin();
					tankY = mainTank.getYorigin();
				}

				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					opt = 1;
				}
				double chaserRotation = (double)chaser.rotationOfChaser();


				if (chaserLife > 0)
				{
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
						if (okayGo == 1)
						{
							chaser.moveChaser('r', 0.15);
							chaser.rotate();
						}
						else if (okayGo == 2)
						{
							chaser.moveChaser('l', 0.15);
							chaser.rotate();
						}
					}
					if (abs(chaserRotation - rotationNeeded) < 1.5 && !chaser.isInMotion())
					{
						chaser.doNotRotate();
						okayGo = 0;
						path = chaser.pathToPlayer(tankX, tankY);
						changePath = path;
					}
					if (chaser.isInMotion() && path != 0)
					{
						chaser.moveChaser('d', 0.15);
						path--;
					}
					if (path < 0)
					{
						chaser.rotate();
						rotationNeeded = chaser.rotationNeeded(tankX, tankY);
					}
					else if ((changePath - path  > 0) && (changePath - path < 3))
					{
						chaser.moveChaser('l', 0.2);
						chaser.rotate();
						tankX = mainTank.getXorigin();
						tankY = mainTank.getYorigin();
						rotationNeeded = chaser.rotationNeeded(tankX, tankY);
					}
					int x = rand() % 10;
					if (x % 7 == 0 )
					{
						chaser.moveChaser('r', 0.2);
						chaser.rotate();
						if (chaserBullets[chaserCurrentBullet].isInFlight() != true)
						{
							//the next section will calculate the direction in which the bullet is fired
							float chaserXX = chaser.getXorigin();
							float chaserYY = chaser.getYorigin();
							chaser.goodPoint(chaserXX, chaserYY);
							double rotation = (double)chaser.rotationOfChaser();
							chaserBullets[chaserCurrentBullet].thirdPoint(chaserXX, chaserYY, chaserRotation, xOrigin, yOrigin, X, Y);
							chaserBullets[chaserCurrentBullet].shoot(chaserXX, chaserYY, xOrigin, yOrigin, chaserRotation);
							chaserCurrentBullet++;
							if (chaserCurrentBullet > 1)
							{
								chaserCurrentBullet = 0;
							}
						}
					}
				}
				//-----------------------------chaser 2 try --------------------------------chaser 2 try--------------------------------chaser 2 try-----------
				if (chaser2Life > 0)
				{
					if (!chaser2.isInMotion())
					{
						double A2, D2;
						if (chaser2Rotation > rotationNeeded2 && okayGo2 == 0)
						{
							A2 = chaser2Rotation - rotationNeeded2;
							D2 = 360 - A2;
						}
						else if (chaser2Rotation < rotationNeeded2 && okayGo2 == 0)
						{
							D2 = rotationNeeded2 - chaser2Rotation;
							A2 = 360 - D2;
						}
						if (A2 > D2 && !okayGo2)
						{
							okayGo2 = 1;
						}
						else if (A2 < D2 && !okayGo2)
						{
							okayGo2 = 2;
						}
						if (okayGo == 1)
						{
							chaser2.moveChaser('r', 1.5);
							chaser2.rotate();
						}
						else if (okayGo2 == 2)
						{
							chaser2.moveChaser('l', 1.5);
							chaser2.rotate();
						}
					}
					//------------------------------------------------DE AICI INCEPE RANDOM MOVEMENT------------------------------------------------------------------------
					if (abs(chaser2Rotation - rotationNeeded2) < 1 && !chaser2.isInMotion())
					{
						if (chaser2Rotation < 100 && chaser2Rotation > 230 || (chaser2Rotation > 250 || chaser2Rotation < 20))
						{
							variabila = rand() % 1000;
							while (variabila < 200)
							{
								variabila = rand() % 1000;
							}
						}
						else
						{
							variabila = rand() % 400;
							while (variabila < 200)
							{
								variabila = rand() % 500;
							}
						}
						chaser2.doNotRotate();
					}
					if (variabila != 0 && chaser2.isInMotion() && variabila % 2 == 0)
					{
						chaser2.moveChaser('u', 1.5);
						variabila -= 2;
					}
					else if (variabila % 2 == 1)
					{
						chaser2.moveChaser('d', 1.5);
						if (variabila == 1)
						{
							variabila = 0;
						}
						else
						{
							variabila -= 2;
						}
					}
					if (variabila < 10)
					{
						chaser2.rotate();
						okayGo2 = 0;
						rotationNeeded2 = rand() % 360;
						if (chaser2Rotation > rotationNeeded2)
						{
							okayGo2 = 2;
						}
					}


					int x = rand() % 11;
					if (x % 10 == 0)
					{
						if (chaser2Bullets[chaser2CurrentBullet].isInFlight() != true)
						{
							//the next section will calculate the direction in which the bullet is fired
							float chaser2XX = chaser2.getXorigin();
							float chaser2YY = chaser2.getYorigin();
							chaser2.goodPoint(chaser2XX, chaser2YY);
							double rotation = (double)chaser2.rotationOfChaser();
							chaser2Bullets[chaser2CurrentBullet].thirdPoint(chaser2XX, chaser2YY, chaserRotation, xOrigin, yOrigin, X, Y);
							chaser2Bullets[chaser2CurrentBullet].shoot(chaser2XX, chaser2YY, xOrigin, yOrigin, chaserRotation);
							chaser2CurrentBullet++;
							if (chaser2CurrentBullet > 1)
							{
								chaser2CurrentBullet = 0;
							}
						}
					}
				}

				// Actualizarea pt bullets in-flight
				for (i = 0; i < playerNumberBullets && mainTank.checkIfAlive(); i++)
				{
					
					if (bullets[i].isInFlight())
					{
						bullets[i].update(0.15);
						if (chaser.checkIfIntersect(bullets[i].getShape()) && chaserLife > 0)
						{
							chaserLife--;
							bullets[i].stop();
						}
						else if (chaser2.checkIfIntersect(bullets[i].getShape()) && chaser2Life > 0)
						{
							chaser2Life--;
							bullets[i].stop();
						}
						if (bullets[i].intersect(obstacol, nr))
						{
							bullets[i].stop();
						}
					}
				}

				//CHASERs BULLETS UPDATE MOVEMENT -----------------------------------------------------------------------------
				for (j = 0; j < 2 && chaserLife > 0; j++)
				{
					if (chaserBullets[j].isInFlight())
					{
						chaserBullets[j].update(0.15);
						int oki = 1;
						
						if (mainTank.checkIfIntersect(chaserBullets[j].getShape()) && mainTank.checkIfAlive() && oki)
						{
							mainTank.lessHealth();
							chaserBullets[j].stop();
						}
						if (chaserBullets[j].intersect(obstacol, nr))
						{
							chaserBullets[j].stop();
						}
					}
				}
				for (k = 0; k < 1 && chaser2Life > 0; k++)
				{
					if (chaser2Bullets[k].isInFlight())
					{
						chaser2Bullets[k].update(0.15);
						if (chaser2Bullets[k].intersect(obstacol, nr))
						{
							chaser2Bullets[k].stop();
						}
						if (mainTank.checkIfIntersect(chaser2Bullets[k].getShape()) && mainTank.checkIfAlive())
						{
							mainTank.lessHealth();
							chaser2Bullets[k].stop();
						}
					}
				}
				mainScreen.clear();

				mainScreen.draw(spriteBackground);
				stringstream string1, string2, string3;
				string1 << "Integrity: " << mainTank.getHealth();
				healthLevel.setString(string1.str());
				string2 << "Speed: " << tankSpeed << " KM/H";
				SpeedTank.setString(string2.str());
				for (int i = 0; i <= nr; i++)
					mainScreen.draw(obstacol[i]);
				mainScreen.draw(healthLevel);
				mainScreen.draw(SpeedTank);
				mainScreen.draw(healthBarEmpty);
				mainScreen.draw(healthBar);
				mainScreen.draw(HP);

				if (mainTank.checkIfAlive())
				{
					mainTank.drawPlayer(mainScreen);
				}
				else
				{
					explosionAnimationTank += 1;
					bool boomTank = explosion.animation(explosionAnimationTank);
					explosion.drawExplosion(mainScreen, boomTank, tankX, tankY);
					string3 << "GAME OVER";
					gameStatus.setString(string3.str());
					gameStatus.setPosition(400, 320);
					mainScreen.draw(gameStatus);
				}

				for (int i = 0; i <= nr; i++)
				{
					if (ammoSpawned == true && ammoSprite.getGlobalBounds().intersects(obstacol[i].getGlobalBounds()))
					{
						ammoSinceDespawn = 0;
						ammoSpawned = false;
					}
					if (healthSpawned == true && healthSprite.getGlobalBounds().intersects(obstacol[i].getGlobalBounds()))
					{
						healthSinceDespawn = 0;
						healthSpawned = false;
					}
					if (speedSpawned == true && speedSprite.getGlobalBounds().intersects(obstacol[i].getGlobalBounds()))
					{
						speedSinceDespawn = 0;
						speedSpawned = false;
					}
				}
				if (ammoSinceSpawn > 10 && ammoSpawned == true)
				{
					ammoSinceDespawn = 0;
					ammoSpawned = false;
				}
				if (healthSinceSpawn > 11 && healthSpawned == true)
				{
					healthSinceDespawn = 0;
					healthSpawned = false;
				}
				if (speedSinceSpawn > 13 && speedSpawned == true)
				{
					speedSinceDespawn = 0;
					speedSpawned = false;
				}
				if (mainTank.checkIfIntersect(ammoSprite))
				{
					ammoSpawned = false;
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

				for (i = 0; i < 2; ++i)
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
				for (k = 0; k < 1; ++k)
				{
					if (chaser2Bullets[k].isInFlight())
					{
						mainScreen.draw(chaser2Bullets[k].getShape());
					}
				}

				//mainAI.draw_ai_Entity(mainScreen); we don't have this entity yet
				if (chaserLife > 0)
				{
					chaser.drawAI_Chaser(mainScreen, 1);
				}
				else
				{
					c1Dead = true;
					explosionAnimation += 1;
					chaserX = chaser.getXorigin();
					chaserY = chaser.getYorigin();
					bool boom = explosion.animation(explosionAnimation);
					explosion.drawExplosion(mainScreen, boom, chaserX, chaserY);
				}

				if (chaser2Life > 0)
				{
					chaser2.drawAI_Chaser(mainScreen, 2);
				}
				else
				{
					c2Dead = true;
					explosionAnimation2 += 1;
					chaser2X = chaser2.getXorigin();
					chaser2Y = chaser2.getYorigin();
					bool boom2 = explosion.animation(explosionAnimation);
					explosion.drawExplosion(mainScreen, boom2, chaser2X, chaser2Y);
				}
				if (c1Dead && c2Dead)
				{
					string3 << "YOU WON, CONGRATZ!";
					gameStatus.setString(string3.str());
					gameStatus.setPosition(200, 320);
					mainScreen.draw(gameStatus);
				}
				mainScreen.draw(plane);
				mainScreen.draw(plane2);
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
								moveLeft(itemCurentExit, optiuneaExit, 1);
								break;
							case::Keyboard::Right:
								moveRight(itemCurentExit, optiuneaExit, 1);
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
