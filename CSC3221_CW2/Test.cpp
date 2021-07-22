#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Collision.h"
#include "Game.h"

#include <cassert>
#include <vector>

const int TEST_GRID_LENGTH = 5;
const double EPSILON = 0.001;

int Piece::totalID = 0;

/*
	Test to see if a Queen moving North works as expected.
*/
void testQueenNorthMovement()
{
	Queen q(1.0, 1.0);

	q.move(2.5, Piece::N);

	assert(abs(q.getX() - 1.0) <= EPSILON);
	assert(abs(q.getY() - 3.5) <= EPSILON);
}

/*
	Test to see if a Rook moving West works as expected.
*/
void testSquareWestMovement()
{
	Rook r(1.0, 1.0);

	r.move(3.21392, Piece::W);

	assert(abs(r.getX() + 2.21392) <= EPSILON);
	assert(abs(r.getY() - 1.0) <= EPSILON);
}

/*
	Two squares touching at one side should count as a collision.
*/
void testSquareSquareTouchCollision()
{
	Rook r(2.0, 2.0);
	Rook s(4.0, 2.0);

	assert(Collision::isPieceCollision(r, s));
}

/*
	A circle just touching the corner of a square should count as a collision.
*/
void testSquareCircleTouchCollision()
{
	Rook r(2.0, 2.0);
	Bishop b(3.7, 3.7);

	assert(Collision::isPieceCollision(r, b));
}

/*
	Test for when a circle perfectly overlaps with a square.

	Unlikely to happen in a game, but this should still count as a collision.
*/
void testCircleSquareOverlapCollision()
{
	Queen q(5.0, 5.0);
	Rook r(5.0, 5.0);

	assert(Collision::isPieceCollision(q, r));
}

/*
	Test to see if piece equality is sound.

	A piece compared with itself should be equal.
*/
void testOnePieceEquality()
{
	std::vector<Piece*> vecPieces = { new Rook(1.0, 1.0) };

	assert(*vecPieces[0] == *vecPieces[0]);

	delete vecPieces[0];
	vecPieces.clear();
}

/*
	Test if two pieces of the same type and position are actually the same.

	Here, they should not be.
*/
void testTwoPieceEquality()
{
	Rook r(1.0, 1.0);
	Rook s(1.0, 1.0);

	assert(r != s);
}

/*
	Using Pythagoras: a^2 + b^2 = c^2
	Here, c^2 = 4, which makes c = 2

	With a radius of 1, these circles are just touching.
	This should count as a collision.
*/
void testCircleCircleTouchCollision()
{
	Bishop b(2.0, 7.0);
	Bishop c(3.6, 5.8);

	assert(Collision::isPieceCollision(b, c));
}

/*
	Test for if the corner of one square just touches the corner of another square.
	I count this as a collision.

	A visual of this is in 'DetermineTestCoords.PNG' where a black Rook is touching a green Rook.
*/
void testSquareSquareCornerCollison()
{
	Rook r(4.2, 1.8);
	Rook s(2.2, 3.8);

	assert(Collision::isPieceCollision(r, s));
}

/*
	Test to see if diagonal movement is sound.
*/
void testBishopSouthEastMovement()
{
	Bishop b(1.2, 4.8);

	b.move(1.4 * ROOT_TWO, Piece::SE);

	assert(abs(b.getX() - 2.6) <= EPSILON);
	assert(abs(b.getY() - 3.4) <= EPSILON);
}

