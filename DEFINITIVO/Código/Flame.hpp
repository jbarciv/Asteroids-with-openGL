////////////////////////////////////////
// Flame.hpp                          //
// Class implementation for the Flame //
////////////////////////////////////////

#include "commonstuff.hpp"
#include "Shape.hpp"
#include "Bullet.hpp"

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
