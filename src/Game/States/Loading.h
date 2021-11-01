#pragma once

#include "State.h"
#include "Player.h"
#include "Enemy.h"

class LoadingState : public State
{
    private:
        ofImage screen;

    public:
        LoadingState();
        void tick();
        void render();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void reset();
        
        int timer;
};