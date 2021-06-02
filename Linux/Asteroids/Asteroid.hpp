
#include "commonstuff.hpp"
#include "Shape.hpp"

#ifndef __ASTEROID_H__
#define __ASTEROID_H__

class Asteroid:public Shape {
 private:
  int size;
  int type;
 public:
  Asteroid* split();
  Asteroid(int = 0);
  Asteroid(int t, int s, float px, float py);
  void draw();
  float getSize();
  void reposition();
};

#endif
