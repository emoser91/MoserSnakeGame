// SnakeGame.cpp : Defines the entry point for the console application.
// Simple snake game printed out into a console with characters and controlled 
// 0 - represents snake head
// o - represents snake tail
// F - represents fruit to collect to increase score
// # - represents a boundry wall

#include <iostream>
#include <conio.h> //console input/output
#include <Windows.h> //used for Sleep() function

//global varribles
bool gameOver;
const int width = 20; //screen width
const int height = 20; //screen height
int snakeHeadX, snakeHeadY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail; // tail length

enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

//function prototypes
void Setup();
void Draw();
void Input();
void Logic();

//Function that handles setup and random fruit coords
void Setup()
{
	gameOver = false;
	dir = STOP;
	snakeHeadX = width / 2;
	snakeHeadY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
}

//Function that handles the drawing of the game
void Draw()
{
	std::system("cls"); //clears the screen

	for (int i = 0; i < width + 2; i++)
		std::cout << "#";
	std::cout << std::endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				std::cout << "#";
			if (i == snakeHeadY && j == snakeHeadX)
				std::cout << "0";
			else if (i == fruitY && j == fruitX)
				std::cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						std::cout << "o";
						print = true;
					}
				}
				if (!print)
					std::cout << " ";
			}

			if (j == width - 1)
				std::cout << "#";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width + 2; i++)
		std::cout << '#';
	std::cout << std::endl;
	std::cout << "Score: " << score << std::endl;
}

//Function that handles input from the keyboard
void Input()
{
	if (_kbhit())//if keyboard is pressed (bool)
	{
		switch (_getch()) //get key pressed
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	//snake tail setup varribles
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X;
	int prev2Y;
	tailX[0] = snakeHeadX;
	tailY[0] = snakeHeadY;

	for (int i = 1; i < nTail; i++) //handles snake tail coords
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}

	switch (dir) //handles all change of direction
	{
	case LEFT:
		snakeHeadX--;
		break;
	case RIGHT:
		snakeHeadX++;
		break;
	case UP:
		snakeHeadY--;
		break;
	case DOWN:
		snakeHeadY++;
		break;
	default:
		break;
	}

	//game over with collision with wall
	//if (x > width || x < 0 || y > height || y < 0) 
		//gameOver = true;
	//wrap around walls if collision
	if (snakeHeadX >= width) snakeHeadX = 0; else if (snakeHeadX < 0) snakeHeadX = width - 1;
	if (snakeHeadY >= height) snakeHeadY = 0; else if (snakeHeadY < 0) snakeHeadY = height - 1;

	for (int i = 0; i < nTail; i++) //tail collision exit
	{
		if (tailX[i] == snakeHeadX && tailY[i] == snakeHeadY)
		{
			gameOver = true;
		}
	}

	if (snakeHeadX == fruitX && snakeHeadY == fruitY) //fruit eatten
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(60); //delay to slow down game play

	}
    return 0;
}

