#pragma once
#include "Piece.h"
#include <vector>

class Game
{
public:
	Game(int gridLength = 40, int maxTurns = 300, int numberOfEachPiece = 50);
	// ~Game();

	static int randDirection();
	static double randDouble(double u, double l);

	void playGame();
private:
	void generatePieces();
	void outputScore();

	int GRID_LENGTH;
	int MAX_TURNS;
	int NUM_EACH_PIECE;
	double MOVE_MAX_SIZE;
	double MOVE_INTERVAL;

	std::vector<Piece*> vecPieces;
};
