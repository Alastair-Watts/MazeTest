#include "Iw2DSceneGraph.h"

#pragma once
using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;


class Ball
{
public:
	Ball(CIwFVec2 loc, CIwFVec2 vel, CIwFVec2 scrnSize);
	CIwFVec2 getLocation();
	CIwFVec2 getVelocity();
	uint64 updateLocation(uint64 currentTime, CIwFVec2 phoneAcceleration);
private:
	CIwFVec2 location;
	CIwFVec2 velocity;
	CIwFVec2 screenSize;
	uint64 previousTime;
	float scale;

};
