#pragma once
#include "Piece.h"
class Rook : public virtual Piece
{
public:
	Rook(const double xPos = 0.0, const double yPos = 0.0) : Piece(xPos, yPos)
	{
		pName = "Rook";
		shape = Square;
		length = 2;
	}
	// ~Rook();

	void incrementScore();
	static int score;

	void move(const double movement, Movement direction);
	double getDistanceFromCentre() const;
protected:
	int length;
};

