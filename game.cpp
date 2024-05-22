#include <iostream>
#include<SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<time.h>
#include<string>
#include<random>
#include<iomanip>
#include<vector>
#include<fstream>
#include<Windows.h>
#include"Menu.h"
#include<math.h>

using namespace std;
using namespace sf;


/*
**************************************************************
*      page number        *       fun                        *
**************************************************************
*       1000              *         mainmenu                 *
*        -1               *         close=Exit               *
*         0               *         Game_Play                *
*         1               *         instruction              *
*         2               *         Designers                *
*         3               *         Name player              *
**************************************************************
*      options            *          menu play               *
*         -1              *           Exit                   *
*          1              *          Restart                 *
*          2              *          Continue                *
*                         *                                  *
**************************************************************
*/

//workout  rounds
const int maxhealth = 6;
struct Spells {
	int speed;
	int moveto;
	Sprite spellSprite;
	int spelleffect = 0;
	bool collideCheck = false;

};

struct players {

	float timershield;


	float Vx = 200, Vy = -12, IndexMultiplier = 1, accY = 5.3;
	int healthCharacter = 6;

	Texture texture1;
	Sprite sprite1;

	bool isGrounded = true;

	int XOffset = 0;


	vector<Spells> spellsInst;
	int index = -1;
	int directionspell;
	int spelltype = -1;
	float addspeed = 0.0;

	bool anotherspell = true;
	Clock spelltake;


	//sound for jump
	SoundBuffer jumpp;
	Sound jump;
	// sound 

	Spells sh;
	bool checktshield = false;
	bool shield_spell = false;
	int tshield = 0;
	//freeze declration
	int tfreeze = 0;
	//shield declration
	Clock tspell;


	//Constructor
	players() {

		//Define player 1
		if (!player1.texture1.loadFromFile("Malfoy2.png")) {
			cout << "Error in loading image";
		}
		player1.sprite1.setTexture(player1.texture1);
		player1.sprite1.setTextureRect(sf::IntRect(0, 0, 32, 32));
		player1.sprite1.setScale(3, 3);
		player1.sprite1.setPosition(20, 950);

		//sound jump

		jumpp.loadFromFile("jump.wav");
		jump.setBuffer(jumpp);

		//Define player 2
		if (!player2.texture1.loadFromFile("Harry.png")) {
			cout << "Error in loading image";
		}
		player2.sprite1.setTexture(player2.texture1);
		player2.sprite1.setTextureRect(IntRect(0, 0, 32, 32));
		player2.sprite1.setScale(3, 3);
		player2.sprite1.setPosition(1800, 950);

		//sound 
		jumpp.loadFromFile("jump.wav");
		jump.setBuffer(jumpp);

	};

	void movement(Time DeltaTime, bool& isGrounded) {

		//Player1 Horizontal movement
		if (Keyboard::isKeyPressed(Keyboard::D) && player1.sprite1.getPosition().x < 1840)
		{

			XOffset = ((int)IndexMultiplier % 3) * (32);
			player1.sprite1.setTextureRect(sf::IntRect(XOffset, 64, 30, 32));
			player1.sprite1.move(player1.Vx * DeltaTime.asSeconds(), 0);
			IndexMultiplier += DeltaTime.asMilliseconds() * 0.01;
			player1.directionspell = 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A) && player1.sprite1.getPosition().x > -5)
		{
			XOffset = ((int)IndexMultiplier % 3) * (32);
			player1.sprite1.setTextureRect(sf::IntRect(XOffset, 32, 30, 32));
			player1.sprite1.move(-player1.Vx * DeltaTime.asSeconds(), 0);
			IndexMultiplier += DeltaTime.asMilliseconds() * 0.01;
			player1.directionspell = -1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player1.sprite1.setTextureRect(sf::IntRect(32, 0, 32, 32));
		}
		//Player 2 Horizontal movement
		if (Keyboard::isKeyPressed(Keyboard::Right) && player2.sprite1.getPosition().x < 1840)
		{
			XOffset = ((int)IndexMultiplier % 3) * (32);
			player2.sprite1.setTextureRect(sf::IntRect(XOffset, 32, 30, 32));
			player2.sprite1.move(player2.Vx * DeltaTime.asSeconds(), 0);
			IndexMultiplier += DeltaTime.asMilliseconds() * 0.01;
			player2.directionspell = 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left) && player2.sprite1.getPosition().x > -5)
		{
			XOffset = ((int)IndexMultiplier % 3) * (32);
			player2.sprite1.setTextureRect(sf::IntRect(XOffset, 0, 30, 32));
			player2.sprite1.move(-player2.Vx * DeltaTime.asSeconds(), 0);
			IndexMultiplier += DeltaTime.asMilliseconds() * 0.01;
			player2.directionspell = -1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player2.sprite1.setTextureRect(sf::IntRect(32, 0, 32, 32));
		}

		//Vertical movement of both players
		if (Keyboard::isKeyPressed(Keyboard::W) && player1.isGrounded) {
			player1.isGrounded = false;
			player1.sprite1.move(0, player1.Vy);
			player1.jump.play();
		}

		if (!player1.isGrounded) {
			player1.Vy += player1.accY * DeltaTime.asSeconds() * 4;
			player1.sprite1.move(0, player1.Vy);
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && player2.isGrounded) {
			player2.isGrounded = false;
			player2.sprite1.move(0, player2.Vy);
			player1.jump.play();
		}

		if (!player2.isGrounded) {
			player2.Vy += player2.accY * DeltaTime.asSeconds() * 4;
			player2.sprite1.move(0, player2.Vy);
		}
	}
	//Draw players
	void draw(sf::RenderWindow& window) {
		window.draw(player1.sprite1);
		window.draw(player2.sprite1);
	}
}player1, player2;
struct Ground {
	Texture GroundTexture;
	Sprite GroundSprite;
	Ground() {
		ground.GroundTexture.loadFromFile("ground2.png");
		ground.GroundSprite.setTexture(ground.GroundTexture);
		ground.GroundSprite.setPosition(0, 1030);
		ground.GroundSprite.setColor(Color(0, 0, 0, 0));
		ground.GroundSprite.setScale(100, 2);
	}
	void Draw(RenderWindow& window) {
		window.draw(ground.GroundSprite);
	}
	bool operator==(const Ground& other) const
	{
		return false;
	}
}ground;

Clock timer;
int t1 = 0, t2 = 0;
int r;
struct maps {
	Sprite background_sprite;
	Texture background_texture;

	Sprite ground_sprite;
	Texture ground_texture;

	Sprite gates_sprite[4];
	Texture gates_texture;

	Sprite blocks_sprite[10];
	Texture blocks_texture;

	Sprite gates3_sprite[1];
	Texture gates3_texture;


}mapp[3];

struct helpspells {
	Sprite dropspells;
	Sprite targetspells;
	int type;
	Clock clock1, clock2;

};

vector<helpspells>spellbag;
//Sprite spellbullet[6];
//Texture spellbullettex[6];

Sprite spells[4];
Texture spellstex[10];

//-------------------------------------------------------------maps functions---------------------------------------------------------//
void draw(RenderWindow& w, Sprite back, Sprite ground, Sprite gates[], int ngates, Sprite blocks[]);
void gateslogic1(RenderWindow& w, Sprite gate[]);
void gateslogic2(RenderWindow& w, Sprite gate[]);
void gateslogic3(RenderWindow& w, Sprite gate[]);
void setBlockPositions1(Sprite blocks[]);
void setBlockPositions2(Sprite blocks[]);
void setBlockPositions3(Sprite blocks[]);
void preDrawing1(RenderWindow& w);
void preDrawing2(RenderWindow& w);
void preDrawing3(RenderWindow& w);


void block_intersect2(Sprite blocks[], Sprite ground, int accuarcyBlocks, int accuarcyGround, int& blockCollision);
void block_intersect(Sprite blocks[], Sprite ground, int accuarcyBlocks, int accuarcyGround, int& blockCollision);
//-------------------------------------------------------------maps functions--------------------------------------------------------//


