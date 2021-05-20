
#include "commonstuff.h"
#include "Shape.h"
#include "Bullet.h"

#ifndef __SHIP_H__
#define __SHIP_H__

class Ship: public Shape {
 private:
  int status;
 public:
  Ship();
  void draw();
  void rotate(float,float,float);
  Bullet* fire();
  void thrust(float);
  void hyperjump();
  float getSize();
  void resetpos();
};

#endif
