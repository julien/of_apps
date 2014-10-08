#pragma once

#include "ofMain.h"

class Mover {

  float damp;
  float G;

public:
  float mass;
  float radius;
  float life;
  bool dead;
  float alpha;
  ofVec2f location;
  ofVec2f velocity;
  ofVec2f acceleration;

  Mover(float x, float y, float m) {
    damp = -0.009;
    G    = 0.05;

    mass = m;
    location = ofVec2f(x, y);
    velocity = ofVec2f(ofRandom(-2.0, 2.0), ofRandom(-2.0, 2.0));
    acceleration = ofVec2f(0, 0);
    radius = ofRandom(0.5, 2.5);
    life = 255;
    dead = false;
  }

  void applyForce(ofVec2f force) {
    ofVec2f f = force / mass;
    acceleration += f;
  }

  void update()  {
    velocity += acceleration;
    location += velocity;
    acceleration *= 0;

    life -= ofRandom(1, 10);
    alpha = life - ofRandom(0.2, 0.5);
    if (life < 0 || alpha < 0) {
      life = 0;
      alpha = 0;
      dead = true;
    }
  }

  void display() {
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, alpha);
    ofCircle(location.x, location.y, mass * radius, mass * radius);
    ofDisableAlphaBlending();
  }

  void checkEdges() {
    float r = radius / 2;
    int w = ofGetWidth(), h = ofGetHeight();

    if (location.x > w - r) {
      location.x = w - r;
      velocity.x *= damp;
    } else if (location.x < r) {
      location.x = r;
      velocity.x *= damp;
    }

    if (location.y > h - r) {
      velocity.y *= damp;
      location.y = h - r;
    } else if (location.y < r) {
      location.y = r;
      velocity.y *= damp;
    }
  }

  ofVec2f attract(Mover* m) {
    ofVec2f force = location - m->location;
    float distance = force.length();
    distance = ofClamp(distance, 5.0, 25.0);

    force.normalize();
    float strength = (G * mass * m->mass) / (distance * distance);
    force *= strength;
    return force;
  }

  bool alive() {
    return !dead;
  }
};