void lava(Sprite blocks[], Clock& clocklava, Clock& timelava, Clock& timelava2, int& lavarand);



//--------------------------------------------------------
int Design(RenderWindow& window);
int Game_Play(RenderWindow& window, int& mutenumber);
int instruction(RenderWindow& window);
void Name_player(RenderWindow& window, string& Pname1, string& Pname2);
int playmenu(RenderWindow& window, int& mutenumber);
void Round(RenderWindow& window, int& Character1, int& Character2, int& rounds, string Pname1, string Pname2);
//---------------------------------------------------------

void CheckCollision(bool&);

void spellentersect();
void checkspellplayer1();
void checkspellplayer2();
void restspeed1();
void restspeed2();

void drawHealth1(RenderWindow& window, Texture& healthTexture);
void drawHealth2(RenderWindow& window, Texture& healthTexture);
void choosespells(Sprite blocks);
void spellspeed();
void movespellbullet1();
void movespellbullet2();
void spelldefine();
void damagespell1();
void damagespell2();

void shieldspell();

void freezespell();

//void FireBall(vector<Spells>& vectorSpells, RenderWindow& window);


RenderWindow window(VideoMode(1920, 1080), "Game", Style::Fullscreen);

int main()
{
	// for define sound 

	int mutenumber = 0;
	Texture unmuted;
	if (!unmuted.loadFromFile("unmute.png"))
	{
		cout << "ERORR can't load the photo\n";
		system("pause");
	}
	Sprite unmute;
	unmute.setTexture(unmuted);
	unmute.setTextureRect(IntRect(0, 10, 130, 100));
	//unmute.setColor(Color(90, 100, 110, 120));
	//mute.setColor(Color(0,0,255));
	Texture muted;
	if (!muted.loadFromFile("mute.png"))
	{
		cout << "ERORR can't load the photo\n";
		system("pause");
	}
	Sprite mute;
	mute.setTexture(muted);
	mute.setTextureRect(IntRect(0, 10, 130, 100));
	//mute.setColor(Color(0, 0, 20, 200));
	//mute.setColor(Color(0,0,255));

	Music smain;
	if (!smain.openFromFile("sound menu.wav"))
	{
		cout << "ERORR!\n";
		system("pause");
	}
	SoundBuffer maiin;
	if (!maiin.loadFromFile("clik.wav"))
	{
		cout << "ERORR!\n";
	}Sound click;
	click.setBuffer(maiin);



	int pagenum = 1000; //Index for choosing
	Menu menu(1920, 1080);
	Texture mainmenubg;
	mainmenubg.loadFromFile("menu main.jpg");
	Sprite bg;
	bg.setTexture(mainmenubg);

	smain.play();


	while (true)
	{
		if (pagenum == 1000)
		{
			while (window.isOpen())
			{
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
					{
						window.close();
						break;
					}

					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::Up)        // go Up
						{
							menu.MoveUp();
							click.play();
						}
						if (event.key.code == Keyboard::Down)     // go Down
						{
							menu.MoveDown();
							click.play();
						}
						//for check mute or not 
						if (Keyboard::isKeyPressed(Keyboard::M))
						{
							mutenumber += 1;
							mutenumber = mutenumber % 2;

						}


						if (event.key.code == Keyboard::Return)    //Enter
						{
							if (menu.pressed() == 0)      //Play            //pressed()return selected~selected = Standing on option in array
							{
								smain.stop();
								pagenum = 0;
							}
							if (menu.pressed() == 1)           //instruction     
							{
								if (mutenumber == 1)
								{
									smain.stop();
								}

								pagenum = 1;
							}
							if (menu.pressed() == 2)           //Designers    
							{
								if (mutenumber == 1)
								{
									smain.stop();
								}

								pagenum = 2;
							}
							if (menu.pressed() == 3)           // Exit
							{
								pagenum = -1;
							}

						}

					}
				}
				window.clear();
				if (pagenum != 1000)   //if not  in main 
				{
					break;
				}

				window.draw(bg);
				menu.draw(window);
				//for draw mute and not mute 

				if (mutenumber == 0)
				{

					window.draw(unmute);


				}
				else if (mutenumber == 1)
				{
					window.draw(mute);
					click.stop();
					smain.play();

				}

				window.display();
			}
			if (pagenum == 0)      //   Play
			{
				smain.stop();
				pagenum = Game_Play(window, mutenumber);
			}
			if (pagenum == -1)        //Exit~~~colse
			{
				window.close();
				break;
			}
			if (pagenum == 2)    // Designers  
			{
				pagenum = Design(window);

			}
			if (pagenum == 1)    // instruction  
			{
				pagenum = instruction(window);
			}
		}
	}
}


int Design(RenderWindow& window)
{
	Texture background;
	background.loadFromFile("Designers.png");  //background
	Sprite bg;
	bg.setTexture(background);
	bg.setColor(Color(255, 255, 255, 128));
	Font font;
	font.loadFromFile("IZONERY Trial.otf");   //font
	Text t[8];
	for (int i = 0; i < 8; i++)
	{
		t[i].setFont(font);                           //language
		t[i].setCharacterSize(70);             //font size 
		t[i].setFillColor(Color::White);                     //color
		t[i].setPosition(100, (50 + i * (130)));      //( X , Y)
	}
	t[0].setString("\t\t\t\t Developed By");
	t[1].setString("\tYousab Ashraf Makram");
	t[2].setString("\t  Reham Maher Roshdy");
	t[3].setString("\tYoussef Khaled Hussein");
	t[4].setString("Asmaa Walid Sayed Moawad");
	t[5].setString("Taha Mustafa Abdel Fattah");
	t[6].setString("\tRana Mohamad Fattouh ");
	t[7].setString("  Mohamed Sameh El-Sayed");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed())
			{
				window.close();
			}
			if (event.key.code == Keyboard::Escape)
			{
				return 1000;   //Return to menu
			}


		}
		window.clear();
		window.draw(bg);   //background

		for (int i = 0; i < 8; i++)
		{
			window.draw(t[i]);
		}

		window.display();
	}
}


int instruction(RenderWindow& window)
{
	Texture background;
	background.loadFromFile("instructions.png");  //background
	Sprite bg;
	Sprite KEY[9];
	Texture key[9];

	key[0].loadFromFile("W.png");
	key[1].loadFromFile("A.png");
	key[2].loadFromFile("D.png");
	key[3].loadFromFile("ctrl.png");
	key[4].loadFromFile("UP.png");
	key[5].loadFromFile("L.png");
	key[6].loadFromFile("R.png");
	key[7].loadFromFile("space.png");
	key[8].loadFromFile("sad.png");

	for (int i = 0; i < 4; i++)
	{
		KEY[i].setPosition(540, 240 + i * 100);

	}
	for (int i = 0; i < 3; i++)
	{
		KEY[i + 4].setPosition(1750, 250 + i * 100);

	}
	KEY[7].setPosition(1650, 420);
	KEY[8].setPosition(1750, 850);

	for (int i = 0; i < 9; i++)
	{
		KEY[i].setTexture(key[i]);
	}
	bg.setTexture(background);
	Font font;
	font.loadFromFile("IZONERY Trial.otf");   //font
	Text t[12];
	for (int i = 3; i < 12; i++)
	{
		t[i].setFont(font);
		t[i].setCharacterSize(70);
		t[i].setFillColor(Color::White);
	}
	t[11].setCharacterSize(50);
	for (int i = 0; i < 3; i++)
	{
		t[i].setFont(font);
		t[i].setCharacterSize(70);
		t[i].setFillColor(Color::White);
	}
	for (int i = 1; i < 5; i++)
	{
		t[i + 2].setPosition(40, 150 + i * 100);
	}
	for (int i = 1; i < 5; i++)
	{
		t[i + 6].setPosition(1250, 150 + i * 100);
	}
	t[11].setPosition(1150, 850);

	t[0].setString("Instruction");
	t[1].setString("The First Player");
	t[2].setString("The Second Player");

	t[3].setString("MOVE UP");
	t[4].setString("MOVE LEFT");
	t[5].setString("MOVE RIGTH");
	t[6].setString("USE THE SPELL");

	t[7].setString("MOVE UP");
	t[8].setString("Move LEFT");
	t[9].setString("MOVE RIGTH");
	t[10].setString("USE THE SPELL");

	t[11].setString("When you get this you can get\nBlood supply or Electricity or\n......... ");

	t[0].setPosition(770, 10);
	t[1].setPosition(60, 70);
	t[2].setPosition(1300, 70);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed())
			{
				window.close();
			}
			if (event.key.code == Keyboard::Escape)
			{

				return 1000;   //Return to menu
			}

		}
		window.clear();
		window.draw(bg);
		for (int i = 0; i < 9; i++)
		{
			window.draw(KEY[i]);
		}
		for (int i = 0; i < 12; i++)
		{
			window.draw(t[i]);
		}
		window.display();
	}
}


