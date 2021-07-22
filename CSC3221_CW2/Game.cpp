#pragma once
#include <iostream>
#include <ctime>
#include <map>
#include <algorithm>

#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Collision.h"
#include "Game.h"

using namespace std;

Game::Game(int gridLength, int maxTurns, int numberOfEachPiece)
{
	GRID_LENGTH = gridLength;
	MAX_TURNS = maxTurns;
	NUM_EACH_PIECE = numberOfEachPiece;
	MOVE_MAX_SIZE = GRID_LENGTH / 5.0;
	MOVE_INTERVAL = 0.5;
}

int Game::randDirection()
{
	return rand() % 8;
}

double Game::randDouble(double lowerBound, double upperBound)
{
	double random = static_cast<double>(rand() / static_cast<double>(RAND_MAX));
	double difference = upperBound - lowerBound;

	return lowerBound + (random * difference);
}

void Game::outputScore()
{
	cout << endl;
	cout << "===== GAME OVER ======" << endl;
	cout << " SCOREBOARD" << endl;
	cout << "======================" << endl;
	cout << "> Rook: " << Rook::score << endl;
	cout << "> Bishop: " << Bishop::score << endl;
	cout << "> Queen: " << Queen::score << endl;
}

void Game::generatePieces()
{
	for (int i = 0; i < NUM_EACH_PIECE; i++)
	{
		double startX = randDouble(1.0, GRID_LENGTH - 1.0);
		double startY = randDouble(1.0, GRID_LENGTH - 1.0);

		vecPieces.push_back(new Rook(startX, startY));

		startX = randDouble(1.0, GRID_LENGTH - 1.0);
		startY = randDouble(1.0, GRID_LENGTH - 1.0);

		vecPieces.push_back(new Queen(startX, startY));

		startX = randDouble(1.0, GRID_LENGTH - 1.0);
		startY = randDouble(1.0, GRID_LENGTH - 1.0);

		vecPieces.push_back(new Bishop(startX, startY));
	}
}

void Game::playGame()
{
	// seed time for pseudo random number generation
	srand(static_cast<unsigned>(time(NULL)));

	// create pieces and populate our vector
	generatePieces();

	int currentTurn = 1;
	int activePieces = vecPieces.size();

	while (activePieces > 1 && currentTurn <= MAX_TURNS)
	{
		cout << endl;
		cout << "Round " << currentTurn << " of " << MAX_TURNS << " | Active pieces left: " << activePieces << endl;

		for (int firstRun = 0; firstRun < activePieces; firstRun++)
		{
			double rFinalDistance = randDouble(0.1, MOVE_MAX_SIZE);
			Piece::Movement rDir = static_cast<Piece::Movement>(randDirection());

			double rStep = MOVE_INTERVAL;
			double rDistanceMoved = 0.0;

			Piece* currentPiece = vecPieces[firstRun];

			bool atLeastOneCollision = false;
			while (rDistanceMoved < rFinalDistance && !atLeastOneCollision)
			{
				// adjust distance moved
				rDistanceMoved += rStep;

				// move a little bit
				currentPiece->move(rStep, rDir);
				
				// check for collisions between each wall and reposition pieces accordingly
				if (Collision::isBoundaryTopCollision(*currentPiece, GRID_LENGTH))
				{
					currentPiece->setPosition(currentPiece->getX(), GRID_LENGTH - currentPiece->getDistanceFromCentre() - 1);
				}

				if (Collision::isBoundaryRightCollision(*currentPiece, GRID_LENGTH))
				{
					currentPiece->setPosition(GRID_LENGTH - currentPiece->getDistanceFromCentre() - 1, currentPiece->getY());
				}

				if (Collision::isBoundaryLeftCollision(*currentPiece))
				{
					currentPiece->setPosition(currentPiece->getDistanceFromCentre() + 1, currentPiece->getY());
				}

				if (Collision::isBoundaryBottomCollision(*currentPiece))
				{
					currentPiece->setPosition(currentPiece->getX(), currentPiece->getDistanceFromCentre() + 1);
				}

				// collision detection with other pieces
				for (int secondRun = 0; secondRun < activePieces;)
				{
					// don't need to bother if pieces are the same
					if (firstRun == secondRun) 
					{
						++secondRun;
						continue;
					}

					// check for collision
					if (Collision::isPieceCollision(*currentPiece, *vecPieces[secondRun]))
					{
						atLeastOneCollision = true;

						// score handling
						currentPiece->incrementScore();

						cout << "\n" << "Collision detected!" << endl;
						cout << currentPiece->getName() << " at (" << currentPiece->getX() << ", " << currentPiece->getY() << ")"
							" hit a " << vecPieces[secondRun]->getName() << " at (" << vecPieces[secondRun]->getX() << ", " << vecPieces[secondRun]->getY() << ")" << endl;

						vecPieces.erase(vecPieces.begin() + secondRun);

						// handle indexes once a piece has been removed
						if (firstRun < secondRun)
						{
							--secondRun;
						}
						else
						{
							--firstRun;
						}

						activePieces = vecPieces.size();
					}
					else
					{
						++secondRun;
					}
				}

				if (atLeastOneCollision)
				{
					break;
				}

				if (rDistanceMoved + rStep >= rFinalDistance)
				{
					// make sure we move the entirety of the move
					rStep = (rFinalDistance - rDistanceMoved);
				}
			}
		}

		currentTurn++;
	}

	// game over -- print the final score
	outputScore();

	if (activePieces == 1)
	{
		cout << endl;
		cout << "Last piece standing" << endl;
		cout << "===================" << endl;
		cout << *vecPieces[0] << endl;
	}
	
	// clean up
	for (int i = 0; i < vecPieces.size(); ++i)
	{
		delete vecPieces[i];
	}
	vecPieces.clear();
}
