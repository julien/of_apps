#include "ofApp.h"
#include "flowfield.h"
#include "vehicle.h"

void ofApp::setup() {
  ofBackground(0);

  flowfield.setup(16);

  maxEntities = 300;
  for (unsigned int i = 0; i < maxEntities; ++i) {
    vehicles.push_back(new Vehicle(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
  }

}

void ofApp::update() {

  for (int i = 0; i < maxEntities; ++i) {
    Vehicle* v = vehicles.at(i);
    if (v && v->alive()) {
      v->follow(flowfield);
      v->update();
      v->boundaries();

      if (!v->alive()) {
        vehicles.erase(vehicles.begin() + i);
        vehicles.push_back(new Vehicle(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
      }
    }
  }
}


void ofApp::draw() {
  flowfield.draw();

  for (unsigned int i = 0; i < maxEntities; i++){
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
