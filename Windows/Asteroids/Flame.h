
#include "commonstuff.h"
#include "Shape.h"
#include "Bullet.h"

#ifndef __FLAME_H__
#define __FLAME_H__

class Flame: public Shape {
 private:
  int size;
  int dir;
 public:
  Flame(float *p);
  void draw();
  float getSize();
};

#endif
