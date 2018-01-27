// DragonBall.cpp
// Written by QUAN Yuhui (È«Óî»Ô£© on 20 June 2017. Last modified on 27 Jan 2018.
// This program aims to reconstruct a clapping game in my middle school. 
#include<iostream>
#include<cmath>
using namespace std;

int playerMove[2];
int energy[2];
int energyRelease[7] = { 3, 0, 0, -1, 1, 2, 5 }; // Energy consumed in a move.
int winnerMatrix[7][7];// A matrix to list results given moves of two players.
int energyAbsorptionMatrix[7][7]; // A matrix to list energy absorption cases.
int const shiftMoveToSubscript = 3; // Difference betweeen the playerMove and the corresponding subscript in the matrix
int roundNum = 0;
const int roundNumMax = 50;
bool gameContinuation = 1; 
bool finishThisRound = 0;
int inputPlayerMove;
bool validInput = 0;
void energyInitialization()
{
	for (int n = 0; n < 2; n++)
		energy[n] = 0;
}

void winnerMatrixInitialization()
{
	for (int i = -3; i <= 3; i++)
	{
		for (int j = -3; j <= 3; j++)
			winnerMatrix[i + shiftMoveToSubscript][j + shiftMoveToSubscript] = 9; //Default value 9 means no winner.
	}
	for (int i = 1; i <= 3; i++) // For attack moves 
	{
		for (int j=-3; j <i ; j++)
		{
			winnerMatrix[i + shiftMoveToSubscript][j + shiftMoveToSubscript] = 0; // Player 0 wins
			winnerMatrix[j + shiftMoveToSubscript][i + shiftMoveToSubscript] = 1; // 1 wins if the moves of 2 players reverse.
		}
		winnerMatrix[i + shiftMoveToSubscript][-i + shiftMoveToSubscript] = 9;
		winnerMatrix[-i + shiftMoveToSubscript][i + shiftMoveToSubscript] = 9; // No winnder if corresponding defense is made.
	}
}

void energyAbsorptionMatrixInitialization()
{
	for (int i = -3; i <= 3; i++)
	{
		for (int j = -3; j <= 3; j++)
			energyAbsorptionMatrix[i + shiftMoveToSubscript] [j+shiftMoveToSubscript]= 0; 
	}
	for (int i = 1; i <= 3; i++)
	{
		energyAbsorptionMatrix[i + shiftMoveToSubscript][i + shiftMoveToSubscript] = energyRelease[i + shiftMoveToSubscript]; // Mutual absorption.
		energyAbsorptionMatrix[-i + shiftMoveToSubscript][i + shiftMoveToSubscript] = energyRelease[i + shiftMoveToSubscript]; // Absorption in correct defense.
	}
}
void playerMovePrompt() //Function to guide player to input a playerMove.
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

void inputPlayerMoveAndValidation()
{
	if (cin >> inputPlayerMove)
	{
		if ((abs(inputPlayerMove) <= 3) || inputPlayerMove == 9)
			validInput = 1;
		else validInput = 0;
	}
	else
		validInput = 0;
	if (validInput == 0)
		cout << "INPUT_ERROR. Please follow the instruction" << endl;
}

void releaseEnergy()
{
	for (int n = 0; n <= 1; n++)
		energy[n] = energy[n] - energyRelease[playerMove[n] + shiftMoveToSubscript];
}

bool energyAbuse(int playerNum) // Determine whether a player abuses energy.
{
	if (energy[playerNum] < 0)
	{
		finishThisRound = 1;
		return 1;
	}
	else
	{
		return 0;
	}
}

void showEnergyAbuse()
{
	if (energyAbuse(0) == 0 && energyAbuse(1) == 1)
		cout << "Player 1 abuses energy and loses. Player 0 wins" << endl;
	if (energyAbuse(1) == 0 && energyAbuse(0) == 1)
		cout << "Player 0 abuses energy and loses. Player 1 wins" << endl;
	if (energyAbuse(0) == 1 && energyAbuse(1) == 1)
		cout << "Both player abuses energy and loses" << endl;
}

void energyAbsorption() // Determine energy absorption
{
	for (int n = 0; n <= 1; n++)
	{
		energy[n] = energy[n] + energyAbsorptionMatrix[playerMove[n] + shiftMoveToSubscript][playerMove[1 - n] + shiftMoveToSubscript];
	}
}


int findWinner()
{
	return winnerMatrix[playerMove[0] + shiftMoveToSubscript][playerMove[1] + shiftMoveToSubscript];
}


void scroll()
{
	for (int i = 0; i <= 5; i++)
		cout << endl;
}

int main()
{
	winnerMatrixInitialization();
	energyAbsorptionMatrixInitialization();
	energyInitialization();
	while(roundNum<roundNumMax && gameContinuation)
	{
		for (int n=0;n<=1 && gameContinuation;n=n+validInput) //Loop for two players.
		{
			cout << "Player: " << n << " energy: " << energy[n] << endl;	
			playerMovePrompt();
			inputPlayerMoveAndValidation();
			if (validInput)
				playerMove[n] = inputPlayerMove;
			if (inputPlayerMove == 9)
				gameContinuation = 0;
		}
		if (gameContinuation && !finishThisRound) // Both game and the current round continues
		{
			releaseEnergy();
			showEnergyAbuse();
			if (findWinner() != 9)
			{
				cout << "Player " << findWinner() << " wins" << endl;
				finishThisRound = 1;
			}
			else energyAbsorption();
		}
		if (finishThisRound)
		{
			scroll();
			energyInitialization;
			roundNum++;
			finishThisRound = 0;
		}	
	}
	
	return 0;
}