#pragma once
#include "ofMain.h"

// Since all entities CAN be fighters the fighting class will provide the ability to enter battle state and fight  
// Example: Player, Enemy and Boss can be fighters but Static entitiy and Friend can not be fighters.
class Fighting{
    protected:
            int baseDamage;
            int health;

            // Fighting coordinates and dimensions
            int fx, fy, fw, fh;
            ofImage fightingSprite;           


    public:
            Fighting (int fx, int fy, int fw, int fh, int health, int baseDamage, string fightingPath);
            virtual void tickFighting() = 0;
            virtual void renderFighting();
            int getHealth() { return health; };
            void setHealth(int health) { this->health = health; };
            int getDmg() { return baseDamage; };
            void setDmg(int baseDamage) { this->baseDamage = baseDamage; };

};