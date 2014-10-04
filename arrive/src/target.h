#pragma once

#include "ofMain.h"

class Target {

  ofPoint origin;
  ofPoint location;
  ofPoint range;
  ofPoint angle;
  ofPoint speed;

public:
  Target(float x, float y) {
    origin.set(x, y);
    location.set(x, y);
    range.set(ofRandom(100, 300), ofRandom(100, 300));
    angle.set(0, 0);
    speed.set(ofRandom(0.02), ofRandom(0.02));
  }

  void update() {
    float x = origin.x + cos(angle.x) * range.x;
    float y = origin.y + sin(angle.y) * range.y;
    angle.x += speed.x;
    angle.y += speed.y;
    location.set(x, y);
  }

  void debugDraw() {
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofCircle(location.x, location.y, 8);
  }

  ofVec2f position() {
    return ofVec2f(location.x, location.y);
  }
};