void Name_player(RenderWindow& window, string& Pname1, string& Pname2)
{

	bool enter = true;

	Texture background1, background2;
	background1.loadFromFile("VS.png");
	background2.loadFromFile("VS2.png");
	Sprite bg1, bg2;
	bg1.setTexture(background1);
	bg2.setTexture(background2);
	bg2.setPosition(420, -100);
	bg2.setScale(2, 2);
	Font font;
	font.loadFromFile("IZONERY Trial.otf");
	Text t[4];
	for (int i = 0; i < 4; i++)
	{
		t[i].setFont(font);
		t[i].setCharacterSize(70);
		t[i].setFillColor(Color::White);

	}
	t[0].setPosition(50, 400);
	t[1].setPosition(1350, 400);

	t[0].setString("Name Frist Player");
	t[1].setString("Name Second Player");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				break;
			}
			if (event.type == Event::TextEntered)
			{

				if (enter)
				{
					if (Pname1.size() < 10)
					{
						Pname1 += static_cast<char>(event.text.unicode);
					}
				}
				else
				{
					if (Pname2.size() < 10)
					{
						Pname2 += static_cast<char>(event.text.unicode);
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::BackSpace))
			{
				if (enter && Pname1.size() > 0)
				{
					Pname1.resize(Pname1.size() - 1);
				}
				else if (Pname2.size() > 0)
				{
					Pname2.resize(Pname2.size() - 1);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Enter) && Pname1.size() > 1)
			{
				enter = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter) && Pname2.size() > 1)
			{
				return;
			}
		}
		t[2].setPosition(230 - (Pname1.size() * 10), 500);
		t[3].setPosition(1600 - (Pname2.size() * 10), 500);

		t[2].setString(Pname1);
		t[3].setString(Pname2);
		window.clear();
		window.draw(bg1);
		window.draw(bg2);
		for (int i = 0; i < 4; i++)
		{
			window.draw(t[i]);
		}
		window.display();

	}

}

int playmenu(RenderWindow& window, int& mutenumber)
{
	// for go up and down 
	SoundBuffer maiin;
	if (!maiin.loadFromFile("clik.wav"))
	{
		cout << "ERORR!\n";
	}Sound click;
	click.setBuffer(maiin);
	///////////////////////////////



	Texture background;
	background.loadFromFile("menu play.jpg");
	Sprite bg;
	bg.setTexture(background);
	bg.setColor(Color(255, 255, 255, 128));

	Font font;
	font.loadFromFile("IZONERY Trial.otf");

	Text options[4];

	int selectedOption = 0;

	options[0].setString("  Continue");
	options[1].setString("   Restart");
	options[2].setString("Instruction");
	options[3].setString("\t  Exit");

	for (int i = 0; i < 4; ++i)
	{
		options[i].setFont(font);
		options[i].setCharacterSize(120);
		options[i].setFillColor(Color::White);
		options[i].setPosition(750, 450 + (i * 140));
	}
	options[2].setCharacterSize(110);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up)
				{
					selectedOption = (selectedOption + 3) % 4;
					click.play();
				}
				if (event.key.code == Keyboard::Down)
				{
					selectedOption = (selectedOption + 1) % 4;
					click.play();
				}
				if (mutenumber == 1)
				{
					click.stop();
				}

				if (event.key.code == Keyboard::Enter)
				{
					if (selectedOption == 0)
					{
						return 2;
					}
					if (selectedOption == 1)
					{
						return 1;
					}
					if (selectedOption == 2)
					{
						instruction(window);
					}
					if (selectedOption == 3)
					{
						return -1;
					}
				}

			}
		}
		window.clear();
		window.draw(bg);
		for (int i = 0; i < 4; i++)
		{
			if (i == selectedOption)
			{
				options[i].setFillColor(Color::Green);
			}
			else
			{
				options[i].setFillColor(Color::White);
			}
			window.draw(options[i]);
		}
		window.display();
	}
}

void Round(RenderWindow& window, int& Character1, int& Character2, int& rounds, string Pname1, string Pname2)
{


	Texture background[4];
	background[0].loadFromFile("round1.jpg");
	background[1].loadFromFile("round2.jpg");
	background[2].loadFromFile("round3.jpeg");
	background[3].loadFromFile("Winnerr.jpg");
	Sprite bg[4];
	for (int i = 0; i < 4; i++)
	{
		bg[i].setTexture(background[i]);
	}

	Font font;
	font.loadFromFile("IZONERY Trial.otf");   //font

	//name player



	Clock clock;

	Text t[6];
	for (int i = 0; i < 6; i++)
	{
		t[i].setFont(font);
		t[i].setCharacterSize(160);
		t[i].setFillColor(Color::White);
	}
	t[0].setPosition(400, 450);
	t[1].setPosition(380, 450);
	t[2].setPosition(300, 350);
	t[3].setPosition(320, 350);
	t[4].setPosition(380 + (Pname1.size()) * 14, 500);
	t[5].setPosition(380 + (Pname1.size()) * 14, 500);

	t[0].setString(" THE FIRST ROUND");
	t[1].setString("THE SECOND ROUND");
	t[2].setString("THE THIRD AND FINAL\n\t\t\t  ROUND");
	t[3].setString("THE WINNER IS");
	t[4].setString(Pname1);
	t[5].setString(Pname2);
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed())
			{
				window.close();
			}

			if ((event.key.code == Keyboard::Enter && clock.getElapsedTime().asSeconds() >= 0.001f))
			{
				clock.restart();
				return;
			}
		}
		if (clock.getElapsedTime().asSeconds() >= 2.0f)
		{
			clock.restart();
			return;
		}
		window.clear();


		if (rounds == 1)
		{
			window.draw(bg[0]);
			window.draw(t[0]);
		}
		if (rounds == 2)
		{
			window.draw(bg[1]);
			window.draw(t[1]);
		}
		if (rounds == 3)
		{
			window.draw(bg[2]);
			window.draw(t[2]);
		}
		if (rounds == 4)
		{
			if (Character1 == 2)
			{
				window.draw(bg[3]);
				window.draw(t[3]);
				window.draw(t[4]);
			}
			if (Character2 == 2)
			{
				window.draw(bg[3]);
				window.draw(t[3]);
				window.draw(t[5]);
			}
		}
		window.display();
	}
}


