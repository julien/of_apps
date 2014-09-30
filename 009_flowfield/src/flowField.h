#pragma once

#include "ofMain.h"

class FlowField {

public:
  vector<vector<ofVec2f>> field;
  int cols;
  int rows;
  int resolution;

  FlowField() {
    resolution = 10;
    cols = ofGetWidth() / resolution;
    rows = ofGetHeight() / resolution;

    for (int i = 0; i < cols; ++i) {
      field.at(i).resize(rows);
    }
    init();
  }

  void init() {

  }

};
