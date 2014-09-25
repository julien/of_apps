#pragma once

class Vehicle {

  ofVec2f location;
  ofVec2f velocity;
  ofVec2f acceleration;
  float maxspeed;
  float maxforce;
  float size;

  ofPath path;

public:
  Vehicle(float x, float y) {
    location.set(x, y);
    acceleration.set(0, 0);
    velocity.set(0, ofRandom(-2, -4));
    maxspeed = ofRandom(2, 4);
    maxforce = ofRandom(0.01, 0.1);
    size = ofRandom(4, 10);

    path.moveTo(ofPoint(0, -size));
    path.lineTo(ofPoint(-size, size));
    path.lineTo(ofPoint(size, size));
    path.close();
  }

  void update() {
    velocity += acceleration;
    velocity.limit(maxspeed);

    location += velocity;
    acceleration *= 0;
  }

  void applyForce(const ofVec2f &force) {
    acceleration += force;
  }

  void seek(const ofVec2f &target) {
    ofVec2f desired = target - location;

    desired.normalize();
    desired *= maxspeed;

    ofVec2f steer = desired - velocity;
    steer.limit(maxforce);

    applyForce(steer);
  }

  void draw() {

    float theta = ofVec2f(1, 0).angle(velocity) + 90;

    ofSetHexColor(0xffffff);

    ofPushMatrix();
    ofTranslate(location.x, location.y, 0);
    ofRotate((theta), 0, 0, 1);
    ofTranslate(-size / 2, -size / 2);

    path.draw();

    ofPopMatrix();
  }
};
