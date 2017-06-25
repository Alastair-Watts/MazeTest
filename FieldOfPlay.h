#include "Ball.h"
#include "Wall.h"
#include "CornerBounce.h"
#include <math.h>

#pragma once
class FieldOfPlay
{
public:
	FieldOfPlay(CIwArray<Wall>);
	float checkForCollisionLeft(Ball);
	float checkForCollisionRight(Ball);
	float checkForCollisionBottom(Ball);
	float checkForCollisionTop(Ball);
	CornerBounce checkForCollisionSides(Ball);
	void addWall(Wall);
	void paint();

private:
	CIwArray<Wall> walls;
};

