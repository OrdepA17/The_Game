#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(30);
	ofSetWindowTitle("PA2");
	setupAreas();
	// Declaration and Initialization of States
	player = new Player(100, 6);
	titleState = new TitleState();
	overworldState = new OverworldState(player, currentArea);
	battleState = new BattleState(player, currentArea);
	winState = new WinState();
	endGameState = new EndGameState();
	pauseState = new PauseState();
	loadingState = new LoadingState();
	//eggs = new Eggs();

	// Initial State
	currentState = titleState;

	//Health displayed in HUD
	playerHealth=player->getHealth();
}

//--------------------------------------------------------------
void ofApp::setupAreas()
{
	//each area is 672 pixels wide and 640 pixels high, with 10 and 8 pixels of space between the player and the edge of the map respectively
	//each in-game pixel is 4 * 1 screen pixel

	vector<Enemy *> enemies2;
	ofPoint entrancePosition2(4 * 110, 4 * 116);
	//Eggs *eggs = new Eggs(ofGetWidth()/2,ofGetHeight()/2,64,64,"images/objects/eggs/eggs.png");
	vector<Entity*> entities;
	Entity *eggs = new Eggs(4*480,4*432);
	entities.push_back(eggs);
	Entity *friend1 = new Friend("Friend",4*440,4*432);
	entities.push_back(friend1);

	Enemy *area2Enemy1 = new Enemy("21", 30, 6, "enemy2", 4 * 120, 4 * 342);
	Enemy *area2Enemy2 = new Enemy("22", 30, 6, "enemy2", 4 * 254, 4 * 130);
	Enemy *area2Enemy3 = new Enemy("23", 30, 6, "enemy2", 4 * 542, 4 * 124);
	Enemy *area2Enemy4 = new Enemy("24", 30, 6, "enemy2", 4 * 532, 4 * 368);
	Enemy *area2Enemy5 = new Enemy("25", 30, 6, "enemy2", 4 * 266, 4 * 312);
	Enemy *area2Enemy6 = new Enemy("26", 30, 6, "enemy2", 4 * 194, 4 * 532);
	enemies2.push_back(area2Enemy1);
	enemies2.push_back(area2Enemy2);
	enemies2.push_back(area2Enemy3);
	enemies2.push_back(area2Enemy4);
	enemies2.push_back(area2Enemy5);
	enemies2.push_back(area2Enemy6);
	Boss *bossArea2 = new Boss ("Boss", 60, 12, "boss", 4 * 200, 4 * 400);
	area2 = new Area(NULL, "images/areas/area2.png", "audio/ice.wav", "images/stages/stage2.png", entrancePosition2, enemies2,{}, bossArea2); 
	vector<Enemy *> enemies1;
	ofPoint entrancePosition1(4 * 414, 4 * 566);
	Enemy *area1Enemy1 = new Enemy("11", 20, 4, "enemy1", 4 * 480, 4 * 432);
	Enemy *area1Enemy2 = new Enemy("12", 20, 4, "enemy1", 4 * 225, 4 * 178);
	Enemy *area1Enemy3 = new Enemy("13", 20, 4, "enemy1", 4 * 420, 4 * 178);
	enemies1.push_back(area1Enemy1);
	enemies1.push_back(area1Enemy2);
	enemies1.push_back(area1Enemy3);
	Boss *bossArea1 = new Boss ("Boss", 60, 12, "boss", 4 * 200, 4 * 400);
	area1 = new Area(area2, "images/areas/area1.png", "audio/forest.wav", "images/stages/stage1.png", entrancePosition1, enemies1, entities, bossArea1);
	currentArea = area1;
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (currentState != nullptr)
	{
		currentState->tick();

		playerHealth= battleState->getCurrentPlayerHealth();

		if (currentState->hasFinished())
		{
			currentState->toggleMusic();
			if (currentState->getNextState() == "Title")
			{
				endGameState->setWin(false);
				area1->resetEnemies();
				area2->resetEnemies();
				currentArea = area1;
				battleState->resetPlayer();
				battleState->setStage(currentArea->getStage());
				overworldState->loadArea(currentArea);
				currentState = titleState;
			}
			else if (currentState->getNextState().compare("Loading") == 0){
				
				if(currentState->getAfterState().compare("Overworld") == 0){
					loadingState->setNextState("Overworld");}
								
				
				if(currentState->getAfterState().compare("Battle") == 0){
					loadingState->setNextState("Battle");}


				if(currentState->getAfterState().compare("Title") == 0){
					loadingState->setNextState("Title");}				

				currentState = loadingState;
			
			}
			else if (currentState->getNextState() == "Overworld")
			{
				currentState = overworldState;
			}
			else if (currentState->getNextState() == "Battle")
			{
				//Fix PauseState when also in Battle State
			if(currentState == pauseState){
					battleState->setCurrentStateName("Pause");
				}
				
				else {battleState->setCurrentStateName("Battle");}

				battleState->startBattle(overworldState->getEnemy());
				currentState = battleState;
				
			}
			else if (currentState->getNextState() == "Win")
			{
				overworldState->getEnemy()->kill();

			if(!currentArea->getBoss()->isDead() && currentArea->getRemainingEnemies() == 0) currentArea->setBoss();

				if (currentArea->getRemainingEnemies() == 0 && currentArea->getBoss()->isDead())
				{
					if (currentArea->getNextArea() == NULL)
					{
						endGameState->setWin(true);
						currentState = endGameState;
					}
					else
					{
						currentArea = currentArea->getNextArea();
						overworldState->loadArea(currentArea);
						battleState->setStage(currentArea->getStage());
						currentState = winState;
					}
				}
				else
				{
					currentState = winState;
				}
			}
			//PauseState fix
			else if (currentState->getNextState()=="Pause"){
				if (currentState->getCurrentStateName()== "Overworld")
					pauseState->setNextState("Overworld");
				
				if(currentState->getCurrentStateName()== "Battle")
					pauseState->setNextState("Battle");

				currentState= pauseState;
			}
			
			else if (currentState->getNextState() == "End")
				currentState = endGameState;
			currentState->toggleMusic();
			currentState->reset();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (currentState != nullptr)
	{
		currentState->render();
	}

	//Drawing HUD
	if( currentState== overworldState){
		string HP= "HP:" + to_string(playerHealth) + "/100";
		string enemies= "REMAINING ENEMIES: " + to_string(currentArea-> getRemainingEnemies());
		ofSetColor(51,51,255);

		ofDrawRectangle(10, ofGetHeight()-57, ofGetWidth()/3 - 50, 55);

		ofSetColor(255);
		ofDrawBitmapString(HP, 40, ofGetHeight() - 40);
		ofDrawBitmapString(enemies, 10, ofGetHeight()-10);
		if(currentArea == area1){
			ofDrawBitmapString("AREA: PLAINS", 35, ofGetHeight()-25);
		}
		if(currentArea == area2){
			ofDrawBitmapString("AREA: ICE CAVES", 35, ofGetHeight()-25);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (currentState != nullptr){
		currentState->keyPressed(key);


	if(key == 'h'|| key == 'H'){ battleState->setCurrentPlayerHealth(100);}

	if (key == 'r'|| key == 'R'){

		if(currentArea == area1){area1->resetEnemies();}

		if(currentArea == area2){area2->resetEnemies();}
	}


}

}
//-----------------------------------------------------------------------

//-------------------------------------------------------------
void ofApp::keyReleased(int key)
{
		if (currentState != nullptr)
		currentState->keyReleased(key);
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	if (currentState != nullptr)
		currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	if (currentState != nullptr)
		currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	if (currentState != nullptr)
		currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	if (currentState != nullptr)
		currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
	if (currentState != nullptr)
		currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
	if (currentState != nullptr)
		currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
	if (currentState != nullptr)
		currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
	if (currentState != nullptr)
		currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
	if (currentState != nullptr)
		currentState->dragEvent(dragInfo);
}