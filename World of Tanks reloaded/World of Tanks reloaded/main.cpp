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
Text optiunea[4], optiuneaExit[3], optiuneaResume[3], optiuneaDif[5], optiuneaOpt[5], optiuneaPlayer[3], optiuneHowToPlay[2];

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
	optiuneaDif[0].setPosition(Vector2f(1366 / 3+120, 768 / 5 * 1 + 70));

	optiuneaDif[1].setFont(textStyle);
	optiuneaDif[1].setFillColor(Color::Red);
	optiuneaDif[1].setString("Malinovka");
	optiuneaDif[1].setPosition(Vector2f(1366 / 4 - 100, 768 / 3 * 2));

	optiuneaDif[2].setFont(textStyle);
	optiuneaDif[2].setFillColor(Color::White);
	optiuneaDif[2].setString("Siegefield");
	optiuneaDif[2].setPosition(Vector2f(1366 / 4 * 2 - 100, 768 / 3 * 2));

	optiuneaDif[3].setFont(textStyle);
	optiuneaDif[3].setFillColor(Color::White);
	optiuneaDif[3].setString("Stalingrad");
	optiuneaDif[3].setPosition(Vector2f(1366 / 4 * 3 - 100, 768 / 3 * 2));

	/*optiuneaDif[4].setFont(textStyle);
	optiuneaDif[4].setFillColor(Color::White);
	optiuneaDif[4].setString("Next setting: ");
	optiuneaDif[4].setPosition(Vector2f(1366 / 3 + 100, 768 / 5 * 4 + 70));*/

}
/*
void setOptionsPlayer()
{
	if (!textStyle.loadFromFile("Font.ttf"))
		cout << "Error loading font!";

	optiuneaPlayer[0].setFont(textStyle);
	optiuneaPlayer[0].setFillColor(Color::White);
	optiuneaPlayer[0].setString("( 2 out of 2 ) Number of human players: ");
	optiuneaPlayer[0].setPosition(Vector2f(1366 / 3 - 80, 768 / 5 * 1 + 70));

	optiuneaPlayer[1].setFont(textStyle);
	optiuneaPlayer[1].setFillColor(Color::Red);
	optiuneaPlayer[1].setString("1 human player");
	optiuneaPlayer[1].setPosition(Vector2f(1366 / 4 + 200, 768 / 3 * 1 + 150));

	optiuneaPlayer[2].setFont(textStyle);
	optiuneaPlayer[2].setFillColor(Color::White);
	optiuneaPlayer[2].setString("2 human players");
	optiuneaPlayer[2].setPosition(Vector2f(1366 / 4 + 200, 768 / 3 * 2));
}
*/
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
void howToPlay()
{
	if (!textStyle.loadFromFile("Font.ttf"))
		cout << "Error loading font!";
	optiuneHowToPlay[0].setFont(textStyle);
	optiuneHowToPlay[0].setFillColor(Color::Red);
	optiuneHowToPlay[0].setString("Back");
	optiuneHowToPlay[0].setPosition(Vector2f(1366 / 3 + 200, 768 - 100));
	optiuneHowToPlay[1].setFont(textStyle);
	optiuneHowToPlay[1].setFillColor(Color::White);
	optiuneHowToPlay[1].setString("Next");
	optiuneHowToPlay[1].setPosition(Vector2f(1366 / 3 + 600, 768 - 100));
}

