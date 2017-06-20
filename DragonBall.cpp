//DragonBall.cpp
//Written by QUAN Yuhui (È«Óî»Ô£© on 20 June 2017. 
//This program aims to reconstruct a clapping game in my middle school. 
#include<iostream>
using namespace std;

int m[2];
int energy[2];
int roundNum = 0;
const int roundNumMax = 50;
bool continuation = 1; 

void initialization()
{
	for (int n = 0; n < 2; n++)
		energy[n] = 0;
}
void movePrompt() //Function to guide player to input a move.
{
	cout << "-3 for big defense" << endl;
	cout << "-2 for middle defense" << endl;
	cout << "-1 for small defense" << endl;
	cout << "0 for save energy" << endl;
	cout << "1 for small attack" << endl;
	cout << "2 for middle attack" << endl;
	cout << "3 for big attack" << endl;
	cout << "9 for exit game" << endl;
}

void energyChange() //Change energy and determine whether moves are valid.
{
	for (int n = 0; n < 2; n++)
	{
		switch (m[n])
		{
			case-3:
			{
				energy[n] = energy[n] - 3;
				break;
			}
			case 0:
			{
				energy[n] = energy[n] + 1;
				break;
			}
			case 1:
			{
				energy[n] = energy[n] - 1; 
				break;
			}
			case 2:
			{
				energy[n] = energy[n] - 2;
				break;
			}
			case 3:
			{
				energy[n] = energy[n] - 5;
				break;
			}
			case 9: //Exit game.
			{
				continuation = 0; 
				break;
			}
		}

		if (energy[n] < 0)
		{
			continuation = 0;
			cout << "Player " << n << " abuses energy and game over." << endl;
		}	
	}
}

void compare(int move_0, int move_1)
{
	if (move_0 <= 0 && move_1 <= 0) //None of players attacks thus both remain alive. 
		continuation = 1;
	else //At least one player attacks.
	{
		if (move_0 == move_1) //Two players make the same attack. 
		{
			energy[0] = energy[0] + move_1;
			energy[1] = energy[1] + move_0; //Mutual absorption.
		}
		else //Two players make different moves.
		{
			if (move_0 + move_1 == 0) //Unilateral absorption.
			{
				if (move_0 > 0)
					energy[1] = energy[1] + move_0;
				else energy[0] = energy[0] + move_1;
			}
			else //Different attacks or incorrect defense.
			{
				if (move_0 > move_1)
				{
					continuation = 0;
					cout << "Player 0 wins." << endl;
				}
				else
				{
					continuation = 0;
					cout << "Player 1 wins." << endl;
				}
			}
		}
	}
}

void scroll()
{
	for (int i = 0; i <= 5; i++)
		cout << endl;
}

int main()
{
	while (continuation && roundNum<roundNumMax)
	{

		movePrompt();
		for (int n = 0; n < 2; n++) //Loop for two players.
		{
			cout << "The move of player " << n << " is ";
			cin >> m[n];
		}

		energyChange();
		if(continuation) //Execute "compare" when energy change is valid.
			compare(m[0], m[1]);
		scroll();	
	}
	return 0;
}