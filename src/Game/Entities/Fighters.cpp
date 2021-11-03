#include "Fighters.h"

Fighting::Fighting(int fx, int fy, int fw, int fh, int health, int baseDamage, string fightingPath) {
    this->fx = fx;
    this->fy = fy;
    this->fh = fh;
    this->fw = fw;
    this->health = health;
    this->baseDamage = baseDamage;

    fightingSprite.load(fightingPath);
}

void Fighting::renderFighting() {
    fightingSprite.draw(fx, fy, fw, fh);
}