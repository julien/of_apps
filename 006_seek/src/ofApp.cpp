#include "ofApp.h"


void ofApp::setup() {
  ofBackground(0);

  maxEntities = 900;

  for (int i = 0; i < maxEntities; ++i) {

    targets.push_back(new Target(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));

    vehicles.push_back(new Vehicle(
      ofRandom(ofGetWidth()),
      ofRandom(ofGetHeight())
    ));

  }
}

void ofApp::update() {

  ofVec2f position;

  for (int i = 0; i < maxEntities; ++i) {
    targets.at(i)->update();
    position = targets.at(i)->position();
    vehicles.at(i)->seek(position);
    vehicles.at(i)->update();
  }
}

void ofApp::draw() {
  for (int i = 0; i < maxEntities; ++i) {
    vehicles.at(i)->draw();
  }
}

void ofApp::keyPressed(int key) {}
void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y ) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
