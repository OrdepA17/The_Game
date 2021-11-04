#pragma once

#include "Entity.h"
#include "Animation.h"


class Friend : public Entity {
    private:
        Direction direction = Direction::down;
        int speed = 8;
        bool walking = false;
        int renderX = 1000;
        int renderY = 1000;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        string id;
        int moveTimer = 60;
        string entityName;
        bool interacting = false;
        bool canInteract = false;
        ofImage message;

    
    public:
        Friend(string name, int ox, int oy);
        ~Friend();
        void setRenderX(int x){ renderX = x; };
        void setRenderY(int y){ renderY = y; };
        void tickOverworld();
        void renderOverworld();
        void keyPressed(int key);
        void keyReleased(int key);
        string getId(){ return id; };
        ofImage getSprite() { return overworldSprite;};
        void setCanInteract(bool i){canInteract = i;}
        bool getCanInteract() {return canInteract;}
        void setInteracting(bool i){interacting = i;}
        bool getInteracting(){return interacting;}
};