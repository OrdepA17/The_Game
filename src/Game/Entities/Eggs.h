#pragma once

#include "Entity.h"
#include "Animation.h"

class Eggs: public Entity {
    private:
    int renderX=1000;
    int renderY=1000;
    public:
    Eggs(int ox, int oy);
    void tickOverworld();
    void renderOverworld();
    void setRenderX(int x){
        renderX=x; };
    void setRenderY(int y){
        renderY=y; };
    
};