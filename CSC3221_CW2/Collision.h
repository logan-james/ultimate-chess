#pragma once
#include "Piece.h"

class Collision
{
public:
	static bool isPieceCollision(const Piece& p1, const Piece& p2);
	static bool isCircleSquareCollision(const Piece& square, const Piece& circle);

	static bool isBoundaryTopCollision(const Piece& p, const int gridBoundary);
	static bool isBoundaryRightCollision(const Piece& p, const int gridBoundary);
	static bool isBoundaryLeftCollision(const Piece& p);
	static bool isBoundaryBottomCollision(const Piece& p);

	static double clampDouble(double value, double min, double max);
};

