#include "OverworldState.h"

OverworldState::OverworldState(Player *player, Area *area)
{
    this->player = player;
    camera = new OverworldCamera(player);
    loadArea(area);
    music.setVolume(0.25);
    music.setLoop(true);
}

void OverworldState::loadArea(Area *area)
{
    this->area = area;
    overworldImage = area->getImage();
    music = area->getMusic();
    music.setVolume(0.25);
    music.setLoop(true);
    player->setOX(area->getEntrancePos().x);
    player->setOY(area->getEntrancePos().y);
}

void OverworldState::checkPlayerCol(){

    player-> setcanWalkUp (true);
    player-> setcanWalkDown (true);
    player-> setcanWalkRight (true);
    player-> setcanWalkLeft (true);

    for(Entity *e : area-> getEntities()){
        if(player->getBounds(player->getOX(),player->getOY() + player->getSpeed()).intersects(e->getBounds())){
            player->setcanWalkDown(false);
        }
        if(player->getBounds(player->getOX(),player->getOY() - player->getSpeed()).intersects(e->getBounds())){
            player->setcanWalkUp(false);
        }
        if(player->getBounds(player->getOX() - player->getSpeed(),player->getOY()).intersects(e->getBounds())){
            player->setcanWalkLeft(false);
        }
        if(player->getBounds(player->getOX() + player->getSpeed(),player->getOY()).intersects(e->getBounds())){
            player->setcanWalkRight(false);
        }
    }
    for(Entity *e : area->getEntities()){

        Friend* f = dynamic_cast<Friend*>(e);
        if(f == NULL) continue;
        f->setCanInteract(false);

        if(player->getBounds(player->getOX(),player->getOY() + player->getSpeed() * 2).intersects(e->getBounds())){
            f->setCanInteract(true);
        }
        if(player->getBounds(player->getOX(),player->getOY() - player->getSpeed() * 2).intersects(e->getBounds())){
            f->setCanInteract(true);
        }
        if(player->getBounds(player->getOX() - player->getSpeed() * 2,player->getOY()).intersects(e->getBounds())){
            f->setCanInteract(true);
        }
        if(player->getBounds(player->getOX() + player->getSpeed() * 2,player->getOY()).intersects(e->getBounds())){
            f->setCanInteract(true);
        }
    }
}

void OverworldState::tick()
{
    checkPlayerCol();

    player->tickOverworld();
    for (unsigned int i = 0; i < area->getEnemies().size(); i++)
    {
        if (!area->getEnemies().at(i)->isDead())
        {
            area->getEnemies().at(i)->tickOverworld();
            if (player->collides(area->getEnemies().at(i)))
            {
                setEnemy(area->getEnemies().at(i));
                setNextState("Loading");
                setAfterState("Battle");
                setFinished(true);
            }
        }
    }
    for (unsigned int i = 0; i < area->getEntities().size(); i++)
    {
         area->getEntities().at(i)->tickOverworld();
            if (player->collides(area->getEntities().at(i)))
            {
               player->setSpeed(0); 
            }
                
    }
    camera->tick();
}

void OverworldState::render()
{
    overworldImage.drawSubsection(0, 0, camera->getDimensionX(), camera->getDimensionY(), camera->getLeftCornerX(), camera->getTopCornerY());
    player->renderOverworld();

    for (unsigned int i = 0; i < area->getEnemies().size(); i++)
    {
        if (!area->getEnemies().at(i)->isDead())
        {
            int playerDistanceX = area->getEnemies().at(i)->getOX() - camera->getPlayerX();
            int playerDistanceY = area->getEnemies().at(i)->getOY() - camera->getPlayerY();
            area->getEnemies().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            area->getEnemies().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            area->getEnemies().at(i)->renderOverworld();
        }
    }

    for (unsigned int i = 0; i < area->getEntities().size(); i++)
    {
        
        Eggs* eggs = dynamic_cast<Eggs*>(area->getEntities().at(i));

        if (eggs == NULL) continue;

        int playerDistanceX = area->getEntities().at(i)->getOX() - camera->getPlayerX();
        int playerDistanceY = area->getEntities().at(i)->getOY() - camera->getPlayerY();
        eggs->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
        eggs->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
        eggs->renderOverworld();
        
    }

    for (unsigned int i = 0; i < area->getEntities().size(); i++)
    {
        
        Friend* friend1 = dynamic_cast<Friend*>(area->getEntities().at(i));

        if (friend1 == NULL) continue;

        int playerDistanceX = area->getEntities().at(i)->getOX() - camera->getPlayerX();
        int playerDistanceY = area->getEntities().at(i)->getOY() - camera->getPlayerY();
        friend1->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
        friend1->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
        friend1->renderOverworld();
        
    }
}

void OverworldState::playerInteractions(){

    for(Entity *e : area->getEntities()){

        Friend* f = dynamic_cast<Friend*>(e);

        if (f == NULL) continue;

        if(f->getCanInteract()) {f->setInteracting(!f->getInteracting());}
    }
}

void OverworldState::keyPressed(int key)
{
    player->keyPressed(key);

    if (key == 'p'){
        setCurrentStateName ("Overworld");
        setNextState("Pause");
        setFinished(true);
        return;
    }
    if (key == 'e') playerInteractions();
    

}

void OverworldState::keyReleased(int key)
{
    player->keyReleased(key);
}

void OverworldState::mousePressed(int x, int y, int button)
{
}

void OverworldState::reset()
{
    player->keyReleased('w');
    player->keyReleased('a');
    player->keyReleased('s');
    player->keyReleased('d');
    setFinished(false);
    setNextState("");
}