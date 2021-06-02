
#include "commonstuff.hpp"
#include "Shape.hpp"
#include "Bullet.hpp"

#ifndef __OVNI__
#define __OVNI__

class Ovni: public Shape {
 private:
  int status;
 public:
  Ovni();
  void draw();
  void rotate(float,float,float);
  Bullet* fire();
  void thrust(double);
  float getSize();
  void resetpos();
};

#endif
