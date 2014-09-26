#pragma once

class Vehicle {

  ofVec2f location;
  ofVec2f velocity;
  ofVec2f acceleration;
  float maxspeed;
  float maxforce;
  float size;
  ofPath path;

  float birth;
  float lifetime;
  float alpha;
  bool dead;

  deque<ofVec2f> history;
  int historysize;

public:

  Vehicle(float x, float y) {
    location.set(x, y);
    acceleration.set(0, 0);
    velocity.set(0, ofRandom(-2, -4));
    maxspeed = ofRandom(2, 4);
    maxforce = ofRandom(0.01, 0.5);
    size = ofRandom(1, 5);
    historysize = ofRandom(20, 80);
    birth = ofGetElapsedTimef();
    lifetime = birth + ofRandom(2, 5);

    alpha = 255;
    dead = false;

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

    history.push_back(location);
    if (history.size() > historysize){
      history.pop_front();
    }

    float now = ofGetElapsedTimef();
    float diff = now - birth;
    alpha = ofMap(diff, birth, birth + lifetime, 255, 0, true);

    if (alpha <= 0) {
      alpha = 0;
      dead = true;
    }
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

  void arrive(const ofVec2f &target) {
    ofVec2f desired = target - location;
    float d = desired.length();

    desired.normalize();

    if (d < 50) {
      float m = ofMap(d, 0, 50, 0, maxspeed);
      desired *= m;
    } else {
      desired *= maxspeed;
    }
    ofVec2f steer = desired - velocity;
    steer.limit(maxforce);

    applyForce(steer);
  }

  void draw() {
    ofNoFill();
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, alpha);
    ofBeginShape();
    for (unsigned int i = 0; i < history.size(); i++){
      ofVertex(history[i].x, history[i].y);
    }
    ofEndShape();

    float theta = ofVec2f(1, 0).angle(velocity) + 90;
    // ofLog() << alpha;

    // ofSetHexColor(0xffffff);
    ofColor c = ofColor(255, 255, 255, alpha);
    path.setFillColor(c);

    ofPushMatrix();
    ofTranslate(location.x, location.y, 0);
    ofRotate((theta), 0, 0, 1);
    ofTranslate(-size / 2, -size / 2);

    path.draw();
    ofDisableAlphaBlending();
    ofPopMatrix();
  }

  bool alive() {
    return !dead;
  }
};
