#include "ofApp.h"


void ofApp::setup() {
  ofBackground(0);

  maxEntities = 200;

  for (int i = 0; i < maxEntities; ++i) {

    targets.push_back(new Target(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));

    vehicles.push_back(new Vehicle(
      ofGetWidth() / 2,
      ofGetHeight() / 2
    ));

  }
}

void ofApp::update() {
  ofVec2f position;

  for (int i = 0; i < vehicles.size(); ++i) {
    Target* t = targets.at(i);
    t->update();
    position = t->position();

    Vehicle* v = vehicles.at(i);
    if (v && v->alive()) {
      v->arrive(position);
      v->update();

      if (!v->alive()) {
        vehicles.erase(vehicles.begin() + i);
        vehicles.push_back(new Vehicle(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
      }
    }
  }
}

void ofApp::draw() {
  for (int i = 0; i < vehicles.size(); ++i) {
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
