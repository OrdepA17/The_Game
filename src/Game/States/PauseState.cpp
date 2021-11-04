#include "PauseState.h"

PauseState::PauseState() {
	pauseScreen.load("images/ui/pauseScreen.png");
	music.load("audio/ui/errorNoise.wav");
	music.setSpeed(1.2);
	music.setVolume(1);
}
void PauseState::tick() {

}
void PauseState::render() {
	pauseScreen.draw(0,0,ofGetWidth(),ofGetHeight());
	
}

void PauseState::keyPressed(int key) {
if (key=='p'){
	setFinished(true);
}
}
void PauseState::mousePressed(int x, int y, int button){

}
void PauseState::reset(){
	setFinished(false);
}