int Game_Play(RenderWindow& window, int& mutenumber)
{
	//name player
	string Pname1;
	string Pname2;
	Name_player(window, Pname1, Pname2);
	Font font;
	font.loadFromFile("IZONERY Trial.otf");
	Text nameplayer1, nameplayer2;
	nameplayer1.setFont(font);
	nameplayer1.setCharacterSize(60);
	nameplayer1.setFillColor(Color::White);
	nameplayer1.setPosition(150 - (Pname1.size()) * 14, 25);
	nameplayer1.setString(Pname1);
	nameplayer2.setFont(font);
	nameplayer2.setCharacterSize(60);
	nameplayer2.setFillColor(Color::White);
	nameplayer2.setPosition(1770 - (Pname1.size()) * 14, 25);
	nameplayer2.setString(Pname2);



	//shield declration
	Spells shield;




	//clock spells handling




	//Gravity check
	bool isGrounded = false;
	int blockCollision = 0;
	//Time since last frame
	Clock deltaClock;
	Time deltaTime;

	//sound for maps 

	Music map1;
	if (!map1.openFromFile("egy map sound .wav"))
	{
		cout << "ERORR!\n";
		system("pause");        ///////////////////////////////// for Rnh map
	}
	SoundBuffer maps1;

	Music map2;
	if (!map2.openFromFile("snow map spell.wav"))
	{
		cout << "ERORR!\n";     ////////////////////////////////for Reham map
		system("pause");
	}
	SoundBuffer maps2;

	Music map3;
	if (!map3.openFromFile("lib sound map.wav"))
	{
		cout << "ERORR!\n";
		system("pause");      //////////////////////////////// for Asmaa map
	}
	SoundBuffer maps3;


	//for spells 


	Music spell;
	if (!spell.openFromFile("freeze.wav"))
	{
		cout << "can't found spell\n";
		system("pause");
	}
	SoundBuffer spell1;

	Music spelll;
	if (!spelll.openFromFile("damage spell.wav"))
	{
		cout << "can't found spell\n";
		system("pause");
	}
	SoundBuffer spell2;

	//health
	Texture healthTexture;
	healthTexture.loadFromFile("health.png");
	int Character1 = 0;
	int Character2 = 0;

	/////lava//////
	Clock clocklava, timelava1, timelava2;
	int lavarand = 0;


	Clock timeradd;

	//rounds
	int rounds = 0;
	Event event;
	window.setFramerateLimit(60);
	float angle1, angle2;
	angle1 = atan2f(player1.sprite1.getPosition().y, player1.sprite1.getPosition().x);
	window.setFramerateLimit(60);
	spelldefine();
	while (true)
	{
		int menuplay = 100;
		if (menuplay == 100)
		{
			while (window.isOpen())
			{
				deltaTime = deltaClock.restart();
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed())
					{
						window.close();
					}
					if (event.key.code == Keyboard::Escape)
					{
						menuplay = playmenu(window, mutenumber);
						timeradd.restart();
						deltaClock.restart();
						clocklava.restart();
						t1 = 0; t2 = 0; timer.restart();
					}
				}
				/////////////

				///////////
				if (rounds == 0 || player1.healthCharacter <= 0 || player2.healthCharacter <= 0)
				{
					if (player1.healthCharacter <= 0)
					{
						Character2++;
					}
					if (player2.healthCharacter <= 0)
					{
						Character1++;
					}
					player1.healthCharacter = 6; player2.healthCharacter = 6;
					rounds++;
					if (rounds == 1)
					{
						if (mutenumber != 1)
						{
							map1.play();
						}
						else
						{
							map1.stop();
						}
						preDrawing1(window);
					}
					else if (rounds == 2)
					{
						map1.stop();
						if (mutenumber != 1)
						{
							map2.play();
						}
						else
						{
							map2.stop();
						}
						preDrawing2(window);
					}
					else
					{
						map2.stop();
						if (mutenumber != 1)
						{
							map3.play();
						}
						else
						{
							map3.stop();
						}
						preDrawing3(window);
					}
					if (rounds <= 3)
					{
						if (rounds < 3)
						{
							map3.stop();
						}
						if (Character2 == 2 || Character1 == 2)
						{
							rounds++;
							Round(window, Character1, Character2, rounds, Pname1, Pname2);
							return 1000;
						}
						else
						{
							player1.sprite1.setPosition(20, 900);
							player1.sprite1.setTextureRect(IntRect(32, 0, 32, 32));
							player2.sprite1.setPosition(1800, 900);
							player2.sprite1.setTextureRect(IntRect(32, 0, 32, 32));
							player1.Vx = 200; player2.Vx = 200;
							player1.anotherspell = true; player2.anotherspell = true;
							player1.checktshield = false; player2.checktshield = false;//shield spell
							player1.shield_spell = false; player2.shield_spell = false;//shield spell
							player1.index = -1; player2.index = -1;
							lavarand = 0;
							for (int i = 0; i < player1.spellsInst.size(); i++)
							{
								player1.spellsInst.erase(player1.spellsInst.begin() + i);
							}
							for (int i = 0; i < player2.spellsInst.size(); i++)
							{
								player2.spellsInst.erase(player2.spellsInst.begin() + i);
							}
							while (true)
							{
								if (!spellbag.empty())
									spellbag.erase(spellbag.begin());
								else
									break;
							}
							timeradd.restart();
							deltaClock.restart();
							t1 = 0; t2 = 0; timer.restart();
							clocklava.restart();
							Round(window, Character1, Character2, rounds, Pname1, Pname2);
						}

					}
					else {
						Round(window, Character1, Character2, rounds, Pname1, Pname2);
						return 1000;
					}
				}
				window.clear();
				if (menuplay == -1)
				{
					return 1000;
				}
				if (menuplay == 1)
				{
					Character1 = 0;
					Character2 = 0;
					rounds = 0;
					break;
				}
				if (rounds == 1)
				{
					gateslogic1(window, mapp[0].gates_sprite);
					block_intersect(mapp[0].blocks_sprite, mapp[0].ground_sprite, 90, 97, blockCollision);
					block_intersect2(mapp[0].blocks_sprite, mapp[0].ground_sprite, 90, 97, blockCollision);
					draw(window, mapp[0].background_sprite, mapp[0].ground_sprite, mapp[0].gates_sprite, 4, mapp[0].blocks_sprite);
				}
				if (rounds == 2)
				{
					gateslogic2(window, mapp[1].gates_sprite);
					block_intersect(mapp[1].blocks_sprite, mapp[1].ground_sprite, 70, 97, blockCollision);
					block_intersect2(mapp[1].blocks_sprite, mapp[1].ground_sprite, 70, 97, blockCollision);
					draw(window, mapp[1].background_sprite, mapp[1].ground_sprite, mapp[1].gates_sprite, 4, mapp[1].blocks_sprite);
				}
				if (rounds == 3)
				{
					block_intersect(mapp[2].blocks_sprite, mapp[2].ground_sprite, 90, 95, blockCollision);
					block_intersect2(mapp[2].blocks_sprite, mapp[2].ground_sprite, 90, 95, blockCollision);
					gateslogic3(window, mapp[2].gates_sprite);
					draw(window, mapp[2].background_sprite, mapp[2].ground_sprite, mapp[2].gates3_sprite, 1, mapp[2].blocks_sprite);
				}


				if (player1.tspell.getElapsedTime().asSeconds() >= 1.0f) {
					player1.tshield++;
					player1.tfreeze++;
					player1.tspell.restart();
				}
				if (player2.tspell.getElapsedTime().asSeconds() >= 1.0f) {
					player2.tshield++;
					player2.tfreeze++;
					player2.tspell.restart();
				}

				player1.draw(window);
				player2.draw(window);
				//CheckCollision(isGrounded);
				player1.movement(deltaTime, isGrounded);
				player2.movement(deltaTime, isGrounded);
				window.draw(nameplayer1);
				window.draw(nameplayer2);

				movespellbullet1();
				movespellbullet2();
				spellspeed();



				if (player1.checktshield)
				{
					player1.shield_spell = true;
					shieldspell();
					if (player1.tshield >= 20.0)
					{
						player1.tshield = 0;
						player1.checktshield = false;
						player1.shield_spell = false;
						checkspellplayer1();
					}
				}
				if (player2.checktshield)
				{
					player2.shield_spell = true;
					shieldspell();
					if (player2.tshield >= 20.0)
					{
						player2.tshield = 0;
						player2.checktshield = false;
						player2.shield_spell = false;
						checkspellplayer1();
					}
				}



				drawHealth1(window, healthTexture);
				drawHealth2(window, healthTexture);

				spellentersect();
				//FireBall(spellsInst, window);

				restspeed1();
				restspeed2();

				if (Keyboard::isKeyPressed(Keyboard::LControl) && !player1.spellsInst.empty() && player1.index >= 0)
				{
					spell.play();
					player1.spellsInst.back().spellSprite.setPosition(player1.sprite1.getPosition());
					player1.spellsInst[player1.index].moveto = player1.directionspell;
					player1.index--;
					player1.anotherspell = true;
					player1.spellsInst.back().collideCheck = true;
					player1.spelltake.restart();
					spell.play();
				}
				if (Keyboard::isKeyPressed(Keyboard::Space) && !player2.spellsInst.empty() && player2.index >= 0)
				{
					spelll.play();
					player2.spellsInst.back().spellSprite.setPosition(player2.sprite1.getPosition());
					player2.spellsInst.back().moveto = player2.directionspell;
					player2.index--;
					player2.spellsInst.back().collideCheck = true;
					player2.anotherspell = true;
					player2.spelltake.restart();
					spelll.play
					();
				}
				damagespell2();
				damagespell1();

				for (int i = 0; i < player1.spellsInst.size(); i++)
				{
					window.draw(player1.spellsInst[i].spellSprite);
				}

				for (int i = 0; i < player2.spellsInst.size(); i++)
				{
					window.draw(player2.spellsInst[i].spellSprite);
				}
				for (int i = 0; i < spellbag.size(); i++)
				{
					window.draw(spellbag[i].dropspells);
				}


				checkspellplayer1();
				checkspellplayer2();


				lava(mapp[rounds - 1].blocks_sprite, clocklava, timelava1, timelava2, lavarand);
				if (lavarand == 0)
				{
					lavarand = rand() % 10;
				}
				ground.Draw(window);

				window.display();

			}

		}
	}

}


