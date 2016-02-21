#include "Snake.hpp"
#include <iostream>

int main() {
	Snake game(WIDTH, HEIGHT);

	timespec req, rem;
	req.tv_sec = 0;
	req.tv_nsec = 200000000L;

	while(game.Update() == 0) {
		nanosleep(&req, &rem);
	}

	return 0;
}

Snake::Snake(int width, int height) {
	this->width = width;
	this->height = height;

	display.reset(new LEDMatrix(width, height));

	gameState = STATE_MAINMENU;

	initscr();

	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
}

Snake::~Snake() {

}

int GetKey() {
	int ch = getch();

	if(ch == ERR)
		return -1;
	else
		return ch;
}

void Snake::StartGame() {
	tail.reset(new Tail(width, height));
	dir = 0;
}

int Snake::Update() {
	int key = GetKey();

//	if(key > 0)
//		std::cout << key << std::endl;

	switch(gameState) {
	case STATE_MAINMENU:
		if(key == 32) {
			StartGame();
			gameState = STATE_PLAY;
		}
	break;

	case STATE_PLAY:
//		if(key > 0)
//			std::cout << key << std::endl;
		if(key == 'w')
			dir = 0;
		else if(key == 'a')
			dir = 1;
		else if(key == 's')
			dir = 2;
		else if(key == 'd')
			dir = 3;

//		std::cout << dir << std::endl;

		//If Move returns -1, game over
		if(tail->Move(dir) < 0)
			gameState = STATE_GAMEOVER;

	break;

	case STATE_GAMEOVER:
		if(key == 32) {
			gameState = STATE_MAINMENU;
		}
	break;

	default:
		break;
	}

	Render();

	return 0;
}

void Snake::Render() {
	display->Clear();

	switch(gameState) {
	case STATE_MAINMENU:
		display->DrawStr(0, 0, Color(255, 0, 0), "Snake");
	break;

	case STATE_PLAY:
		display->DrawLineHoriz(0, 0, width-1, Color(0, 0, 255));
		display->DrawLineHoriz(0, height-1, width-1, Color(0, 0, 255));
		display->DrawLineVert(0, 0, height-1, Color(0, 0, 255));
		display->DrawLineVert(width-1, 0, height-1, Color(0, 0, 255));

		tail->Draw(display.get());
	break;

	case STATE_GAMEOVER:
		display->DrawStr(0, 0, Color(255, 0, 0), "Game");
		display->DrawStr(0, 8, Color(255, 0, 0), "Over");
	break;
	}

	display->Display();
}
