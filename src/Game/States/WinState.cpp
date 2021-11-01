#include "WinState.h"

WinState::WinState() {
    screen.load("images/ui/winscreen.png");
    music.load("audio/ui/beep.wav");

}

void WinState::tick() {

}

void WinState::render(){
    screen.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void WinState::keyPressed(int key) {
    setNextState("Loading");
    setNextState("Overworld");
    setFinished(true);
}

void WinState::mousePressed(int x, int y, int button) {

}

void WinState::reset() {
    setFinished(false);
    setNextState("");
}
