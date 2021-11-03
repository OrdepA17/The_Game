#include "Eggs.h"

Eggs::Eggs (int ox, int oy): Entity( ox, oy,64,64,"images/entities/eggs/eggs.png")

{
    overworldSprite.load("images/entities/eggs/eggs.png");
}

void Eggs::tickOverworld()
{

}
void Eggs::renderOverworld()
{
overworldSprite.draw(renderX,renderY, ow, oh);
}
