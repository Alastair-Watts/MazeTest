#include "Ball.h"
#include <iostream>

Ball::Ball(CIwFVec2 loc, CIwFVec2 vel, CIwFVec2 scrnSize) {
	location = loc;
	velocity = vel;
	screenSize = scrnSize;
	scale = 1 / (1000 * screenSize.GetLength());
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

uint64 Ball::updateLocation(uint64 currentTime, CIwFVec2 phoneAcceleration)
{
	uint64 deltaT = currentTime - previousTime;
	previousTime = currentTime;

	CIwFVec2 newVelocity = velocity + phoneAcceleration * deltaT * scale;

	location = location + (((newVelocity + velocity) / 2)*deltaT);

	while (location.x > screenSize.x) {
		location.x = screenSize.x;
		newVelocity = CIwFVec2(velocity.x*(-0.01), velocity.y);
	}

	while (location.y > screenSize.y) {
		location.y = screenSize.y;
		newVelocity = CIwFVec2(velocity.x, velocity.y*(-0.01));
	}

	while (location.x < 0) {
		location.x = 0;
		newVelocity = CIwFVec2(velocity.x*(-0.01), velocity.y);
	}

	while (location.y < 0) {
		location.y = 0;
		newVelocity = CIwFVec2(velocity.x, velocity.y*(-0.01));
	}

	velocity = newVelocity;
	return deltaT;
}