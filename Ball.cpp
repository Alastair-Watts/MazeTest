#include "Ball.h"
#include <iostream>

Ball::Ball(CIwFVec2 loc, CIwFVec2 vel, CIwFVec2 scrnSize) {
	location = loc;
	velocity = vel;
	screenSize = scrnSize;
	radius = scrnSize.x / 20;
	scale = 1 / (500 * screenSize.GetLength());
	previousTime = s3eTimerGetMs();
}

CIwFVec2 Ball::getLocation(void)
{
	return location;
}

CIwFVec2 Ball::getVelocity(void)
{
	return velocity;
}

void Ball::paint() {
	CIwFVec2 sizeOfCircle = CIwFVec2(radius, radius);
	Iw2DSetColour(0xffff0000);
	Iw2DFillArc(location, sizeOfCircle, 0, 2 * PI);
}

uint64 Ball::updateLocation(uint64 currentTime, CIwFVec2 phoneAcceleration)
{
	uint64 deltaT = currentTime - previousTime;
	previousTime = currentTime;

	float coefficientOfFriction = 1000;
	CIwFVec2 frictionalDecceleration = velocity * coefficientOfFriction;

	CIwFVec2 newVelocity = velocity + (phoneAcceleration - frictionalDecceleration) * deltaT * scale;

	location = location + (((newVelocity + velocity) / 2)*deltaT);

	float e = -0.25;

	while (location.x + radius > screenSize.x) {
		location.x = screenSize.x - radius;
		newVelocity = CIwFVec2(velocity.x*e, velocity.y);
	}

	while (location.y + radius > screenSize.y) {
		location.y = screenSize.y -radius;
		newVelocity = CIwFVec2(velocity.x, velocity.y*e);
	}

	while (location.x < radius) {
		location.x = 0 + radius;
		newVelocity = CIwFVec2(velocity.x*e, velocity.y);
	}

	while (location.y < radius) {
		location.y = 0 + radius;
		newVelocity = CIwFVec2(velocity.x, velocity.y*e);
	}

	velocity = newVelocity;
	return deltaT;
}