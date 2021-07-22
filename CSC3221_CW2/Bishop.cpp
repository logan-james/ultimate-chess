#include "Bishop.h"
#include <ctime>

void Bishop::move(const double movement, Movement direction)
{
	double straightMovement = movement / ROOT_TWO;

	switch (direction)
	{
	case N:
	case NE:
		posX += straightMovement;
		posY += straightMovement;
		break;
	case E:
	case SE:
		posX += straightMovement;
		posY -= straightMovement;
		break;
	case S:
	case SW:
		posX -= straightMovement;
		posY -= straightMovement;
		break;
	case W:
	case NW:
		posX -= straightMovement;
		posY += straightMovement;
		break;
	}
}

double Bishop::getDistanceFromCentre() const
{
	return radius;
}

int Bishop::score = 0;
void Bishop::incrementScore()
{
	score++;
	individualScore++;
}