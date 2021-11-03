#pragma once
#include "ofMain.h"
enum Direction {left, right, up, down};
class Entity {
    protected:

        // Overworld Coordinates and dimensions
        int ox, oy, ow, oh;
       
        ofImage overworldSprite;

    public:
        Entity(int ox, int oy, int ow, int oh, string overworldPath);
        virtual void tickOverworld() = 0;
        
        virtual void renderOverworld();
    
        int getOX() { return ox; };
        int getOY() { return oy; };
        int getOW() { return ow; };
        int getOH() { return oh; };
        ofRectangle getBounds();
        ofRectangle getBounds(int ox, int oy);
        bool collides(Entity* entity);
        void setOX(int ox) { this-> ox = ox; };
        void setOY(int oy) { this-> oy = oy; };
};