//setting the possetion of the blocks for  map1.
void setBlockPositions1(Sprite blocks[]) {
	for (int i = 0; i < 10; i++)
	{
		blocks[i].setScale(0.30, 0.50);
	}
	blocks[0].setPosition(320, 300);
	blocks[1].setPosition(620, 520);
	blocks[2].setPosition(250, 800);
	blocks[3].setPosition(1340, 800);
	blocks[4].setPosition(1000, 300);
	blocks[5].setPosition(950, 700);
	blocks[6].setPosition(1600, 300);
	blocks[7].setPosition(1600, 600);
	blocks[8].setPosition(10, 600);
	blocks[9].setPosition(650, 1080);
}
//setting the possetion of the blocks for  map2.
void setBlockPositions2(Sprite blocks_sprite[])
{

	blocks_sprite[2].setPosition(1016, 300);
	blocks_sprite[0].setPosition(300, 800);
	blocks_sprite[3].setPosition(1400, 800);

	blocks_sprite[6].setPosition(0, 630);
	blocks_sprite[1].setPosition(676, 630);
	blocks_sprite[4].setPosition(1660, 630);

	blocks_sprite[5].setPosition(430, 400);
	blocks_sprite[8].setPosition(1400, 400);


	blocks_sprite[7].setPosition(0, 200);
	blocks_sprite[9].setPosition(1660, 200);


}
//setting the possetion of the blocks for  map3.
void setBlockPositions3(Sprite blocks[]) {

	blocks[0].setPosition(830, 630);
	blocks[1].setPosition(0, 630);
	blocks[2].setPosition(1660, 630);
	blocks[3].setPosition(1300, 800);
	blocks[4].setPosition(300, 800);
	blocks[5].setPosition(1300, 400);
	blocks[6].setPosition(0, 200);
	blocks[7].setPosition(830, 200);
	blocks[8].setPosition(430, 400);
	blocks[9].setPosition(1660, 200);
	//blocks[10].setPosition(0, 1040);

}


//predrawing1 function that is a function set the texture to background, ground, gates and blocks for map1. "RAAAAAAAAAAna"
void preDrawing1(RenderWindow& w) {
	// background map1
	mapp[0].background_texture.loadFromFile(("Background finalllll.jpg"));
	mapp[0].background_sprite.setTexture(mapp[0].background_texture);

	// ground map1
	mapp[0].ground_texture.loadFromFile("groundffpng.png");
	mapp[0].ground_sprite.setTexture(mapp[0].ground_texture);
	mapp[0].ground_sprite.setPosition(-100, 1030);

	mapp[0].ground_sprite.setScale(3, .2);

	// gates
	mapp[0].gates_texture.loadFromFile("gatessprite.png");
	for (int i = 0; i < 4; ++i) {
		mapp[0].gates_sprite[i].setTexture(mapp[0].gates_texture);
		mapp[0].gates_sprite[i].setTextureRect(IntRect(0, 0, 144, 144));
		//mapp[0].gates_sprite[i].setPosition((i) * 565,-40);
		mapp[0].gates_sprite[i].setPosition(320 + (i * 340), -30);
		mapp[0].gates_sprite[i].setScale(1.5, 1.5);
	}

	// blocks
	mapp[0].blocks_texture.loadFromFile("blockk.png");
	for (int i = 0; i < 10; ++i) {
		mapp[0].blocks_sprite[i].setTexture(mapp[0].blocks_texture);
	}
	setBlockPositions1(mapp[0].blocks_sprite);


}
//predrawing2 function that is a function set the texture to background, ground, gates and blocks for map2  "Reham".
void preDrawing2(RenderWindow& w) {
	// background
	mapp[1].background_texture.loadFromFile("baaaa2.png");
	mapp[1].background_sprite.setTexture(mapp[1].background_texture);

	// ground
	mapp[1].ground_texture.loadFromFile("groundd.png");
	mapp[1].ground_sprite.setTexture(mapp[1].ground_texture);
	mapp[1].ground_sprite.setPosition(1, 1020);
	mapp[1].ground_sprite.setScale(3, 1);

	// gates
	mapp[1].gates_texture.loadFromFile("gatess2.png");
	for (int i = 0; i < 4; ++i) {
		mapp[1].gates_sprite[i].setTexture(mapp[1].gates_texture);
		mapp[1].gates_sprite[i].setTextureRect(IntRect(0, 0, 146, 96));
		mapp[1].gates_sprite[i].setPosition(300 + (i * 340), 0);
		mapp[1].gates_sprite[i].setScale(1.5, 1.5);
	}

	// blocks
	mapp[1].blocks_texture.loadFromFile("block2.png");
	for (int i = 0; i < 14; ++i) {
		mapp[1].blocks_sprite[i].setTexture(mapp[1].blocks_texture);

	}
	setBlockPositions2(mapp[1].blocks_sprite);
}
//predrawing3 function that is a function set the texture to background, ground, gates and blocks for map3.... made for ypu "Asmaa".
void preDrawing3(RenderWindow& w) {

	//ground_properties
	mapp[2].ground_texture.loadFromFile("group1.png");
	mapp[2].ground_sprite.setTexture(mapp[2].ground_texture);
	mapp[2].ground_sprite.setPosition(0, 1040);

	//back
	mapp[2].background_texture.loadFromFile("back (1).jpg");
	mapp[2].background_sprite.setTexture(mapp[2].background_texture);


	//gate
	mapp[2].gates3_texture.loadFromFile("group 3.png");

	for (int i = 0; i < 1; i++) {
		mapp[2].gates3_sprite[i].setTexture(mapp[2].gates3_texture);
		mapp[2].gates3_sprite[i].setPosition(0, 0);
	}


	//blocks

	mapp[2].blocks_texture.loadFromFile("Layergate2.png");
	for (int i = 0; i < 10; i++) {

		mapp[2].blocks_sprite[i].setTexture(mapp[2].blocks_texture);
		mapp[2].blocks_sprite[i].setScale(0.7, 0.7);

	}

	setBlockPositions3(mapp[2].blocks_sprite);

}


