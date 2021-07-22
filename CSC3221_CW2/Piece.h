#pragma once
#include <iostream>
#include <string>

static const double ROOT_TWO = 1.41421356237;

class Piece
{
public:
	Piece(const double xPos = 0.0, const double yPos = 0.0);
	virtual ~Piece() { }

	double getX() const;
	double getY() const;
	int getShape() const;
	bool getIsActive() const;
	std::string getName() const;
	int getIndividualScore() const;
	int getPieceID() const;

	void setInactive();
	void setPosition(const double x, const double y);

	bool operator==(const Piece& rhs) const;
	bool operator!=(const Piece& rhs) const;

	enum Shape
	{
		Circle = 0, Square = 1
	};
	enum Movement
	{
		N = 0, NE = 1, 
		E = 2, SE = 3, 
		S = 4, SW = 5, 
		W = 6, NW = 7
	};

	virtual double getDistanceFromCentre() const = 0;
	virtual void move(const double movement, Movement dir) { }
	virtual void incrementScore() { }

	friend std::ostream& operator<<(std::ostream& outStream, const Piece& piece);
protected:
	double posX;
	double posY;
	bool isActive;
	int individualScore;
	Shape shape;
	std::string pName;

	static int totalID;
	int pieceID;
};
