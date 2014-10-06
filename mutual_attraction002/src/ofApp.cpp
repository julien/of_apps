#include "ofApp.h"


void ofApp::setup(){

  ofSetFrameRate(60);
  ofBackground(0);

  spring = 0.03;
  factor = 1;
  numMovers = 200;
  maxMovers = 500;

  for (int i = 0; i < numMovers; ++i) {
    movers.push_back(
      new Mover(ofRandom(ofGetWidth()),
                ofRandom(ofGetHeight()),
                ofRandom(1.0, 20.0)));
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

    //ofNoFill();

    ofSetColor(255, 255, 255, 255);

    ofBeginShape();

      ofVertex(a->location.x, a->location.y);
      ofVertex(b->location.x, b->location.y);

    ofEndShape();

  }
}

void ofApp::update() {
  int i;
  int j;
  // TODO: optimize this shit
  for (i = 0; i < numMovers; ++i) {
    for (j = 0; j < numMovers; ++j) {
      if (i != j) {
        ofVec2f force = movers.at(j)->attract(movers.at(i));
        force *= factor;
        movers.at(i)->applyForce(force);
      }
    }
    movers.at(i)->update();
    movers.at(i)->checkEdges();
  }

  for (i = 0; i < numMovers - 1; ++i) {
    Mover *mA = movers.at(i);
    for (j = 1; j < numMovers; ++j) {
      Mover *mB = movers.at(j);
      checkCollision(mA, mB);
    }
  }
}

void ofApp::draw() {
  for (int i = 0; i < numMovers; ++i) {
    movers.at(i)->display();
  }
}

void ofApp::mousePressed(int x, int y, int button) {
  numMovers = movers.size();

  if (numMovers < maxMovers) {

    movers.push_back(
      new Mover(mouseX,
                mouseY,
                ofRandom(1.0, 10.0)));
    ++numMovers;
  }
}

void ofApp::keyPressed(int key) {}
void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
