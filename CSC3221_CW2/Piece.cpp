#include "Piece.h"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

Piece::Piece(const double xPos, const double yPos)
{
	posX = xPos;
	posY = yPos;
	isActive = true;
	individualScore = 0;

	pieceID = totalID;
	totalID++;
}

double Piece::getX() const
{
	return posX;
}

double Piece::getY() const
{
	return posY;
}

int Piece::getShape() const
{
	return shape;
}

bool Piece::getIsActive() const
{
	return isActive;
}

std::string Piece::getName() const
{
	return pName;
}

int Piece::getIndividualScore() const
{
	return individualScore;
}

int Piece::getPieceID() const
{
	return pieceID;
}

void Piece::setInactive()
{
	isActive = false;
}

void Piece::setPosition(const double x, const double y)
{
	posX = x;
	posY = y;
}

bool Piece::operator==(const Piece& rhs) const
{
	return pieceID == rhs.getPieceID();
}

bool Piece::operator!=(const Piece& rhs) const
{
	return !(*this == rhs);
}

ostream& operator<<(ostream& outStream, const Piece& piece)
{
	outStream << "Piece " << piece.getName() 
		<< " is at (" << to_string(piece.getX()) << "," << to_string(piece.getY()) << ")" << endl;

	outStream << "This piece wiped out " << piece.getIndividualScore() << " piece(s) during its lifetime" << endl;

	return outStream;
}