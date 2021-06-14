#include "commonstuff.hpp"
#include "Shape.hpp"
#include "Bullet.hpp"

#ifndef _UFO_H_
#define _UFO_H_

class Alien: public Shape {
 private:
  int status;
 public:
  Alien();
  void draw();
  void rotate(float,float,float);
  Bullet* fire();
  void move();
  float getSize();
  void resetpos();
};

#endif