//the logic of opening and closeing the gates of map1 for"RANA"
void gateslogic1(RenderWindow& w, Sprite gate[]) {


	r = rand() % 4;
	if ((int)timer.getElapsedTime().asSeconds() >= 1) {
		t1++;
		t2++;
		cout << "T1 : " << t1 << endl;
		timer.restart();
	}
	if (t1 >= 8) {
		for (int i = 0; i < 4; i++) {
			gate[r].setTextureRect(IntRect(0 * 144, i * 144, 144, 144));
		}
		if (r == 0) {
			choosespells(mapp[0].blocks_sprite[0]);
			cout << "Block 1" << endl;
		}
		if (r == 1) {
			choosespells(mapp[0].blocks_sprite[1]);
			cout << "Block 2 \n";
		}
		if (r == 2)
		{
			choosespells(mapp[0].blocks_sprite[5]);
			cout << "Block 3 \n";

		}

		if (r == 3)
		{
			choosespells(mapp[0].blocks_sprite[3]);
			cout << "Block 4\n";
		}
		t1 = 0;
		t2 = 0;
	}


	if (t2 >= 2) {
		gate[r].setTextureRect(IntRect(0 * 144, 0 * 144, 144, 144));

	}

}
//for the logic of gates 2 "Reham".
void gateslogic2(RenderWindow& w, Sprite gate[]) {


	int r = rand() % 4;
	if ((int)timer.getElapsedTime().asSeconds() >= 1)
	{
		t1++;
		t2++;

		cout << "the timer now : " << t1 << endl;

		timer.restart();
	}

	if (t1 >= 6) {

		for (int i = 0; i < 4; i++) {
			gate[r].setTextureRect(IntRect(0 * 144, i * 96, 144, 96));

		} // now there is a random gate open.

		if (r == 0) {
			choosespells(mapp[1].blocks_sprite[0]);
			cout << "Block 1" << endl;
		}
		if (r == 1) {
			choosespells(mapp[1].blocks_sprite[1]);
			cout << "Block 2 \n";
		}
		if (r == 2)
		{
			choosespells(mapp[1].blocks_sprite[2]);
			cout << "Block 3 \n";

		}

		if (r == 3)
		{
			choosespells(mapp[1].blocks_sprite[3]);
			cout << "Block 4\n";
		}
		t1 = 0;
		t2 = 0;
	}

	if (t2 >= 4) {
		// Close the gate after 4 seconds
		gate[r].setTextureRect(IntRect(0, 0, 144, 96)); // Assuming the closed gate texture is at index 0
		// Reset t2 to restart the cycle
	}
}
//the logic of opening and closeing the gates of map3...made for you "Asmaa".
void gateslogic3(RenderWindow& w, Sprite gate[]) {

	int r = rand() % 4;


	if (timer.getElapsedTime().asSeconds() >= 1) {
		t1++;
		t2++;
		timer.restart(); // to be sure the timer is between 0 & 1..so every second the t1 will increse 1.
	}  // to avoid time delaying


	if (t1 >= 12) {
		gate[0].setPosition(0, -20);
		//every 15 sec gate opens

		if (r == 0) {
			choosespells(mapp[2].blocks_sprite[0]);
			cout << "Block 1" << endl;
		}
		if (r == 1) {
			choosespells(mapp[2].blocks_sprite[1]);
			cout << "Block 2 \n";
		}
		if (r == 2)
		{
			choosespells(mapp[2].blocks_sprite[2]);
			cout << "Block 3 \n";

		}

		if (r == 3)
		{
			choosespells(mapp[2].blocks_sprite[3]);
			cout << "Block 4\n";
		}






		t1 = 0;
		t2 = 0;
	}

	if (t2 >= 4.0) {
		gate[0].setPosition(0, 0);
	}
}


//drawing the whole map function
void draw(RenderWindow& w, Sprite back, Sprite ground, Sprite gates[], int ngates, Sprite blocks[]) {

	w.draw(back); //drawing background

	for (int i = 0; i < ngates; ++i) {
		w.draw(gates[i]); // Draw the gates
	}

	w.draw(ground); // drawing groud

	for (int i = 0; i < 10; ++i) {
		w.draw(blocks[i]); //drawing blocks
	}

}


void drawHealth1(RenderWindow& window, Texture& healthTexture)
{

	Sprite healthbars[maxhealth];
	for (int i = 0; i < maxhealth; i++)
	{
		healthbars[i].setTexture(healthTexture);
		healthbars[i].setPosition(10 + i * 40, 100);
		healthbars[i].setScale(0.25, 0.2);

		if (i < player1.healthCharacter)
		{
			window.draw(healthbars[i]);
		}
	}
}
void drawHealth2(RenderWindow& window, Texture& healthTexture)
{
	Sprite healthbars[maxhealth];
	for (int i = 0; i < maxhealth; i++)
	{

		healthbars[i].setTexture(healthTexture);
		healthbars[i].setPosition(1840 - i * 40, 100);
		healthbars[i].setScale(0.25, 0.2);

		if (i < player2.healthCharacter)
		{
			window.draw(healthbars[i]);
		}
	}
}


void CheckCollision(bool& isGrounded)               //Gravity function
{
	//Player 1 collision
	if (ground.GroundSprite.getGlobalBounds().intersects(player1.sprite1.getGlobalBounds())) {
		player1.isGrounded = true;
		player1.Vy = -13;
	}
	else {
		player1.isGrounded = false;
	}

	//Player 2 collision
	if (ground.GroundSprite.getGlobalBounds().intersects(player2.sprite1.getGlobalBounds())) {
		player2.isGrounded = true;
		player2.Vy = -13;
	}
	else {
		player2.isGrounded = false;
	}
}


void spelldefine()
{
	spellstex[0].loadFromFile("sad.png");
	spellstex[1].loadFromFile("sad.png");
	spellstex[2].loadFromFile("sad.png");
	spellstex[3].loadFromFile("sad.png");
	spellstex[4].loadFromFile("lightning.png");
	spellstex[5].loadFromFile("Water.png");
	spellstex[6].loadFromFile("net.png");
	spellstex[7].loadFromFile("fair.png");
	spellstex[8].loadFromFile("shield 3.png");// for shield tex
	spellstex[9].loadFromFile("freeze sprite.png");  // freeze 

	for (int i = 0; i < 4; i++)
	{
		spells[i].setTexture(spellstex[i]);
		spells[i].setScale(0.8f, 0.8f);
	}

}


void spellspeed()
{


	for (int i = 0; i < spellbag.size(); i++)
	{
		spellbag[i].dropspells.move(0, 3);
		if (spellbag[i].dropspells.getGlobalBounds().intersects(spellbag[i].targetspells.getGlobalBounds()))
		{
			spellbag[i].dropspells.move(0, -3);
		}

	}
}


void restspeed1() {
	if (player1.addspeed <= 0)
	{
		player1.addspeed = 0;
		player1.Vx = 200;
		player1.sprite1.setColor(Color::White);
		player1.accY = 5.3;

	}
	else
	{
		player1.addspeed -= 0.01;
	}
}
void restspeed2() {
	if (player2.addspeed <= 0)
	{
		player2.addspeed = 0;
		player2.Vx = 200;
		player2.sprite1.setColor(Color::White);
		player2.accY = 5.3;
	}
	else
	{
		player2.addspeed -= 0.01;
	}
}

void choosespells(Sprite block) {


	int indexspells = rand() % 7;


	helpspells spell;
	spell.dropspells = spells[1];

	spell.targetspells = block;

	spell.dropspells.setPosition(spell.targetspells.getPosition().x + spell.dropspells.getScale().x * 80, 80);

	spell.type = indexspells;

	spellbag.push_back(spell);


}

