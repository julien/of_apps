#pragma once

#include "ofMain.h"

class Mover {
public:
  ofVec2f location;
  ofVec2f velocity;
  ofVec2f acceleration;
  float mass;
  float radius;

  float damp;
  float G;

  Mover(float x, float y, float m);
  void applyForce(ofVec2f force);
  void update();
  void display();
  void checkEdges();

  ofVec2f attract(Mover* m);
};
