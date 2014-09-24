#include "ofApp.h"

Params param;

void Params::setup() {
  eCenter = ofPoint(ofGetWidth()/ 2, ofGetHeight() / 2);
  eRad = 50;
  velRad = 200;
  lifeTime = 1.0;
  rotate = 90;
}

ofPoint randomPointInCircle(float maxRad) {
  ofPoint pt;
  float rad = ofRandom(0, maxRad);
  float angle = ofRandom(0, M_TWO_PI);
  pt.x = cos(angle) * rad;
  pt.y = sin(angle) * rad;
  return pt;
}

Particle::Particle() {
  live = false;
}

void Particle::setup() {
  pos = param.eCenter + randomPointInCircle(param.eRad);
  vel = randomPointInCircle(param.velRad);
  time = 0;
  lifeTime = param.lifeTime;
  live = true;
}

void Particle::update(float dt) {
  if (live) {
    // rotate velocity
    vel.rotate(0, 0, param.rotate * dt);

    // update position
    pos += vel * dt;

    // update time and check life
    time += dt;
    if (time >= lifeTime) {
      live = false;
    }
  }
}

void Particle::draw() {
  if (live) {
    // size
    float size = ofMap(fabs(time - lifeTime / 2), 0,  lifeTime / 2, 3, 1);

    // color
    ofColor color = ofColor::red;
    float hue = ofMap(time, 0, lifeTime, 128, 255);
    color.setHue(hue);
    ofSetColor(color);

    ofCircle(pos, size);
  }
}

void ofApp::setup() {
  ofSetFrameRate(60);

  // allocate drawing buffer
  int w = ofGetWidth();
  int h = ofGetHeight();

  fbo.allocate(w, h, GL_RGB32F_ARB);

  fbo.begin();
  ofBackground(255, 255, 255);
  fbo.end();

  param.setup();
  history = 0.99;

  time0 = ofGetElapsedTimef();
}

void ofApp::update() {
  float time = ofGetElapsedTimef();
  float dt = ofClamp(time - time0, 0, 0.1);
  time0 = time;

  if (!p.live) {
    p.setup();
  }

  p.update(dt);
}

void ofApp::draw(){
  ofBackground(255, 255, 255);

  fbo.begin();

  ofEnableAlphaBlending();

  float alpha = (1 - history) * 255;
  ofSetColor(255, 255, 255, alpha);
  ofFill();
  ofRect(0, 0, ofGetWidth(), ofGetHeight());

  ofDisableAlphaBlending();

  ofFill();
  p.draw();

  fbo.end();

  // draw buffer on screen
  ofSetColor(255, 255, 255);
  fbo.draw(0, 0);
}

void ofApp::keyPressed(int key){ }

void ofApp::keyReleased(int key){ }

void ofApp::mouseMoved(int x, int y ){ }

void ofApp::mouseDragged(int x, int y, int button){ }

void ofApp::mousePressed(int x, int y, int button){ }

void ofApp::mouseReleased(int x, int y, int button){ }

void ofApp::windowResized(int w, int h){ }

void ofApp::gotMessage(ofMessage msg){ }

void ofApp::dragEvent(ofDragInfo dragInfo){ }
