#include "Collision.h"
#include <algorithm>

static const double EPSILON = 0.001;

bool Collision::isPieceCollision(const Piece& p1, const Piece& p2)
{
	bool result = false;

	if (p1 == p2)
	{
		return result;
	}

	if (p1.getShape() == p2.getShape())
	{
		if (p1.getShape() == Piece::Shape::Square)
		{
			// square on square collision
			result =
			!(
				p1.getX() - p1.getDistanceFromCentre() > p2.getX() + p2.getDistanceFromCentre()
				|| p1.getX() + p1.getDistanceFromCentre() < p2.getX() - p2.getDistanceFromCentre()
				|| p1.getY() + p1.getDistanceFromCentre() < p2.getY() - p2.getDistanceFromCentre()
				|| p1.getY() - p1.getDistanceFromCentre() > p2.getY() + p2.getDistanceFromCentre()
			);
		}
		else
		{
			// circle on circle collision
			result = hypot(p1.getX() - p2.getX(), p1.getY() - p2.getY()) <= (p1.getDistanceFromCentre() * 2);
		}
	}
	else
	{
		// square on circle collision
		result = (p1.getShape() == Piece::Shape::Square)
			? isCircleSquareCollision(p1, p2)
			: isCircleSquareCollision(p2, p1);
	}

	return result;
}

bool Collision::isCircleSquareCollision(const Piece& square, const Piece& circle)
{
	// clamp the values of the circle to the square to determine an overlap
	double closestX = clampDouble(circle.getX(), square.getX() - square.getDistanceFromCentre(), square.getX() + square.getDistanceFromCentre());
	double closestY = clampDouble(circle.getY(), square.getY() - square.getDistanceFromCentre(), square.getY() + square.getDistanceFromCentre());
	
	// distance between circle centre and closest X
	double distanceX = circle.getX() - closestX;

	// distance between circle centre and closest Y
	double distanceY = circle.getY() - closestY;

	// use pythagoras to determine whether the distance is within the circle radius
	return pow(distanceX, 2) + pow(distanceY, 2) < pow(circle.getDistanceFromCentre(), 2);
}

bool Collision::isBoundaryTopCollision(const Piece& p, const int gridBoundary)
{
	return EPSILON >= (gridBoundary - p.getDistanceFromCentre() - p.getY());
}

bool Collision::isBoundaryRightCollision(const Piece& p, const int gridBoundary)
{
	return EPSILON >= (gridBoundary - p.getDistanceFromCentre() - p.getX());
}

bool Collision::isBoundaryLeftCollision(const Piece& p)
{
	return EPSILON <= (p.getDistanceFromCentre() - p.getX());
}

bool Collision::isBoundaryBottomCollision(const Piece& p)
{
	return EPSILON <= (p.getDistanceFromCentre() - p.getY());
}

double Collision::clampDouble(double value, double min, double max)
{
	return (value < min) ? min : ((value > max) ? max : value);
}
