#pragma once

#include "ofMain.h"

class Vehicle {

  ofVec2f location;
  ofVec2f velocity;
  ofVec2f acceleration;
  float size;
  // max steering force
  float maxforce;
  float maxspeed;

public:
  Vehicle(float x, float y);
  void update();
  void applyForce(const ofVec2f &force);
  void seek(const ofVec2f &target);
  void display();
};
