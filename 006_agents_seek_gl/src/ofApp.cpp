#include "ofApp.h"

void ofApp::setup() {
  ofBackground(0);

  target = new Target(ofGetWidth() / 2, ofGetHeight() / 2);

  numVehicles = 400;
  for (int i = 0; i < numVehicles; ++i) {
    vehicles.push_back(new Vehicle(ofGetWidth() / 2, ofGetHeight() / 2));
  }

}

void ofApp::update() {
  target->update();
  ofVec2f position = target->position();

  for (int i = 0; i < numVehicles; ++i) {
    vehicles.at(i)->seek(position);
    vehicles.at(i)->update();
  }
}

void ofApp::draw() {
  for (int i = 0; i < numVehicles; ++i) {
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
