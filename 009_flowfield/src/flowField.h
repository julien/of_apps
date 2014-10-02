#pragma once

#include "ofMain.h"

class FlowField {

  vector<vector<ofVec2f> > field;
  int cols;
  int rows;
  int resolution;

public:

  void setup(int r = 10) {
    resolution = r;
    cols = ofGetWidth() / resolution;
    rows = ofGetHeight() / resolution;

    field.resize(cols);
    for (int i = 0; i < cols; ++i) {
      field.at(i).resize(rows);
    }
    init();
  }

  void init() {
    float xoffSeed = ofRandom(0, 1);
    float yoffSeed = ofRandom(0, 1);
    float xoff = xoffSeed;

    for (int i = 0; i < cols; ++i) {
      float yoff = yoffSeed;

      for (int j = 0; j < rows; ++j) {
        float theta = ofMap(ofNoise(xoff, yoff), 0, 1, 0, TWO_PI);

        field[i][j].set(cos(theta), sin(theta));
        yoff += 0.03;
      }
      xoff += 0.03;
    }

  }

  void draw() {
    for (int i = 0; i < cols; ++i) {
      for (int j = 0; j < rows; ++j) {
        drawVector(field[i][j], i * resolution, j * resolution, resolution - 2);
      }
    }
  }

  void drawVector(const ofVec2f &v, float x, float y, float scale) {
    ofPushMatrix();

    float arrowsize = 4;

    ofTranslate(x, y);
    // get direction
    ofRotate(ofVec2f(1, 0).angle(v));
    // get length and scale
    float len = v.length() * scale;

    ofEnableAlphaBlending();
    ofSetColor(255, 255, 0, 100);

    ofLine(0, 0, len, 0);
    ofLine(len, 0, len - arrowsize, +arrowsize / 2);
    ofLine(len, 0, len - arrowsize, -arrowsize / 2);

    ofDisableAlphaBlending();
    ofPopMatrix();
  }

  ofVec2f lookup(const ofVec2f &target) {
    int col = int(ofClamp(target.x / resolution, 0, cols - 1));
    int row = int(ofClamp(target.y / resolution, 0, rows - 1));
    return field[col][row];
  }
};
