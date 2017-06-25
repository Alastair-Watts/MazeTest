#include "Wall.h"



Wall::Wall(CIwFVec2 topLeft, CIwFVec2 area) {
	topCorner = topLeft;
	size = area;
}

Wall::Wall() {

}

CIwFVec2 Wall::getCentre() {
	return CIwFVec2(topCorner.x + (size.x / 2), topCorner.y + (size.y / 2));
}

float Wall::getLeftHandSideLocation() {
	return topCorner.x;
}
float Wall::getRightHandSideLocation(){
	return topCorner.x + size.x;
}
float Wall::getTopLocation(){
	return topCorner.y;
}
float Wall::getBottomLocation(){
	return topCorner.y + size.y;
}
void Wall::paint(){
	Iw2DSetColour(0xff00ff00);
	Iw2DFillRect(topCorner,size);
}

