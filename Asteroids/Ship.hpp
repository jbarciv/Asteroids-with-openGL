///////////////////////////////////////
// Ship.hpp                          //
// Class implementation for the Ship //
///////////////////////////////////////
#include "commonstuff.hpp"
#include "Shape.hpp"
#include "Bullet.hpp"

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
  void thrust(double);
  void hyperjump();
  float getSize();
  void resetpos();
};

#endif
