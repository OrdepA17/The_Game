#include "Entity.h"

Entity::Entity(int ox, int oy, int ow, int oh, int fx, int fy, int fw, int fh, int health, int baseDamage, string fightingPath, string overworldPath) {
    this->ox = ox;
    this->oy = oy;
    this->oh = oh;
    this->ow = ow;
    this->fx = fx;
    this->fy = fy;
    this->fh = fh;
    this->fw = fw;
    this->health = health;
    this->baseDamage = baseDamage;

    fightingSprite.load(fightingPath);
    overworldSprite.load(overworldPath);
}

void Entity::renderOverworld() {
    overworldSprite.draw(ox, oy, ow, oh);
}

void Entity::renderFighting() {
    fightingSprite.draw(fx, fy, fw, fh);
}

bool Entity::collides(Entity* entity){
    return this->getBounds().intersects(entity->getBounds());
}

ofRectangle Entity::getBounds(){
    return ofRectangle(ox, oy, ow, oh);
}

ofRectangle Entity::getBounds(int ox, int oy){
    return ofRectangle(ox, oy, ow, oh);
}
