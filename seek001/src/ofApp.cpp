#include "ofApp.h"


void ofApp::setup() {
  ofBackground(0);

  target.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
  time0 = ofGetElapsedTimef();
  numVehicles = 300;

  for (int i = 0; i < numVehicles; ++i) {

    vehicles.push_back(new Vehicle(
          ofRandom(ofGetWidth() /2),
          ofRandom(ofGetHeight() / 2)
          ));
  }
}

void ofApp::update() {


  float time = ofGetElapsedTimef();
  if (time - time0 > 10) {
    time0 = ofGetElapsedTimef();
    target.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
  }

  for (int i = 0; i < numVehicles; ++i) {

    vehicles.at(i)->seek(target);
    vehicles.at(i)->update();
  }
}

void ofApp::draw() {

  for (int i = 0; i < numVehicles; ++i) {

    vehicles.at(i)->display();
  }
}

void ofApp::keyPressed(int key) {}
void ofApp::keyReleased(int key) {}

void ofApp::mouseMoved(int x, int y ) {
  target.set(mouseX, mouseY);
}

void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
