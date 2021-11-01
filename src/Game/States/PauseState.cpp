#include "PauseState.h"

PauseState::PauseState() {
	screen.load("images/ui/pause.png");
	music.load("audio/ui/beep.wav");

}
void PauseState::tick() {

}
void PauseState::render() {
	screen.draw(0,0,ofGetWidth(),ofGetHeight());
}

void PauseState::keyPressed(int key) {
if (key=='p'){
	setNextState("overworld");
	setFinished(true);
}
}
void PauseState::mousePressed(int x, int y, int button){

}
void PauseState::reset(){
	setFinished(false);
	setNextState("");
}

