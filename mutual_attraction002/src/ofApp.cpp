#include "ofApp.h"

void ofApp::addMovers(int num) {

  for (int i = 0; i < num; ++i) {
    movers.push_back(
      new Mover(ofRandom(ofGetWidth()),
                ofRandom(ofGetHeight()),
                ofRandom(1.0, 6.0)));
  }
}

void ofApp::checkCollision(Mover *a, Mover *b) {
  float dx = b->location.x - a->location.x;
  float dy = b->location.y - a->location.y;
  float dist = sqrt(dx * dx + dy * dy);
  float min_dist = a->radius + b->radius;

  if (dist < min_dist) {

    float angle = atan2(dy, dx);
    float tx = a->location.x + cos(angle) * min_dist;
    float ty = a->location.y + sin(angle) * min_dist;
    float ax = (tx - b->location.x) * spring * 0.5;
    float ay = (ty - b->location.y) * spring * 0.5;

    a->velocity.x -= ax;
    a->velocity.y -= ay;

    b->velocity.x += ax;
    b->velocity.y += ay;

    ofLine(a->location.x, a->location.y, b->location.x, b->location.y);
  }
}


void ofApp::setup(){

  ofSetFrameRate(60);
  ofBackground(0);

  spring = 0.03;
  factor = 1;
  numMovers = 300;
  maxMovers = 500;
  startTime = ofGetElapsedTimef();

  addMovers(numMovers);
}

void ofApp::update() {
  int i;
  int j;
  int l = movers.size();

  for (i = 0; i < l; ++i) {
    Mover *a = movers.at(i);
    if (a && a->alive()) {
      a->update();
      a->checkEdges();

      if (!a->alive()) {
        movers.erase(movers.begin() + i);

        addMovers(1);
      }
    }
  }

  l = movers.size();
  for (i = 0; i < l - 1; ++i) {
    Mover *a = movers.at(i);

    for (j = 1; j < l; ++j) {
      Mover *b = movers.at(j);

      ofVec2f force = b->attract(a);
      force *= factor;
      a->applyForce(force);
      checkCollision(a, b);
    }
  }

  // float now = ofGetElapsedTimef();
  // if (now - startTime > 2) {

  //   addMovers(ofRandom(1, 5));
  // }

}

void ofApp::draw() {
  int l = movers.size();
  for (int i = 0; i < l; ++i) {
    movers.at(i)->display();
  }
}

void ofApp::mousePressed(int x, int y, int button) {
  // int l = ofRandom(10, numMovers);
  // for (int i = 0; i < l; ++i) {
  //   movers.push_back(new Mover(ofRandom(ofGetWidth()),
  //         ofRandom(ofGetHeight()),
  //         ofRandom(1.0, 6.0)));
  // }
}

void ofApp::keyPressed(int key) {}
void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
