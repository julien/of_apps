#pragma once

#include "ofMain.h"
#include "mover.h"

class ofApp : public ofBaseApp {

public:
  double spring;
  vector<Mover*> movers;
  int numMovers;
  int maxMovers;
  int factor;
  float startTime;

  void addMovers(int num);
  void checkCollision(Mover *a, Mover *b);

  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

};
