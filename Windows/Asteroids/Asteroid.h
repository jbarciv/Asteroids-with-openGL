
#include "commonstuff.h"
#include "Shape.h"

#ifndef __ASTEROID_H__
#define __ASTEROID_H__

class Asteroid:public Shape {
 private:
  int size;
  int type;
 public:
  Asteroid *split();
  Asteroid(int);
  Asteroid(int t, int s, float px, float py);
  void draw();
  float getSize();
  void reposition();
};

#endif
