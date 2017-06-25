#include "FieldOfPlay.h"


FieldOfPlay::FieldOfPlay(CIwArray<Wall> initialWalls) {
	walls = initialWalls;
}

float FieldOfPlay::checkForCollisionRight(Ball ball) {
	for (int i = 0; i < walls.size(); i++) {
		Wall wall = walls[i];
		if (ball.getLocation().x + ball.getRadius() > wall.getLeftHandSideLocation()
			&& ball.getLocation().x < wall.getCentre().x
			&& (ball.getLocation().y > wall.getTopLocation() && ball.getLocation().y < wall.getBottomLocation())) {
			return(wall.getLeftHandSideLocation());
		}
	}
	return 0;
}

float FieldOfPlay::checkForCollisionLeft(Ball ball) {
	for (int i = 0; i < walls.size(); i++) {
		Wall wall = walls[i];
		if (ball.getLocation().x - ball.getRadius() < wall.getRightHandSideLocation()
			&& ball.getLocation().x > wall.getCentre().x
			&& (ball.getLocation().y > wall.getTopLocation() && ball.getLocation().y < wall.getBottomLocation())) {
			return(wall.getRightHandSideLocation());
		}
	}
	return 0;
}

float FieldOfPlay::checkForCollisionBottom(Ball ball) {
	for (int i = 0; i < walls.size(); i++) {
		Wall wall = walls[i];
		if (ball.getLocation().y + ball.getRadius() > wall.getTopLocation()
			&& ball.getLocation().y < wall.getCentre().y
			&& (ball.getLocation().x > wall.getLeftHandSideLocation() && ball.getLocation().x < wall.getRightHandSideLocation())) {
			return(wall.getTopLocation());
		}
	}
	return 0;
}

float FieldOfPlay::checkForCollisionTop(Ball ball) {
	for (int i = 0; i < walls.size(); i++) {
		Wall wall = walls[i];
		if (ball.getLocation().y - ball.getRadius() < wall.getBottomLocation()
			&& ball.getLocation().y > wall.getCentre().y
			&& (ball.getLocation().x > wall.getLeftHandSideLocation() && ball.getLocation().x < wall.getRightHandSideLocation())) {
			return(wall.getBottomLocation());
		}
	}
	return 0;
}

CornerBounce FieldOfPlay::checkForCollisionSides(Ball ball) {
	for (int i = 0; i < walls.size(); i++) {
		Wall wall = walls[i];

		CIwArray<CIwFVec2> corners;
		corners.append(CIwFVec2(wall.getLeftHandSideLocation(), wall.getTopLocation()));
		corners.append(CIwFVec2(wall.getLeftHandSideLocation(), wall.getBottomLocation()));
		corners.append(CIwFVec2(wall.getRightHandSideLocation(), wall.getTopLocation()));
		corners.append(CIwFVec2(wall.getRightHandSideLocation(), wall.getBottomLocation()));

		for (int j = 0; j < corners.size(); j++) {
			CIwFVec2 corner = corners[j];
			float delX = ball.getLocation().x - corner.x;
			float delY = ball.getLocation().y - corner.y;
			if (sqrtf(powf(delX, 2.0) + powf(delY, 2)) < ball.getRadius()) {
				return CornerBounce(atanf(delY / delX), corner);
			}
		}
	}
	return CornerBounce(5, CIwFVec2(0, 0));
}

void FieldOfPlay::paint() {
	for (int i = 0; i < walls.size(); i++) {
		Wall wall = walls[i];
		wall.paint();
	}
}
