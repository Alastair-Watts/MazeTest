#include "Iw2DSceneGraph.h"

#pragma once
class Wall
{
public:
	Wall(CIwFVec2 topLeft, CIwFVec2 area);
	Wall();
	float getLeftHandSideLocation();
	float getRightHandSideLocation();
	float getTopLocation();
	float getBottomLocation();
	CIwFVec2 getCentre();
	void paint();
private:
	CIwFVec2 topCorner;
	CIwFVec2 size;
};

