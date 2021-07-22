#pragma once
#include "Piece.h"
class Queen : public virtual Piece
{
public:
	Queen(const double xPos = 0.0, const double yPos = 0.0) : Piece(xPos, yPos)
	{
		pName = "Queen";
		shape = Circle;
		radius = 1;
	}
	// ~Queen();

	void incrementScore();
	static int score;

	void move(const double movement, Movement direction);
	double getDistanceFromCentre() const;
protected:
	int radius;
};
