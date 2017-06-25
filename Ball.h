#include "Iw2DSceneGraph.h"
#include "CornerBounce.h"
#include <math.h>

#pragma once
using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;


class Ball
{
public:
	Ball(CIwFVec2 loc, CIwFVec2 vel, CIwFVec2 scrnSize);
	CIwFVec2 getLocation();
	CIwFVec2 getVelocity();
	float getRadius();
	uint64 updateLocation(uint64 currentTime, CIwFVec2 phoneAcceleration);
	void paint();
	void bounceLeft(float);
	void bounceRight(float);
	void bounceUp(float);
	void bounceDown(float);
	void bounceAtAngle(CornerBounce);
private:
	void bounceX();
	void bounceY();
	CIwFVec2 location;
	CIwFVec2 velocity;
	CIwFVec2 screenSize;
	uint64 previousTime;
	float scale;
	float radius;

};