void checkspellplayer1()
{

	if (player1.spelltype == 0)
	{
		Spells lightning;
		lightning.spellSprite.setTexture(spellstex[4]);
		lightning.spellSprite.setPosition(50, 150);
		lightning.speed = 6;

		player1.spellsInst.push_back(lightning);
		player1.index++;

		player1.spelltype = -1;

	}
	else if (player1.spelltype == 1)
	{
		Spells Water;
		Water.spellSprite.setTexture(spellstex[5]);
		Water.speed = 6;
		Water.spellSprite.setPosition(50, 150);

		player1.spellsInst.push_back(Water);
		player1.index++;

		player1.spelltype = -1;
	}


	else if (player1.spelltype == 2)
	{
		Spells Net;
		Net.spellSprite.setTexture(spellstex[6]);
		Net.speed = 6;
		Net.spellSprite.setPosition(50, 150);

		player1.spellsInst.push_back(Net);
		player1.index++;
		player1.spelltype = -1;
	}

	else if (player1.spelltype == 3)
	{
		player1.addspeed = 10;
		player1.Vx = 300;
		player1.sprite1.setColor(Color::White);
		player1.accY = 5.3;
	}
	else if (player1.spelltype == 4)
	{
		Spells FireBall;
		FireBall.spellSprite.setTexture(spellstex[7]);
		FireBall.speed = 6;
		FireBall.spellSprite.setPosition(50, 150);

		player1.spellsInst.push_back(FireBall);
		player1.index++;
		player1.spelltype = -1;
	}
	else if (player1.spelltype == 5) {
		player1.tshield = 0;
		player1.timershield = 8;
		player1.checktshield = true;
		player1.spelltype = -1;
	}


	//freezespell
	else if (player1.spelltype == 6) {
		Spells freeze;
		freeze.spellSprite.setTexture(spellstex[9]);
		freeze.spellSprite.setScale(0.2, 0.2);
		freeze.speed = 6;
		freeze.spellSprite.setPosition(50, 150);
		freeze.spelleffect = 1;
		player1.spellsInst.push_back(freeze);


		player1.index++;

		player1.spelltype = -1;
	}
	player1.spelltype = -1;
}
void checkspellplayer2()
{
	if (player2.spelltype == 0)
	{
		Spells lightning;
		lightning.spellSprite.setTexture(spellstex[4]);
		lightning.speed = 6;
		lightning.spellSprite.setPosition(1800, 150);
		//cons

		player2.spellsInst.push_back(lightning);
		player2.index++;

		player2.spelltype = -1;


	}
	else if (player2.spelltype == 1)
	{
		Spells Water;
		Water.spellSprite.setTexture(spellstex[5]);
		Water.speed = 6;
		Water.spellSprite.setPosition(1800, 150);

		player2.spellsInst.push_back(Water);
		player2.index++;

		player2.spelltype = -1;
	}
	else if (player2.spelltype == 2)
	{
		Spells Net;
		Net.spellSprite.setTexture(spellstex[6]);
		Net.speed = 6;
		Net.spellSprite.setPosition(1800, 150);

		player2.spellsInst.push_back(Net);
		player2.index++;
		player2.spelltype = -1;
	}
	else if (player2.spelltype == 3)
	{
		player2.addspeed = 10;
		player2.Vx = 300;
		player2.sprite1.setColor(Color::White);
		player2.accY = 5.3;
	}
	else if (player2.spelltype == 4)
	{
		Spells FireBall;
		FireBall.spellSprite.setTexture(spellstex[7]);
		FireBall.speed = 6;
		FireBall.spellSprite.setPosition(1800, 150);

		player2.spellsInst.push_back(FireBall);
		player2.index++;
		player2.spelltype = -1;

	}

	else if (player2.spelltype == 5) {
		player2.tshield = 0;
		player2.timershield = 8;
		player2.checktshield = true;
		player2.spelltype = -1;

	}

	else if (player2.spelltype == 6) {
		Spells freeze;
		freeze.spellSprite.setTexture(spellstex[9]);
		freeze.spellSprite.setScale(0.2, 0.2);
		freeze.speed = 6;
		freeze.spellSprite.setPosition(1800, 150);
		freeze.spelleffect = 1;

		player2.spellsInst.push_back(freeze);
		// freezespell(freeze.spellSprite,2);

		player2.index++;

		player2.spelltype = -1;
	}

	player2.spelltype = -1;
}

void spellentersect()
{
	for (int i = 0; i < spellbag.size(); i++)
	{
		if (player1.sprite1.getGlobalBounds().intersects(spellbag[i].dropspells.getGlobalBounds()))
		{
			if (player1.anotherspell && player1.spelltake.getElapsedTime().asSeconds() >= 0.1f)
			{
				player1.spelltype = spellbag[i].type;
				spellbag.erase(spellbag.begin() + i);
				if (player1.spelltype != 3 && player1.spelltype != 5)
				{
					player1.anotherspell = false;
				}
			}
		}

		else if (player2.sprite1.getGlobalBounds().intersects(spellbag[i].dropspells.getGlobalBounds()))
		{
			if (player2.anotherspell && player2.spelltake.getElapsedTime().asSeconds() >= 0.1f)
			{
				player2.spelltype = spellbag[i].type;
				spellbag.erase(spellbag.begin() + i);

				if (player2.spelltype != 3 && player2.spelltype != 5)
				{
					player2.anotherspell = false;
				}
			}
		}
	}
}

void movespellbullet1() {

	for (int i = 0; i < player1.spellsInst.size(); i++)
	{

		if (player1.spellsInst[i].moveto == 1)
		{
			player1.spellsInst[i].spellSprite.move(3 * player1.spellsInst[i].speed, 0);
		}
		if (player1.spellsInst[i].moveto == -1)
		{
			player1.spellsInst[i].spellSprite.move(-3 * player1.spellsInst[i].speed, 0);
		}
		if (player1.spellsInst[i].spellSprite.getPosition().x > 2000 || player1.spellsInst[i].spellSprite.getPosition().x < -10)
		{
			player1.spellsInst.erase(player1.spellsInst.begin() + i);

		}

	}
}
void movespellbullet2() {

	for (int i = 0; i < player2.spellsInst.size(); i++)
	{

		if (player2.spellsInst[i].moveto == 1)
		{
			player2.spellsInst[i].spellSprite.move(3 * player2.spellsInst[i].speed, 0);
		}
		if (player2.spellsInst[i].moveto == -1)
		{
			player2.spellsInst[i].spellSprite.move(-3 * player2.spellsInst[i].speed, 0);
		}

		if (player2.spellsInst[i].spellSprite.getPosition().x > 2000 || player2.spellsInst[i].spellSprite.getPosition().x < -10)
		{
			player2.spellsInst.erase(player2.spellsInst.begin() + i);

		}

	}
}

void damagespell1() {
	for (int i = 0; i < player1.spellsInst.size(); i++)
	{
		if (player2.sprite1.getGlobalBounds().intersects(player1.spellsInst[i].spellSprite.getGlobalBounds()) && player1.spellsInst[i].collideCheck)
		{
			player2.healthCharacter--;

			if (player1.spellsInst[i].spelleffect == 1)
				freezespell();


			player1.spellsInst.erase(player1.spellsInst.begin() + i);

		}






	}
}
void damagespell2() {
	for (int i = 0; i < player2.spellsInst.size(); i++)
	{
		if (player1.sprite1.getGlobalBounds().intersects(player2.spellsInst[i].spellSprite.getGlobalBounds()) && player2.spellsInst[i].collideCheck)
		{
			player1.healthCharacter--;

			if (player2.spellsInst[i].spelleffect == 1) {
				freezespell();
			}


			player2.spellsInst.erase(player2.spellsInst.begin() + i);

		}


	}
}

