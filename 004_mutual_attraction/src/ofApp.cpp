#include "ofApp.h"

void ofApp::setup(){
  ofSetFrameRate(60);
  ofBackground(0);

  factor = 1;
  numMovers = 20;
  maxMovers = 500;

  for (int i = 0; i < numMovers; ++i) {
    movers.push_back(
      new Mover(ofRandom(ofGetWidth()),
                ofRandom(ofGetHeight()),
                ofRandom(1.0, 10.0)));
  }
}

void ofApp::update() {
  for (int i = 0; i < numMovers; ++i) {
    for (int j = 0; j < numMovers; ++j) {
      if (i != j) {
        ofVec2f force = movers.at(j)->attract(movers.at(i));
        force *= factor;
        movers.at(i)->applyForce(force);
      }
    }
    movers.at(i)->update();
    movers.at(i)->checkEdges();
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