int main()
{
	setOptions();
	setOptionsExit();
	setOptionsOpt();
	resumeGame();
	setOptionsDif();
	howToPlay();
	//setOptionsPlayer();
	RenderWindow mainScreen(VideoMode(1366, 768), "World of Tanks reloaded", Style::Fullscreen);
	Player mainTank("E-100.png");
	Player secondTank("T34.png");

	secondTank.setPostion();
	int no_players = 1;
	//ai_Entity mainAI("Ferdinand.png");
	AI_Chaser chaser("E-1002.png", 1);
	AI_Chaser chaser2("T-59.png", 2);
	AI_Chaser chaser3("Ferdinand.png", 3);
	//---------------------------------------------------------------------------------------------------------------
	float tankX = mainTank.getXorigin();
	float tankY = mainTank.getYorigin();
	float rotationNeeded = chaser.rotationNeeded(tankX, tankY);
	float rotationNeeded2 = chaser2.rotationNeeded(tankX, tankY);
	float rotationNeeded3 = chaser3.rotationNeeded(tankX, tankY);
	float path, changePath;
	int ok = 1, okayGo = 0;
	Bullet chaserBullets[3];
	int chaserCurrentBullet = 0, j;
	int chaserLife = 3;
	srand(time(NULL));
	//------------------------------------FOR SECOND TANK ------------------FOR BULLETS-----------------------------------------
	float secondTankX = secondTank.getXorigin();
	float secondTankY = secondTank.getYorigin();
	Bullet secondTankBullets[10];
	int currentBulletSec = 0, t;
	int player2NumberBullets = 1;
	//---------------------------------------------------CHASER3 BOY!-----------------------------------------------------------------------------------
	float chaser3X, chaser3Y; //= chaser3.rotationOfChaser(); //rotationNeeded3 = chaser3.rotationNeeded(tankX, tankY)
	int variabila, okayGo3 = 0;
	Bullet chaser3Bullets[3];
	int chaser3CurrentBullet = 0, p;
	int chaser3Life = 5;
	bool c3Dead = false;
	float path3 = 0, changePath3;
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
	float chaser2X, chaser2Y, chaser2Rotation = chaser2.rotationOfChaser(); //rotationNeeded2 = chaser2.rotationNeeded(tankX, tankY);
	int okayGo2 = 0;
	Bullet chaser2Bullets[3];
	int chaser2CurrentBullet = 0, k;
	int chaser2Life = 5;
	float path2 = 0, changePath2;
	//------------------------------------------------------------------------------------------------------------------------------------------------
	bool c1Dead = false, c2Dead = false;
	unsigned int explosionAnimation = 0, explosionAnimation2 = 0, explosionAnimationTank = 0, explosionAnimation3 = 0, explosionAnimationTanks = 0;
	explosion explosion, explosions, exp1, exp2, exp3;
	Text gameStatus;
	Bullet bullets[10];
	int currentBullet = 0, i;

	Event Event;
	Texture healthBarTexture, textureBackground, planeTexture, plane2Texture, healthTexture, speedTexture, ammoTexture, menuTexture, menuBackgroundExitTexture, ResumeTexture;
	Sprite HP2, HP, spriteBackground, stone0, plane, plane2, healthSprite, healthSprite2, ammoSprite, speedSprite, menuBackground, menuExitBackground, resumeBackground;
	RectangleShape healthBar, healthBar2, healthBarEmpty, healthBarEmpty2;

	Text healthLevel, healthLevel2, SpeedTank, SpeedTank2;
	Font fontHealth;
	bool planeActive = false, plane2Active = false, ammoSpawned = false, speedSpawned = false, healthSpawned = false;
	float planeSpeed = 0.0f, plane2Speed = 0.0f, TIMP = 0, ammoSinceDespawn = 0, healthSinceDespawn = 0, speedSinceDespawn = 0, ammoSinceSpawn = 0, healthSinceSpawn = 0, speedSinceSpawn = 0;
	int health = mainTank.getHealth(), itemCurent = 0, itemCurentExit = 2, itemCurentResume = 0, itemCurentDif = 1, itemCurentOpt = 1, itemCurentPlayer = 1;
	int health2 = secondTank.getHealth();

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


	map1.setPosition(1366 / 4 - 160, 768 / 3 + 50);
	map2.setPosition(1366 / 4 * 2 - 160, 768 / 3 + 50);
	map3.setPosition(1366 / 4 * 3 - 160, 768 / 3 + 50);


	mainScreen.setKeyRepeatEnabled(true);

	Texture playerTexture;
	playerTexture.loadFromFile("player.png");
	Sprite playerBackground;
	playerBackground.setTexture(playerTexture);
	playerBackground.setPosition(0, 0);

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
	healthSprite2.setTexture(healthTexture);

	ammoSprite.setTexture(ammoTexture);
	speedSprite.setTexture(speedTexture);


	HP.setTexture(healthBarTexture);
	HP2.setTexture(healthBarTexture);


	plane.setTexture(planeTexture);
	plane2.setTexture(plane2Texture);

	resumeBackground.setPosition(0, 0);
	menuBackground.setPosition(0, 0);
	HP.setPosition(1000, 20);
	HP2.setPosition(1000, 590);
	stone0.setPosition(100, 550);
	spriteBackground.setPosition(0, 0);

	healthBar2.setPosition(1070, 600);
	healthBar.setPosition(1070, 30);

	plane2.scale(0.3f, 0.3f);


	healthBarEmpty.setPosition(1070, 30);
	healthBarEmpty2.setPosition(1070, 600);


	healthSprite.setScale(0.2f, 0.2f);
	ammoSprite.setScale(0.1f, 0.1f);
	speedSprite.setScale(0.15f, 0.15f);

	HP.setScale(0.4f, 0.4f);
	HP2.setScale(0.4f, 0.4f);


	plane.scale(0.3f, 0.3f);

	planeTexture.setSmooth(true);
	plane2Texture.setSmooth(true);



	healthBar.setFillColor(Color(120, 201, 32));
	healthBarEmpty.setFillColor(Color(255, 0, 0, 200));
	healthBarEmpty.setSize(Vector2f(260, 30));


	healthBar2.setFillColor(Color(120, 201, 32));
	healthBarEmpty2.setFillColor(Color(255, 0, 0, 200));
	healthBarEmpty2.setSize(Vector2f(260, 30));

	healthLevel.setFont(fontHealth);
	healthLevel.setCharacterSize(30);
	healthLevel.setFillColor(Color::White);

	healthLevel2.setFont(fontHealth);
	healthLevel2.setCharacterSize(30);
	healthLevel2.setFillColor(Color::White);


	SpeedTank.setFont(fontHealth);
	SpeedTank.setCharacterSize(30);
	SpeedTank.setFillColor(Color::White);


	SpeedTank2.setFont(fontHealth);
	SpeedTank2.setCharacterSize(30);
	SpeedTank2.setFillColor(Color::White);

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
	for (int i = 0; i < 14; i++)
		for (int j = 0; j < 23; j++)
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
								if (itemCurentDif > 1)
									moveLeft(itemCurentDif, optiuneaDif, 2);
								break;
							case::Keyboard::Right:
								if (itemCurentDif < 3)
									moveRight(itemCurentDif, optiuneaDif, 2);
								break;
							/*case::Keyboard::Down:
								if (itemCurentDif != 4)
								{
									optiuneaDif[itemCurentDif].setFillColor(Color::White);
									itemCurentDif = 4;
									optiuneaDif[itemCurentDif].setFillColor(Color::Red);
								}
								break;
							case::Keyboard::Up:
								if (itemCurentDif == 4)
								{
									optiuneaDif[itemCurentDif].setFillColor(Color::White);
									itemCurentDif = 1;
									optiuneaDif[itemCurentDif].setFillColor(Color::Red);
								}
								break;*/
							case::Keyboard::Return:
								switch (itemCurentDif)
								{
								case 1:
									harta = 1;
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
									for (int i = 0; i < 14; i++)
										for (int j = 0; j < 23; j++)
											if (matrix[i][j])
												obstacol[++nr].setPosition(Vector2f(j * 60, i * 60));
									for (int i = 0; i < 100; i++)
									{
										obstacol[i].setTexture(CrateTexture);
									}

									opt = 1;
									break;
								case 2:
									harta = 2;
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
									for (int i = 0; i < 14; i++)
										for (int j = 0; j < 23; j++)
											if (matrix2[i][j])
												obstacol[++nr].setPosition(Vector2f(j * 60, i * 60));
									for (int i = 0; i < 100; i++)
									{
										obstacol[i].setTexture(CrateTexture);
									}

									opt = 1;
									break;
								//case 4:
								//	opt = 66;
								//	break;
								case 3:
									harta = 3;
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
									for (int i = 0; i < 14; i++)
										for (int j = 0; j < 23; j++)
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
					for (int i = 0; i < 5; i++)
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
								if (itemCurentOpt > 1)
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
							secondTank.restart();
							secondTank.setPostion();
							c1Dead = false;
							c2Dead = false;
							chaser2Life = 5;
							chaserLife = 3;
							chaser.restart(1);
							chaser.restart(2);
							opt = 3;
						}
						else
							if (opt == 3)
							{
								healthLevel.setPosition(1017, 65);
								SpeedTank.setPosition(1017, 125);

								healthLevel2.setPosition(1017, 640);
								SpeedTank2.setPosition(1017, 700);

								Time dt = timeGone.restart();

								if (dt.asSeconds() < 1)
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
									if (opt == 3)plane2.setPosition(plane2.getPosition().x + (plane2Speed * TIMP), plane2.getPosition().y);
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

								float tankSpeed = 0, tankSpeed2 = 0;

								healthBar.setSize(Vector2f(mainTank.getHealth()*2.6, 30));
								healthBar2.setSize(Vector2f(secondTank.getHealth()*2.6, 30));

								//--------------------SECOND TANKS MOVEMENT----------------------------
								if (secondTank.checkIfAlive())
								{
									if (Keyboard::isKeyPressed(Keyboard::Down))
									{
										secondTank.movePlayer('u', nr, obstacol);
										tankSpeed2 = rand() % 1000;
										tankSpeed2 /= 1000;
										tankSpeed2 = tankSpeed2 - secondTank.getSpeed() * 300;
										srand(time(0));
										tankSpeed2 += rand() % 5;
									}
									else if (Keyboard::isKeyPressed(Keyboard::Right))
									{
										secondTank.movePlayer('l', nr, obstacol);
									}
									else if (Keyboard::isKeyPressed(Keyboard::Left))
									{
										secondTank.movePlayer('r', nr, obstacol);
									}
									else if (Keyboard::isKeyPressed(Keyboard::Up))
									{
										secondTank.movePlayer('d', nr, obstacol);
										tankSpeed2 = rand() % 1000;
										tankSpeed2 /= 1000;
										tankSpeed2 = tankSpeed2 + secondTank.getSpeed() * 300;
										srand(time(0));
										tankSpeed2 += rand() % 5;
									}
									// Fire a bullet
									if (Keyboard::isKeyPressed(Keyboard::RControl))
									{
										if (secondTankBullets[currentBulletSec].isInFlight() != true)
										{
											float tankXX2;
											float tankYY2;
											secondTank.goodPoint(tankXX2, tankYY2);
											double rotation = (double)secondTank.rotationOfPlayer();
											secondTankBullets[currentBulletSec].thirdPoint(tankXX2, tankYY2, rotation, xOrigin, yOrigin, X, Y);
											//if (currentBulletSec < player2NumberBullets)
											//{
											secondTankBullets[currentBulletSec].shoot(tankXX2, tankYY2, xOrigin, yOrigin, rotation);
											//}

											currentBulletSec++;
											if (currentBulletSec >= player2NumberBullets)
											{
												currentBulletSec = 0;
											}
										}

									}
								}
								//--------------------SECOND TANKS MOVEMENT END ----------------------------


								if (mainTank.checkIfAlive())
								{
									//first we have to handle the player's input
									if (Keyboard::isKeyPressed(Keyboard::S))
									{
										mainTank.movePlayer('u', nr, obstacol);
										tankSpeed = rand() % 1000;
										tankSpeed /= 1000;
										tankSpeed = tankSpeed - mainTank.getSpeed() * 300;
										srand(time(0));
										tankSpeed += rand() % 5;
									}
									else if (Keyboard::isKeyPressed(Keyboard::D))
									{
										mainTank.movePlayer('l', nr, obstacol);
									}
									else if (Keyboard::isKeyPressed(Keyboard::A))
									{
										mainTank.movePlayer('r', nr, obstacol);
									}
									else if (Keyboard::isKeyPressed(Keyboard::W))
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
											chaser.moveChaser('r', 0.15, nr, obstacol);
											chaser.rotate();
										}
										else if (okayGo == 2)
										{
											chaser.moveChaser('l', 0.15, nr, obstacol);
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
										chaser.moveChaser('d', 0.15, nr, obstacol);
										path--;
									}
									if (path < 0)
									{
										chaser.rotate();
										rotationNeeded = chaser.rotationNeeded(tankX, tankY);
									}
									else if ((changePath - path > 0) && (changePath - path < 3))
									{
										chaser.moveChaser('l', 0.2, nr, obstacol);
										chaser.rotate();
										tankX = mainTank.getXorigin();
										tankY = mainTank.getYorigin();
										rotationNeeded = chaser.rotationNeeded(tankX, tankY);
									}
									int x = rand() % 10;
									if (x % 7 == 0)
									{
										chaser.moveChaser('r', 0.2, nr, obstacol);
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
								// Actualizarea pt bullets in-flight
								for (t = 0; t < player2NumberBullets && secondTank.checkIfAlive(); t++)
								{

									if (secondTankBullets[t].isInFlight())
									{
										secondTankBullets[t].update(0.15);
										if (chaser.checkIfIntersect(secondTankBullets[t].getShape()) && chaserLife > 0)
										{
											chaserLife--;
											secondTankBullets[t].stop();
										}
										/*else if (chaser2.checkIfIntersect(bullets[i].getShape()) && chaser2Life > 0)
										{
											chaser2Life--;
											bullets[i].stop();
										}*/
										if (secondTankBullets[t].intersect(obstacol, nr))
										{
											secondTankBullets[t].stop();
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
								/*for (k = 0; k < 1 && chaser2Life > 0; k++)
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
								}*/
								mainScreen.clear();
								mainScreen.draw(spriteBackground);
								stringstream string1, string2, string3, string4, string5;

								string1 << "Integrity: " << mainTank.getHealth();
								healthLevel.setString(string1.str());
								string2 << "Speed: " << tankSpeed << " KM/H";
								SpeedTank.setString(string2.str());

								string5 << "Integrity: " << secondTank.getHealth();
								healthLevel2.setString(string5.str());
								string4 << "Speed: " << tankSpeed2 << " KM/H";
								SpeedTank2.setString(string4.str());

								for (int i = 0; i <= nr; i++)
									mainScreen.draw(obstacol[i]);


								mainScreen.draw(healthLevel);
								mainScreen.draw(healthLevel2);

								mainScreen.draw(SpeedTank);
								mainScreen.draw(SpeedTank2);

								mainScreen.draw(healthBarEmpty);
								mainScreen.draw(healthBarEmpty2);

								mainScreen.draw(healthBar2);
								mainScreen.draw(healthBar);

								mainScreen.draw(HP2);
								mainScreen.draw(HP);

								if (secondTank.checkIfAlive())
									secondTank.drawPlayer(mainScreen);

								if (mainTank.checkIfAlive())
									mainTank.drawPlayer(mainScreen);
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


								//-------------------------SECOND TANK PICKUP

								if (secondTank.checkIfIntersect(ammoSprite))
								{
									ammoSpawned = false;
									ammoSinceDespawn = 0;
								}
								if (secondTank.checkIfIntersect(healthSprite) && healthSpawned)
								{
									secondTank.updateHealth();
									healthSpawned = false;
									healthSinceDespawn = 0;
								}
								if (secondTank.checkIfIntersect(speedSprite) && speedSpawned)
								{
									secondTank.updateSpeed();
									speedSpawned = false;
									speedSinceDespawn = 0;
								}
								//-------------------------SECOND TANK PICKUP ENDDDDDDDDDDDDDDDDDDDDDDDDDd

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

								for (t = 0; t < player2NumberBullets; ++t)
								{
									if (secondTankBullets[t].isInFlight())
									{
										mainScreen.draw(secondTankBullets[t].getShape());
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

						
								if (c1Dead) 
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







								else if (opt == 50)
								{
									healthLevel.setPosition(1017, 65);
									SpeedTank.setPosition(1017, 100);

									Time dt = timeGone.restart();

									if (dt.asSeconds() < 1)
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
										if (opt == 3)plane2.setPosition(plane2.getPosition().x + (plane2Speed * TIMP), plane2.getPosition().y);
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

									float tankSpeed = 0, tankSpeed2 = 0;

									healthBar.setSize(Vector2f(mainTank.getHealth()*2.6, 30));

									//mainAI.BuildPathToTarget(mainTank.getXorigin(), mainTank.getYorigin());
									if (mainTank.checkIfAlive())
									{
										//first we have to handle the player's input
										if (Keyboard::isKeyPressed(Keyboard::S))
										{
											//	cout << endl << " DA " << endl;
											mainTank.movePlayer('u', nr, obstacol); //era 1.5 peste tot dar tancul se misca prea repede
											tankSpeed = rand() % 1000;
											tankSpeed /= 1000;
											tankSpeed = tankSpeed - mainTank.getSpeed() * 300;
											srand(time(0));
											tankSpeed += rand() % 5;
										}
										else if (Keyboard::isKeyPressed(Keyboard::D))
										{
											mainTank.movePlayer('l', nr, obstacol);
										}
										else if (Keyboard::isKeyPressed(Keyboard::A))
										{
											mainTank.movePlayer('r', nr, obstacol);
										}
										else if (Keyboard::isKeyPressed(Keyboard::W))
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


									//--------------------SECOND TANKS MOVEMENT----------------------------
									if (secondTank.checkIfAlive())
									{
										if (Keyboard::isKeyPressed(Keyboard::Down))
										{
											secondTank.movePlayer('u', nr, obstacol);
											tankSpeed2 = rand() % 1000;
											tankSpeed2 /= 1000;
											tankSpeed2 = tankSpeed2 - secondTank.getSpeed() * 300;
											srand(time(0));
											tankSpeed2 += rand() % 5;
										}
										else if (Keyboard::isKeyPressed(Keyboard::Right))
										{
											secondTank.movePlayer('l', nr, obstacol);
										}
										else if (Keyboard::isKeyPressed(Keyboard::Left))
										{
											secondTank.movePlayer('r', nr, obstacol);
										}
										else if (Keyboard::isKeyPressed(Keyboard::Up))
										{
											secondTank.movePlayer('d', nr, obstacol);
											tankSpeed2 = rand() % 1000;
											tankSpeed2 /= 1000;
											tankSpeed2 = tankSpeed2 + secondTank.getSpeed() * 300;
											srand(time(0));
											tankSpeed2 += rand() % 5;
										}
										// Fire a bullet
										if (Keyboard::isKeyPressed(Keyboard::RControl))
										{
											if (secondTankBullets[currentBulletSec].isInFlight() != true)
											{
												float tankXX2;
												float tankYY2;
												secondTank.goodPoint(tankXX2, tankYY2);
												double rotation = (double)secondTank.rotationOfPlayer();
												secondTankBullets[currentBulletSec].thirdPoint(tankXX2, tankYY2, rotation, xOrigin, yOrigin, X, Y);
												
												secondTankBullets[currentBulletSec].shoot(tankXX2, tankYY2, xOrigin, yOrigin, rotation);
												

												currentBulletSec++;
												if (currentBulletSec >= player2NumberBullets)
												{
													currentBulletSec = 0;
												}
											}

										}
									}
									//--------------------SECOND TANKS MOVEMENT END ----------------------------


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
												chaser.moveChaser('r', 0.15, nr, obstacol);
												chaser.rotate();
											}
											else if (okayGo == 2)
											{
												chaser.moveChaser('l', 0.15, nr, obstacol);
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
											chaser.moveChaser('d', 0.15, nr, obstacol);
											path--;
										}
										if (path < 0)
										{
											chaser.rotate();
											rotationNeeded = chaser.rotationNeeded(tankX, tankY);
										}
										else if ((changePath - path > 0) && (changePath - path < 3))
										{
											chaser.moveChaser('l', 0.2, nr, obstacol);
											chaser.rotate();
											tankX = mainTank.getXorigin();
											tankY = mainTank.getYorigin();
											rotationNeeded = chaser.rotationNeeded(tankX, tankY);
										}
										int x = rand() % 10;
										if (x % 7 == 0)
										{
											chaser.moveChaser('r', 0.2, nr, obstacol);
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
									double chaser2Rotation = (double)chaser2.rotationOfChaser();
									if (chaser2Life > 0)
									{

										if (!chaser2.isInMotion())
										{
											double A2, D2;
											//rotationNeeded2 = chaser2.rotationNeeded(tankX, tankY);
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
											if (okayGo2 == 1)
											{
												//chaser2.moveChaser('r', 0.25);
												chaser2.moveChaser('r', 0.15, nr, obstacol);
												chaser2.rotate();
											}
											else if (okayGo2 == 2)
											{
												//chaser2.moveChaser('l', 0.25);
												chaser2.moveChaser('l', 0.15, nr, obstacol);
												chaser2.rotate();
											}

										}
										//------------------------------------------------AI MOVEMENT--------------------------CHASE     CHASE     CHASE------------------------------------------------------------------
										double chaser2Rotation = (double)chaser2.rotationOfChaser();  //??????
										if (abs(chaser2Rotation - rotationNeeded2) < 2 && !chaser2.isInMotion())
										{
											chaser2.doNotRotate();
											okayGo2 = 0;
											path2 = chaser2.pathToPlayer(tankX, tankY);
											changePath2 = path2;

										}
										if (chaser2.isInMotion() && path2 != 0)
										{
											chaser2.moveChaser('d', 0.15, nr, obstacol);
											path2--;
										}
										if (path2 < 0)
										{
											chaser2.rotate();
											tankX = mainTank.getXorigin();
											tankY = mainTank.getYorigin();
											rotationNeeded2 = chaser2.rotationNeeded(tankX, tankY);
										}
										else if ((changePath2 - path2 > 0) && (changePath2 - path2 < 3))
										{
											chaser2.moveChaser('l', 0.2, nr, obstacol);
											chaser2.rotate();
											tankX = mainTank.getXorigin();
											tankY = mainTank.getYorigin();
											rotationNeeded2 = chaser2.rotationNeeded(tankX, tankY);
										}

										int x = rand() % 3;
										if (x % 2 == 0) 
										{
											chaser2.moveChaser('r', 0.2, nr, obstacol);
											chaser2.rotate();
											if (chaser2Bullets[chaser2CurrentBullet].isInFlight() != true)
											{
												//the next section will calculate the direction in which the bullet is fired
												float chaser2XX = chaser2.getXorigin();
												float chaser2YY = chaser2.getYorigin();
												chaser2.goodPoint(chaser2XX, chaser2YY);
												double rotation = (double)chaser2.rotationOfChaser();
												chaser2Bullets[chaser2CurrentBullet].thirdPoint(chaser2XX, chaser2YY, chaser2Rotation, xOrigin, yOrigin, X, Y);
												chaser2Bullets[chaser2CurrentBullet].shoot(chaser2XX, chaser2YY, xOrigin, yOrigin, chaser2Rotation);
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
											else if (secondTank.checkIfIntersect(bullets[i].getShape()) && secondTank.checkIfAlive())
											{
												secondTank.lessHealth();
												bullets[i].stop();
											}
											if (bullets[i].intersect(obstacol, nr))
											{
												bullets[i].stop();
											}
											
										}
									}
									// Actualizarea pt bullets in-flight
									for (t = 0; t < player2NumberBullets && secondTank.checkIfAlive(); t++)
									{

										if (secondTankBullets[t].isInFlight())
										{
											secondTankBullets[t].update(0.15);
											if (chaser.checkIfIntersect(secondTankBullets[t].getShape()) && chaserLife > 0)
											{
												chaserLife--;
												secondTankBullets[t].stop();
											}
											else if (chaser2.checkIfIntersect(secondTankBullets[t].getShape()) && chaser2Life > 0)
											{
												chaser2Life--;
												secondTankBullets[t].stop();
											}
											else if (mainTank.checkIfIntersect(secondTankBullets[t].getShape()) && mainTank.checkIfAlive())
											{
												mainTank.lessHealth();
												secondTankBullets[t].stop();
											}
											if (secondTankBullets[t].intersect(obstacol, nr))
											{
												secondTankBullets[t].stop();
											}
										}
									}
									//CHASERs BULLETS UPDATE MOVEMENT -----------------------------------------------------------------------------
									for (j = 0; j < 2 && chaserLife > 0; j++)
									{
										if (chaserBullets[j].isInFlight())
										{
											chaserBullets[j].update(0.15);

											if (mainTank.checkIfIntersect(chaserBullets[j].getShape()) && mainTank.checkIfAlive())
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

									if (secondTank.checkIfAlive())
										secondTank.drawPlayer(mainScreen);
									else
									{
										float stx = secondTank.getXorigin(), sty = secondTank.getYorigin();
										explosionAnimationTanks += 1;
										bool boomTanks = explosions.animation(explosionAnimationTank);
										explosions.drawExplosion(mainScreen, boomTanks,stx, sty);
										
									}
									if (mainTank.checkIfAlive())
									{
										mainTank.drawPlayer(mainScreen);
									}
									else
									{
										explosionAnimationTank += 1;
										bool boomTank = explosion.animation(explosionAnimationTank);
										explosion.drawExplosion(mainScreen, boomTank, tankX, tankY);
										
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


									//-------------------------SECOND TANK PICKUP

									if (secondTank.checkIfIntersect(ammoSprite))
									{
										ammoSpawned = false;
										ammoSinceDespawn = 0;
									}
									if (secondTank.checkIfIntersect(healthSprite) && healthSpawned)
									{
										secondTank.updateHealth();
										healthSpawned = false;
										healthSinceDespawn = 0;
									}
									if (secondTank.checkIfIntersect(speedSprite) && speedSpawned)
									{
										secondTank.updateSpeed();
										speedSpawned = false;
										speedSinceDespawn = 0;
									}
									//-------------------------SECOND TANK PICKUP ENDDDDDDDDDDDDDDDDDDDDDDDDDd




									for (i = 0; i < 2; ++i)
									{
										if (bullets[i].isInFlight())
										{
											mainScreen.draw(bullets[i].getShape());
										}
									}
									for (t = 0; t < player2NumberBullets; ++t)
									{
										if (secondTankBullets[t].isInFlight())
										{
											mainScreen.draw(secondTankBullets[t].getShape());
										}
									}
									//CHASER BULLETS DRAW ON MAIN SCREEN -------------------------------------------------------
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
										bool boom = exp1.animation(explosionAnimation);
										exp1.drawExplosion(mainScreen, boom, chaserX, chaserY);
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
										bool boom2 = exp2.animation(explosionAnimation2);
										exp2.drawExplosion(mainScreen, boom2, chaser2X, chaser2Y);
									}
									if (c1Dead && c2Dead && !mainTank.checkIfAlive())
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

								else if (opt == 100)
								{
									healthLevel.setPosition(1017, 65);
									SpeedTank.setPosition(1017, 100);

									Time dt = timeGone.restart();

									if (dt.asSeconds() < 1)
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
										if (opt == 3)plane2.setPosition(plane2.getPosition().x + (plane2Speed * TIMP), plane2.getPosition().y);
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
												chaser.moveChaser('r', 0.15, nr, obstacol);
												chaser.rotate();
											}
											else if (okayGo == 2)
											{
												chaser.moveChaser('l', 0.15, nr, obstacol);
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
											chaser.moveChaser('d', 0.15, nr, obstacol);
											path--;
										}
										if (path < 0)
										{
											chaser.rotate();
											rotationNeeded = chaser.rotationNeeded(tankX, tankY);
										}
										else if ((changePath - path > 0) && (changePath - path < 3))
										{
											chaser.moveChaser('l', 0.2, nr, obstacol);
											chaser.rotate();
											tankX = mainTank.getXorigin();
											tankY = mainTank.getYorigin();
											rotationNeeded = chaser.rotationNeeded(tankX, tankY);
										}
										int x = rand() % 10;
										if (x % 7 == 0 && 0)
										{
											chaser.moveChaser('r', 0.2, nr, obstacol);
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
									double chaser2Rotation = (double)chaser2.rotationOfChaser();
									if (chaser2Life > 0)
									{

										if (!chaser2.isInMotion())
										{
											double A2, D2;
											//rotationNeeded2 = chaser2.rotationNeeded(tankX, tankY);
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
											if (okayGo2 == 1)
											{
												//chaser2.moveChaser('r', 0.25);
												chaser2.moveChaser('r', 0.15, nr, obstacol);
												chaser2.rotate();
											}
											else if (okayGo2 == 2)
											{
												//chaser2.moveChaser('l', 0.25);
												chaser2.moveChaser('l', 0.15, nr, obstacol);
												chaser2.rotate();
											}

										}
										//------------------------------------------------AI MOVEMENT--------------------------CHASE     CHASE     CHASE------------------------------------------------------------------
										double chaser2Rotation = (double)chaser2.rotationOfChaser();  //??????
										if (abs(chaser2Rotation - rotationNeeded2) < 2 && !chaser2.isInMotion())
										{
											chaser2.doNotRotate();
											okayGo2 = 0;
											path2 = chaser2.pathToPlayer(tankX, tankY);
											changePath2 = path2;

										}
										if (chaser2.isInMotion() && path2 != 0)
										{
											chaser2.moveChaser('d', 0.15, nr, obstacol);
											path2--;
										}
										if (path2 < 0)
										{
											chaser2.rotate();
											tankX = mainTank.getXorigin();
											tankY = mainTank.getYorigin();
											rotationNeeded2 = chaser2.rotationNeeded(tankX, tankY);
										}
										else if ((changePath2 - path2 > 0) && (changePath2 - path2 < 3))
										{
											chaser2.moveChaser('l', 0.2, nr, obstacol);
											chaser2.rotate();
											tankX = mainTank.getXorigin();
											tankY = mainTank.getYorigin();
											rotationNeeded2 = chaser2.rotationNeeded(tankX, tankY);
										}

										int x = rand() % 10;//% 11;
										if (x % 7 == 0) // % 10 == 0)  //redundant change
										{
											chaser2.moveChaser('r', 0.2, nr, obstacol);
											chaser2.rotate();
											if (chaser2Bullets[chaser2CurrentBullet].isInFlight() != true)
											{
												//the next section will calculate the direction in which the bullet is fired
												float chaser2XX = chaser2.getXorigin();
												float chaser2YY = chaser2.getYorigin();
												chaser2.goodPoint(chaser2XX, chaser2YY);
												double rotation = (double)chaser2.rotationOfChaser();
												chaser2Bullets[chaser2CurrentBullet].thirdPoint(chaser2XX, chaser2YY, chaser2Rotation, xOrigin, yOrigin, X, Y);
												chaser2Bullets[chaser2CurrentBullet].shoot(chaser2XX, chaser2YY, xOrigin, yOrigin, chaser2Rotation);
												chaser2CurrentBullet++;
												if (chaser2CurrentBullet > 1)
												{
													chaser2CurrentBullet = 0;
												}
											}
										}
									}

									//-----------------------------chaser 3 try --------------------------------chaser 3 try--------------------------------chaser 3 try-----------
									double chaser3Rotation = (double)chaser3.rotationOfChaser();
									if (chaser3Life > 0)
									{

										if (!chaser3.isInMotion())
										{
											double A3, D3;
											//rotationNeeded3 = chaser3.rotationNeeded(tankX, tankY);
											if (chaser3Rotation > rotationNeeded3 && okayGo3 == 0)
											{
												A3 = chaser3Rotation - rotationNeeded3;
												D3 = 360 - A3;
											}
											else if (chaser3Rotation < rotationNeeded3 && okayGo3 == 0)
											{
												D3 = rotationNeeded3 - chaser3Rotation;
												A3 = 360 - D3;
											}
											if (A3 > D3 && !okayGo3)
											{
												okayGo3 = 1;
											}
											else if (A3 < D3 && !okayGo3)
											{
												okayGo3 = 2;
											}
											if (okayGo3 == 1)
											{
												//chaser3.moveChaser('r', 0.25);
												chaser3.moveChaser('r', 0.15, nr, obstacol);
												chaser3.rotate();
											}
											else if (okayGo3 == 2)
											{
												//chaser3.moveChaser('l', 0.25);
												chaser3.moveChaser('l', 0.15, nr, obstacol);
												chaser3.rotate();
											}

										}
										//------------------------------------------------AI MOVEMENT--------------------------CHASE     CHASE     CHASE------------------------------------------------------------------
										double chaser3Rotation = (double)chaser3.rotationOfChaser();  //??????
										if (abs(chaser3Rotation - rotationNeeded3) < 2 && !chaser3.isInMotion())
										{
											chaser3.doNotRotate();
											okayGo3 = 0;
											path3 = chaser3.pathToPlayer(tankX, tankY);
											changePath3 = path3;

										}
										if (chaser3.isInMotion() && path3 != 0)
										{
											chaser3.moveChaser('d', 0.15, nr, obstacol);
											path3--;
										}
										if (path3 < 0)
										{
											chaser3.rotate();
											tankX = mainTank.getXorigin();
											tankY = mainTank.getYorigin();
											rotationNeeded3 = chaser3.rotationNeeded(tankX, tankY);
										}
										else if ((changePath3 - path3 > 0) && (changePath3 - path3 < 3))
										{
											chaser3.moveChaser('l', 0.2, nr, obstacol);
											chaser3.rotate();
											tankX = mainTank.getXorigin();
											tankY = mainTank.getYorigin();
											rotationNeeded3 = chaser3.rotationNeeded(tankX, tankY);
										}

										int x = rand() % 10;//% 11;
										if (x % 7 == 0) // % 10 == 0)  //redundant change
										{
											chaser3.moveChaser('r', 0.2, nr, obstacol);
											chaser3.rotate();
											if (chaser3Bullets[chaser3CurrentBullet].isInFlight() != true)
											{
												//the next section will calculate the direction in which the bullet is fired
												float chaser3XX = chaser3.getXorigin();
												float chaser3YY = chaser3.getYorigin();
												chaser3.goodPoint(chaser3XX, chaser3YY);
												double rotation = (double)chaser3.rotationOfChaser();
												chaser3Bullets[chaser3CurrentBullet].thirdPoint(chaser3XX, chaser3YY, chaser3Rotation, xOrigin, yOrigin, X, Y);
												chaser3Bullets[chaser3CurrentBullet].shoot(chaser3XX, chaser3YY, xOrigin, yOrigin, chaser3Rotation);
												chaser3CurrentBullet++;
												if (chaser3CurrentBullet > 1)
												{
													chaser3CurrentBullet = 0;
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
											else if (chaser3.checkIfIntersect(bullets[i].getShape()) && chaser3Life > 0)
											{
												chaser3Life--;
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
									for (p = 0; p < 1 && chaser3Life > 0; p++)
									{
										if (chaser3Bullets[p].isInFlight())
										{
											chaser3Bullets[p].update(0.15);
											if (chaser3Bullets[p].intersect(obstacol, nr))
											{
												chaser3Bullets[p].stop();
											}
											if (mainTank.checkIfIntersect(chaser3Bullets[p].getShape()) && mainTank.checkIfAlive())
											{
												mainTank.lessHealth();
												chaser3Bullets[p].stop();
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
									//CHASER BULLETS DRAW ON MAIN SCREEN -------------------------------------------------------
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
									for (p = 0; p < 1; ++p)
									{
										if (chaser3Bullets[p].isInFlight())
										{
											mainScreen.draw(chaser3Bullets[p].getShape());
										}
									}

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
									if (chaser3Life > 0)
									{
										chaser3.drawAI_Chaser(mainScreen, 3);
									}
									else
									{
										c3Dead = true;
										explosionAnimation3 += 1;
										chaser3X = chaser3.getXorigin();
										chaser3Y = chaser3.getYorigin();
										bool boom3 = explosion.animation(explosionAnimation);
										explosion.drawExplosion(mainScreen, boom3, chaser3X, chaser3Y);
									}
									if (c1Dead && c2Dead && c3Dead)
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
	}
	/*else
		if (opt == 200)
		{
			sf::Event menuEvent;
			stringstream string1, string2, string3;
			string1 << endl << "how to play" << endl;
			string1 << "one player mode :" << endl;
			string1 << "the player" << endl;
			string1 << "the player can be controlled using the Keyboard. press:" << endl;
			string1 << "       ~ a or left arrow to rotate to the left," << endl;
			string1 << "       - d or right arrow to rotate to the right," << endl;
			string1 << "       - w or up arrow to move forward," << endl;
			string1 << "       - s or down arrow to move backwards," << endl;
			string1 << "       - spacebar or right ctrl to shoot." << endl;
			string1 << "the enemies" << endl;
			string1 << "         the enemies can chase you, or just randomly move on the screen" << endl;
			string1 << "powerups " << endl;
			string1 << "    there are three types of powerups" << endl;
			string1 << "               health" << endl;
			string1 << "               speed boost" << endl;
			string1 << "               number of bullets you can shoot" << endl;
			string1 << endl << endl;
			string1 << "two players mode :" << endl;
			string1 << "               the player from the left side of the screen can control the tank using wasd and spacebar" << endl;
			string1 << "               the player from the right side of the screen can control the tank using arrows and right ctrl" << endl;
			string1 << endl << endl;
			string1 << "tip : stay alive";
			howToPlay.setString(string1.str());
			howToPlay.setPosition(Vector2f(200, 200));
			while (mainScreen.pollEvent(menuEvent))
			{
				switch (menuEvent.type)
				{
				case Event::KeyPressed:
					switch (menuEvent.key.code)
					{
					case::Keyboard::Left:
						moveLeft(itemCurent, optiuneHowToPlay);
						break;
					case::Keyboard::Right:
						moveRight(itemCurent, optiuneHowToPlay);
						break;
					case::Keyboard::Return:
						switch (itemCurent)
						{
						case 0:
							opt = 1;
							break;
							//case 1:
							//	opt = 71;
							//	break;
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
			mainScreen.draw(HTPplayerImg);
			mainScreen.draw(howToPlay);
			for (int i = 0; i < 2; i++)
				mainScreen.draw(optiuneHowToPlay[i]);
			mainScreen.display();
		}*/
}


