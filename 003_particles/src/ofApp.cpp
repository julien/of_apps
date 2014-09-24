#include "ofApp.h"

Params param;

void Params::setup() {
  eCenter = ofPoint(ofGetWidth()/ 2, ofGetHeight() / 2);
  eRad = 180;
  velRad = 0;
  lifeTime = 1.0;

  rotate = 90;
  force = 1000;
  spinning = 1500;
  friction = 0.5;
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

    ofPoint acc;
    ofPoint delta = pos - param.eCenter;
    float len = delta.length();

    if (ofInRange(len, 0, param.eRad)) {
      delta.normalize();

      acc += delta * param.force;

      acc.x += -delta.y * param.spinning;
      acc.y += delta.y * param.spinning;

    }

    vel += acc * dt;
    vel *= (1 - param.friction);

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
  history = 0.991;
  bornRate = 800;
  bornCount = 0;

  time0 = ofGetElapsedTimef();
}

void ofApp::update() {
  float time = ofGetElapsedTimef();
  float dt = ofClamp(time - time0, 0, 0.1);
  time0 = time;

  int i = 0;
  while (i  < p.size()) {
    if (!p[i].live) {
      p.erase(p.begin() + i);
    } else {
      i++;
    }
  }

  bornCount += dt * bornRate;
  if (bornCount >= 1) {
    int bornN = int(bornCount);
    bornCount -= bornN;

    for (int i = 0; i < bornN; i++) {
      Particle k;
      k.setup();
      p.push_back(k);
    }
  }

  for (i = 0; i < p.size(); i++) {
    p[i].update(dt);
  }
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

  for (int i = 0; i < p.size(); i++) {
    p[i].draw();
  }

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
