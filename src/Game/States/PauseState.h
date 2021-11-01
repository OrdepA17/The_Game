#pragma once
#include "State.h"
class PauseState: public State
{
	private:
	ofImage screen;

	public:

	PauseState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
};
