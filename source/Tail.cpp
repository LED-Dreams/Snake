#include "Tail.hpp"
#include <iostream>

Tail::Tail(int width, int height) {
	this->width = width;
	this->height = height;

	Point start = {width/2, height/2};

	blocks.push_back(start);

	GenerateFood();
}

int Tail::GetLength() {
	return blocks.size();
}

bool Tail::PointInTail(int x, int y) {
	for(auto &p : blocks) {
		if(p.x == x && p.y == y)
			return true;
	}

	return false;
}

//@param dir:
//0 - up
//1 - left
//2 - down
//3 - right
int Tail::Move(int dir) {
	bool hasEaten = false;

	Point newPoint = blocks[0];

	if(dir == 0)
		newPoint.y--;
	else if(dir == 1)
		newPoint.x--;
	else if(dir == 2)
		newPoint.y++;
	else
		newPoint.x++;

	if(newPoint.y > (height-2) || newPoint.y < 1 || newPoint.x > (width-2) || newPoint.x < 1)
		return -1;

	if(PointInTail(newPoint.x, newPoint.y))
		return -1;

	if(hasEaten = food.x == newPoint.x && food.y == newPoint.y)
		blocks.push_back(blocks[blocks.size()-1]);

	for(int i = blocks.size()-1; i > 0; i--) {
		blocks[i] = blocks[i-1];
	}

	blocks[0] = newPoint;

	if(hasEaten)
		GenerateFood();

	return 0;
}

void Tail::Draw(LEDMatrix *display) {
	for(auto &p : blocks) {
		display->SetPixel(p.x, p.y, Color(255, 255, 0));
	}

	display->SetPixel(food.x, food.y, Color(255, 255, 0));
}

void Tail::GenerateFood() {
	int x, y;

	do {
		x = 1 + (rand() % (width - 2));
		y = 1 + (rand() % (height - 2));
	}
	while(PointInTail(x, y));

	food.x = x;
	food.y = y;
}
