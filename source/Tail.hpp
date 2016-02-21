#ifndef TAIL_HPP
#define TAIL_HPP

#include <memory>
#include <vector>
#include "../../OutSystem/source/LEDMatrix.hpp"

class Tail
{
public:
	Tail(int width, int height);

	int GetLength();

	bool PointInTail(int x, int y);

	int Move(int dir);

	void Draw(LEDMatrix *display);
private:
	void GenerateFood();

	struct Point {
		int x, y;
	};

	std::vector<Point> blocks;
	Point food;

	int width, height;
};

#endif