/*
	Stripped down version of game loop to detect hitting multiple pieces at once with one move.

	A piece should wipe out all pieces that it is touching, and then terminate the move.

	Here, a Queen should be touching two Rooks and a Bishop. The Queen should be the last piece standing.

	A visual of this is in 'DetermineTestCoords.PNG' where the pink Queen is touching a red Rook, a green Rook,
	and an orange Bishop.
*/
void testMultiCollisionInOneMove()
{
	std::vector<Piece*> vecPieces =
	{
		new Rook(2.0, 2.0)
		, new Rook(4.2, 1.8)
		, new Bishop(4.0, 4.0)
		, new Queen(1.2, 4.8)
	};

	vecPieces[3]->move(1.4 * ROOT_TWO, Piece::SE);

	// end point should be 2.2, 3.8
	// replica of testBishopSouthEastMovement() so this movement should hold
	assert(abs(vecPieces[3]->getX() - 2.6) <= EPSILON);
	assert(abs(vecPieces[3]->getY() - 3.4) <= EPSILON);

	// need to do a collision detection between the other 3 pieces
	// they should all be wiped out by this move
	int innerLoopSurpassingOuterLoop = 0;

	int vecSize = vecPieces.size();
	int queenPos = 3;

	for (int firstRun = queenPos; firstRun < vecSize; ++firstRun)
	{
		Piece* temp = vecPieces[firstRun];
		bool atLeastOneCollision = false;
		for (int secondRun = 0; secondRun < vecSize;)
		{
			// don't need to bother if pieces are the same
			if (firstRun == secondRun)
			{
				++secondRun;
				continue;
			}

			// check for collision
			if (Collision::isPieceCollision(*temp, *vecPieces[secondRun]))
			{
				atLeastOneCollision = true;

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

				vecSize = vecPieces.size();
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
	}

	// should have one piece left of type Queen
	assert(vecPieces.size() == 1);
	assert(vecPieces[0]->getName() == "Queen");

	// clean up
	for (int i = 0; i < vecPieces.size(); ++i)
	{
		delete vecPieces[i];
	}
	vecPieces.clear();
}

/*
	Test to see if we can detect whether a piece has passed the top of the board, and whether resetting it to a sensible position works.
*/
void testTopBoundaryCollision()
{
	Bishop b(2.0, 2.0);
	b.move(10.0 * ROOT_TWO, Piece::NW);

	assert(abs(b.getX() + 8.0) <= EPSILON);
	assert(abs(b.getY() - 12.0) <= EPSILON);
	assert(Collision::isBoundaryTopCollision(b, TEST_GRID_LENGTH));

	b.setPosition(b.getX(), TEST_GRID_LENGTH - b.getDistanceFromCentre() - 1);

	assert(abs(b.getX() + 8.0) <= EPSILON);
	assert(abs(b.getY() - (TEST_GRID_LENGTH - 2.0)) <= EPSILON);
	assert(!Collision::isBoundaryTopCollision(b, TEST_GRID_LENGTH));
}

/*
	Test to see if we can detect whether a piece has passed the top of the board, and whether resetting it to a sensible position works.
*/
void testBottomBoundaryCollision()
{
	Queen q(5.0, 5.0);
	q.move(10.0, Piece::S);

	assert(abs(q.getX() - 5.0) <= EPSILON);
	assert(abs(q.getY() + 5.0) <= EPSILON);
	assert(Collision::isBoundaryBottomCollision(q));

	q.setPosition(q.getX(), q.getDistanceFromCentre() + 1);

	assert(abs(q.getX() - 5.0) <= EPSILON);
	assert(abs(q.getY() - 2.0) <= EPSILON);
	assert(!Collision::isBoundaryBottomCollision(q));
}

/*
	Test to see if we can detect whether a piece has passed the left of the board, and whether resetting it to a sensible position works.
*/
void testLeftBoundaryCollision()
{
	Rook r(5.0, 5.0);
	r.move(10.0, Piece::W);

	assert(abs(r.getX() + 5.0) <= EPSILON);
	assert(abs(r.getY() - 5.0) <= EPSILON);
	assert(Collision::isBoundaryLeftCollision(r));

	r.setPosition(r.getDistanceFromCentre() + 1, r.getY());

	assert(abs(r.getX() - 2.0) <= EPSILON);
	assert(abs(r.getY() - 5.0) <= EPSILON);
	assert(!Collision::isBoundaryLeftCollision(r));
}

/*
	Test to see if we can detect whether a piece has passed the right of the board, and whether resetting it to a sensible position works.
*/
void testRightBoundaryCollision()
{
	Rook r(5.0, 5.0);
	r.move(10.0, Piece::E);

	assert(abs(r.getX() - 15.0) <= EPSILON);
	assert(abs(r.getY() - 5.0) <= EPSILON);
	assert(Collision::isBoundaryRightCollision(r, TEST_GRID_LENGTH));

	r.setPosition(TEST_GRID_LENGTH - r.getDistanceFromCentre() - 1, r.getY());

	assert(abs(r.getX() - (TEST_GRID_LENGTH - 2.0)) <= EPSILON);
	assert(abs(r.getY() - 5.0) <= EPSILON);
	assert(!Collision::isBoundaryRightCollision(r, TEST_GRID_LENGTH));
}

/*
	This will run a few unit tests before running the game.

	If a unit test fails, the program will blow up.
*/
int main()
{
	// movement
	testQueenNorthMovement();
	testSquareWestMovement();
	testBishopSouthEastMovement();

	// piece collision
	testSquareSquareTouchCollision();
	testSquareSquareCornerCollison();
	testSquareCircleTouchCollision();
	testCircleSquareOverlapCollision();
	testCircleCircleTouchCollision();
	testMultiCollisionInOneMove();

	// piece equality
	testOnePieceEquality();
	testTwoPieceEquality();

	// boundary collision
	testTopBoundaryCollision();
	testBottomBoundaryCollision();
	testLeftBoundaryCollision();
	testRightBoundaryCollision();

	// play a game!

	// grid length, max turns, number of each piece
	Game g(60, 400, 80);
	g.playGame();

	return 0;
}