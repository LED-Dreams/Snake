#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <time.h>
#include <memory>
#include <curses.h>
#include "../../OutSystem/source/LEDMatrix.hpp"
#include "Tail.hpp"

#define WIDTH		32
#define HEIGHT		24

class Snake
{
public:
	Snake(int width, int height);
	~Snake();

	int Update();

private:
	void StartGame();
	void Render();

	enum {
		STATE_MAINMENU,
		STATE_PLAY,
		STATE_GAMEOVER
	} gameState;

	std::unique_ptr<LEDMatrix> display;
	std::unique_ptr<Tail> tail;

	int width, height, dir;
};


#endif
