#include "Friend.h"

Friend :: Friend(string name, int ox, int oy): Entity(ox-100, oy+100, 80, 80, "images/entities/friend/FriendlyTurkey.png")
{
    entityName = name;

    overworldSprite.load("images/entities/friend/friend-ow-up1.png");
    speach.load("images/ui/HelloThere.jpg");

    vector<ofImage> downFrames = {};
    vector<ofImage> upFrames = {};
    vector<ofImage> leftFrames = {};
    vector<ofImage> rightFrames = {};
    ofImage temp;

    for (int i = 1; i < 4; i++)
    {
        temp.load("images/entities/" + entityName + "/downframes/" + entityName + "-ow-down" + std::to_string(i == 3 ? 1 : i) + ".png");
        downFrames.push_back(temp);
        temp.load("images/entities/" + entityName + "/upframes/" + entityName + "-ow-up" + std::to_string(i == 3 ? 1 : i) + ".png");
        upFrames.push_back(temp);
        temp.load("images/entities/" + entityName + "/leftframes/" + entityName + "-ow-left" + std::to_string(i == 3 ? 1 : i) + ".png");
        leftFrames.push_back(temp);
        temp.load("images/entities/" + entityName + "/rightframes/" + entityName + "-ow-right" + std::to_string(i == 3 ? 1 : i) + ".png");
        rightFrames.push_back(temp);
    }


    walkDown = new Animation(3, downFrames);
    walkUp = new Animation(3, upFrames);
    walkLeft = new Animation(3, leftFrames);
    walkRight = new Animation(3, rightFrames);

}

void Friend::tickOverworld()
{
    if (moveTimer == 60 && (!interacting || !canInteract))
        {
            switch (direction)
            {
            case Direction::left:
                direction = Direction::down;
                break;
            case Direction::right:
                direction = Direction::up;
                break;
            case Direction::up:
                direction = Direction::left;
                break;
            case Direction::down:
                direction = Direction::right;
                break;
        }
    }

    if (moveTimer == 45 || canInteract || interacting) walking = false;
    if(moveTimer > 45 && !canInteract && !interacting) walking = true;
    if(!canInteract && !interacting) moveTimer--;
    if (moveTimer == 0){
        moveTimer = 60;
        walking = true;
    }

    if (walking)
    {
        switch (direction)
        {
        case Direction::left:
            this->ox -= speed;
            walkLeft->tick();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::right:
            this->ox += speed;
            walkRight->tick();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        case Direction::up:
            this->oy -= speed;
            walkUp->tick();
            overworldSprite = walkUp->getCurrentFrame();
            break;
        case Direction::down:
            this->oy += speed;
            walkDown->tick();
            overworldSprite = walkDown->getCurrentFrame();
            break;
        }
    }
    else
    {
       switch (direction)
        {
        case Direction::left:
            overworldSprite.load("images/entities/" + entityName + "/leftframes/" + entityName + "-ow-left1.png");
            break;
        case Direction::right:
            overworldSprite.load("images/entities/" + entityName + "/rightframes/" + entityName + "-ow-right1.png");
            break;
        case Direction::up:
            overworldSprite.load("images/entities/" + entityName + "/upframes/" + entityName + "-ow-up1.png");
            break;
        case Direction::down:
            overworldSprite.load("images/entities/" + entityName + "/downframes/" + entityName + "-ow-down1.png");
            break;
        }
    }

}

void Friend::renderOverworld()
{
    overworldSprite.draw(renderX, renderY, ow, oh);
    
    if (interacting) {speach.draw(renderX, renderY - 50, 140, 70);}
}
Friend::~Friend(){
    delete walkDown;
    delete walkUp;
    delete walkLeft;
    delete walkRight;
}