void freezespell() {
	Color freezeffect(0, 0, 255, 128);


	for (int i = 0; i < player2.spellsInst.size(); i++)
	{
		if (player1.sprite1.getGlobalBounds().intersects(player2.spellsInst[i].spellSprite.getGlobalBounds()) && player2.spellsInst[i].collideCheck)
		{

			player1.sprite1.setColor(freezeffect);
			//player2.spellsInst.erase(player2.spellsInst.begin() + i);
			player2.spellsInst[i].spelleffect = 0;
			player1.addspeed = 10;
			player1.Vx = 20;
			player1.accY = 12;
		}
	}


	for (int i = 0; i < player1.spellsInst.size(); i++)
	{
		if (player2.sprite1.getGlobalBounds().intersects(player1.spellsInst[i].spellSprite.getGlobalBounds()) && player1.spellsInst[i].collideCheck)
		{

			player2.sprite1.setColor(freezeffect);
			player1.spellsInst[i].spelleffect = 0;
			player2.addspeed = 10;
			player2.Vx = 20;
			player2.accY = 12;
			//player1.spellsInst.erase(player1.spellsInst.begin() + i);
		}

	}


}
void shieldspell()
{
	if (player1.shield_spell)
	{
		player1.sh.spellSprite.setTexture(spellstex[8]);
		player1.sh.spellSprite.setTextureRect(IntRect(0, 0, 1200, 1200));
		player1.sh.spellSprite.setScale(0.2, 0.2);
		player1.sh.spellSprite.setPosition(player1.sprite1.getPosition().x - 70, player1.sprite1.getPosition().y - 60);
		window.draw(player1.sh.spellSprite);
		for (int i = 0; i < player2.spellsInst.size(); i++)
		{
			if (player1.sh.spellSprite.getGlobalBounds().intersects(player2.spellsInst[i].spellSprite.getGlobalBounds()))
			{
				player2.spellsInst.erase(player2.spellsInst.begin() + i);

				player1.tshield = 0;
				player1.checktshield = false;
				player1.shield_spell = false;
				checkspellplayer1();
			}
		}
	}
	if (player2.shield_spell)
	{
		player2.sh.spellSprite.setTexture(spellstex[8]);
		player2.sh.spellSprite.setTextureRect(IntRect(0, 0, 1200, 1200));
		player2.sh.spellSprite.setScale(0.2, 0.2);
		player2.sh.spellSprite.setPosition(player2.sprite1.getPosition().x - 70, player2.sprite1.getPosition().y - 60);
		window.draw(player2.sh.spellSprite);
		for (int i = 0; i < player1.spellsInst.size(); i++)
		{
			if (player2.sh.spellSprite.getGlobalBounds().intersects(player1.spellsInst[i].spellSprite.getGlobalBounds()))
			{
				player1.spellsInst.erase(player1.spellsInst.begin() + i);

				player2.tshield = 0;
				player2.checktshield = false;
				player2.shield_spell = false;
				checkspellplayer1();
			}
		}
	}
}


//struct for map1 and map2
void block_intersect(Sprite blocks[], Sprite ground, int accuarcyBlocks, int accuarcyGround, int& blockCollision) {

	float const rightWall = 1850; // --> according to our screen size
	float const leftwall = 0;     // 
	//float const ceiling = 1;     //

	FloatRect playerBounds = player1.sprite1.getGlobalBounds();
	FloatRect groundBounds = ground.getGlobalBounds();

	for (int i = 0; i < 10 && player1.isGrounded == false; i++) {

		FloatRect blockBounds = blocks[i].getGlobalBounds();

		if (playerBounds.intersects(blockBounds) && (playerBounds.top + playerBounds.height) > blockBounds.top) {
			blockCollision = i;
			player1.sprite1.setPosition(player1.sprite1.getPosition().x, blockBounds.top - accuarcyBlocks); //95  // the variable number change according to each map, and to enhance the accuracy
			player1.isGrounded = true;
			player1.Vy = -13;
		}


		else
			player1.isGrounded = false;  // player return to fall again if he is not on the block
	}

	if (playerBounds.intersects(groundBounds)) {
		player1.sprite1.setPosition(player1.sprite1.getPosition().x, groundBounds.top - accuarcyGround); //90
		player1.isGrounded = true;
		player1.Vy = -13;
	}

	else if (player1.isGrounded) {
		if (!playerBounds.intersects(blocks[blockCollision].getGlobalBounds())) // if the player 
		{
			player1.isGrounded = false;
			player1.Vy = 0;
		}

	}

	// walls and ceiling lemitations
	if (player1.sprite1.getPosition().x >= rightWall)
		player1.sprite1.setPosition(player1.sprite1.getPosition().x - 10, player1.sprite1.getPosition().y);

	else if (player1.sprite1.getPosition().x < leftwall)
		player1.sprite1.setPosition(player1.sprite1.getPosition().x + 10, player1.sprite1.getPosition().y);

	/*else if (player1.sprite1.getPosition().y < ceiling)
		player1.sprite1.setPosition(player1.sprite1.getPosition().x, player1.sprite1.getPosition().y + 10);*/


}
void block_intersect2(Sprite blocks[], Sprite ground, int accuarcyBlocks, int accuarcyGround, int& blockCollision) {

	float const rightWall = 1850;
	float const leftwall = 0;
	//float const ceiling = 10;

	FloatRect playerBounds = player2.sprite1.getGlobalBounds();
	FloatRect groundBounds = ground.getGlobalBounds();

	for (int i = 0; i < 10 && player2.isGrounded == false; i++) {


		FloatRect blockBounds = blocks[i].getGlobalBounds();

		if (playerBounds.intersects(blockBounds)) {
			blockCollision = i;
			player2.sprite1.setPosition(player2.sprite1.getPosition().x, blockBounds.top - accuarcyBlocks); //95  map3
			// 70 map1'reham' // 
			player2.isGrounded = true;
			player2.Vy = -13;
		}


		else
			player2.isGrounded = false;

	}
	if (playerBounds.intersects(groundBounds)) {
		player2.sprite1.setPosition(player2.sprite1.getPosition().x, groundBounds.top - accuarcyGround); //90 map3
		player2.isGrounded = true;
		player2.Vy = -13;
	}

	else if (player2.isGrounded) {
		if (!playerBounds.intersects(blocks[blockCollision].getGlobalBounds())) {
			player2.isGrounded = false;
			player2.Vy = 0;
		}

	}

	if (player2.sprite1.getPosition().x >= rightWall)
		player2.sprite1.setPosition(player2.sprite1.getPosition().x - 10, player2.sprite1.getPosition().y);

	else if (player2.sprite1.getPosition().x < leftwall)
		player2.sprite1.setPosition(player2.sprite1.getPosition().x + 10, player2.sprite1.getPosition().y);

	/*else if (player2.sprite1.getPosition().y < ceiling)
		player2.sprite1.setPosition(player2.sprite1.getPosition().x, player2.sprite1.getPosition().y + 10);*/


}


void lava(Sprite blocks[], Clock& clocklava, Clock& timelava1, Clock& timelava2, int& lavarand)
{
	if (clocklava.getElapsedTime().asSeconds() >= 10.0f)
	{

		blocks[lavarand].setColor(Color::Red);
		if (player2.sprite1.getGlobalBounds().intersects(blocks[lavarand].getGlobalBounds()) && timelava2.getElapsedTime().asSeconds() >= 1.0f)
		{
			player2.healthCharacter--;
			timelava2.restart();
		}
		if (player1.sprite1.getGlobalBounds().intersects(blocks[lavarand].getGlobalBounds()) && timelava1.getElapsedTime().asSeconds() >= 1.0f)
		{
			player1.healthCharacter--;
			timelava1.restart();
		}

	}
	if (clocklava.getElapsedTime().asSeconds() >= 15.0f)
	{
		blocks[lavarand].setColor(Color::White);
		lavarand = 0;
		clocklava.restart();
	}
	if (lavarand == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			blocks[i].setColor(Color::White);

		}
	}
}

