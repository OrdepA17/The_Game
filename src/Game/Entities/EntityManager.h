#pragma once

#include "Entity.h"
#include "Player.h"
#include "Fighters.h"

class EntityManager {
    public:
        ~EntityManager();
        std::vector<Entity*> entities;
        Player *player;

};