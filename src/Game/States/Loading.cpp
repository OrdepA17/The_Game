#include "Loading.h"


LoadingState::LoadingState() {
    screen.load("images/ui/loading.png");
    screen.draw(0,0,ofGetHeight(),ofGetWidth());
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
    setFinished(false);
    //setNextState("");
    }
