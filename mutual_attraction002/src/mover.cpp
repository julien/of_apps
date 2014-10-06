#include "mover.h"

Mover::Mover(float x, float y, float m) {
  damp = -0.978;
  G    = 0.5;

  mass = m;
  location = ofVec2f(x, y);
  velocity = ofVec2f(ofRandom(-2.0, 2.0), ofRandom(-2.0, 2.0));
  acceleration = ofVec2f(0, 0);
  radius = ofRandom(0.5, 2.5);
}

void Mover::applyForce(ofVec2f force) {
  ofVec2f f = force / mass;
  acceleration += f;
}

void Mover::update() {
  velocity += acceleration;
  location += velocity;
  acceleration *= 0;
}

void Mover::display() {
  ofCircle(location.x, location.y, mass * radius, mass * radius);
}

void Mover::checkEdges() {
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

ofVec2f Mover::attract(Mover* m) {
  ofVec2f force = location - m->location;
  float distance = force.length();
  distance = ofClamp(distance, 5.0, 25.0);

  force.normalize();
  float strength = (G * mass * m->mass) / (distance * distance);
  force *= strength;
  return force;
}
