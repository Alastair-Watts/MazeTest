#include "Ball.h"
#include <iostream>
#include <math.h>

#define e 0.5

int sign(float);

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

float Ball::getRadius(void)
{
	return radius;
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

	velocity = newVelocity;

	if (location.x + radius > screenSize.x) {
		bounceLeft(screenSize.x);
	}

	if (location.y + radius > screenSize.y) {
		bounceUp(screenSize.y);
	}

	if (location.x < radius) {
		bounceRight(0);
	}

	if (location.y < radius) {
		bounceDown(0);
	}
	return deltaT;
}

void Ball::bounceLeft(float bounceLocation) {
	location.x = bounceLocation - radius;
	bounceX();
}

void Ball::bounceRight(float bounceLocation) {
	location.x = bounceLocation + radius;
	bounceX();
}

void Ball::bounceUp(float bounceLocation) {
	location.y = bounceLocation - radius;
	bounceY();
}

void Ball::bounceDown(float bounceLocation) {
	location.y = bounceLocation + radius;
	bounceY();
}

void Ball::bounceX() {
	velocity = CIwFVec2(-velocity.x*e, velocity.y);
}

void Ball::bounceY() {
	velocity = CIwFVec2(velocity.x, -velocity.y*e);
}


int sign(float x) {
	return (x > 0) - (x < 0);
}

void Ball::bounceAtAngle(CornerBounce bounceLocation) {
	float xOffset = location.x - bounceLocation.cornerLocation.x;
	float yOffset = location.y - bounceLocation.cornerLocation.y;

	float centreToCorner = sqrtf(powf(xOffset, 2) + powf(yOffset, 2));
	float delR = radius - centreToCorner;
	float delRSquared = powf(delR, 2);

	float delX = (sign(xOffset)) * sqrtf(delRSquared / (powf(tanf(bounceLocation.angle), 2) + 1));
	location.x = location.x + delX;
	float delY = (sign(yOffset)) * sqrtf(delRSquared / (1 + (1 / powf(tanf(bounceLocation.angle), 2))));
	location.y = location.y + delY;

	float s = sinf(bounceLocation.angle);
	float c = cosf(bounceLocation.angle);

	velocity = CIwFVec2(
		(1 - e) * velocity.y * s * c + velocity.x * (powf(s, 2) - e*powf(c, 2)),
		(1 - e) * velocity.x * s * c + velocity.y * (powf(c, 2) - e*powf(s, 2)));
}
