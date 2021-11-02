#include "Loading.h"

LoadingState::LoadingState() {
    screen.load("images/ui/loading.png");
    music.load("audio/ui/beep.wav");
    timer = 0;
}

void LoadingState::tick() {

    timer++;

    if(timer == 90){
        setFinished(true);
        timer = 0;
    }
}

void LoadingState::render(){
    screen.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void LoadingState::keyPressed(int key) { 

}

void LoadingState::mousePressed(int x, int y, int button) {

}

void LoadingState::reset() {
    setFinished(false);
    setNextState("");
} 