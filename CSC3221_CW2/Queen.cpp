#include "Queen.h"
#include <ctime>

void Queen::move(const double movement, Movement direction)
{
	double straightMovement = movement / ROOT_TWO;

	switch (direction)
	{
	case N:
		posY += movement;
		break;
	case NE:
		posX += straightMovement;
		posY += straightMovement;
		break;
	case E:
		posX += movement;
		break;
	case SE:
		posX += straightMovement;
		posY -= straightMovement;
		break;
	case S:
		posY -= movement;
		break;
	case SW:
		posX -= straightMovement;
		posY -= straightMovement;
		break;
	case W:
		posX -= movement;
		break;
	case NW:
		posX -= straightMovement;
		posY += straightMovement;
		break;
	}
}

double Queen::getDistanceFromCentre() const
{
	return radius;
}

int Queen::score = 0;
void Queen::incrementScore()
{
	score++;
	individualScore++;
}