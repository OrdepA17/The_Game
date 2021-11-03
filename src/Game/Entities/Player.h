#pragma once

#include "Entity.h" 
#include "Animation.h"
#include "Fighters.h"

#define INIT_X 100
#define INIT_Y 100
#define CENTER_X 288
#define CENTER_Y 208

#define OXDIMENSION 2688
#define OYDIMENSION 2560


class Player : public Entity, public Fighting {
    private:
        Direction direction = Direction::up;
        int speed = 8;
        bool walking = false;
        bool canWalkUp = true;
        bool canWalkDown = true;
        bool canWalkRight = true;
        bool canWalkLeft = true;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        Animation *fighting;
        vector<char> pressedKeys;
    
    public:
        Player(int health, int baseDamage);
        ~Player();
        void tickOverworld();
        void tickFighting();
        void renderOverworld();
        void keyPressed(int key);
        void keyReleased(int key);
        void reset();
        void setSpeed(int speed);
        int getSpeed() {
            return speed;}
        void setcanWalkUp (bool b){canWalkUp=b;}
        void setcanWalkDown (bool b){canWalkDown=b;}
        void setcanWalkRight (bool b){canWalkRight=b;}
        void setcanWalkLeft (bool b){canWalkLeft=b;}
};