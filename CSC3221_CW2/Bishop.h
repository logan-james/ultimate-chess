#pragma once
#include "Piece.h"
class Bishop : public virtual Piece
{
public:
	Bishop(const double xPos = 0.0, const double yPos = 0.0) : Piece(xPos, yPos)
	{
		shape = Circle;
		pName = "Bishop";
		radius = 1;
	}
	// ~Bishop();

	void incrementScore();
	static int score;

	void move(const double movement, Movement direction);
	double getDistanceFromCentre() const;
protected:
	int radius;
};

