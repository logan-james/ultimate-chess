#include "Rook.h"

void Rook::move(const double movement, Movement direction)
{
	switch (direction)
	{
	case N:
	case NE:
		posY += movement;
		break;
	case SE:
	case E:
		posX += movement;
		break;
	case S:
	case SW:
		posY -= movement;
		break;
	case W:
	case NW:
		posX -= movement;
		break;
	}
}

double Rook::getDistanceFromCentre() const
{
	return length / 2;
}

int Rook::score = 0;
void Rook::incrementScore()
{
	score++;
	individualScore++;
}
