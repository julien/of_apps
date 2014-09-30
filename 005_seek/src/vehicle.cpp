#include "vehicle.h"

Vehicle::Vehicle(float x, float y) {
  location.set(x, y);

  acceleration.set(0, 0);
  velocity.set(0, -2);
  size = ofRandom(3, 8);
  maxspeed = ofRandom(1, 4);
  maxforce = ofRandom(0.02, 0.09);
}

void Vehicle::update() {
  velocity += acceleration;
  velocity.limit(maxspeed);

  location += velocity;
  acceleration *= 0;
}

void Vehicle::applyForce(const ofVec2f &force) {
  // we could add mass here if we want A = F / M
  acceleration += force;
}

void Vehicle::seek(const ofVec2f &target) {
  ofVec2f desired = target - location;

  desired.normalize();
  desired *= maxspeed;

  ofVec2f steer = desired - velocity;
  steer.limit(maxforce);

  applyForce(steer);
}

void Vehicle::display() {

  float theta = ofVec2f(1, 0).angle(velocity) + 90;

  ofFill();
  ofSetColor(255, 255, 255);

  ofPushMatrix();

  ofTranslate(location.x, location.y);
  ofRotate(theta);

  ofBeginShape();

  ofVertex(0, -size);
  ofVertex(-size, size);
  ofVertex(size, size);
  ofEndShape(true);

  ofPopMatrix();
}

