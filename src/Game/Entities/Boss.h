#pragma once
#include "Enemy.h"


class Boss : public Enemy {

    private:
    int angered = 0;

    public:
    Boss(string id, int health, int baseDamage, string entityName, int ox, int oy);
    void tickFighting();
    int getTimesDefeated() {return angered;}
    void setTimesDefeated(int mad) {angered = mad;}
    ~Boss();
    

};