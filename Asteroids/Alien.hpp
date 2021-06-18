////////////////////////////////////////
// Alien.hpp                          //
// Class implementation for the Alien //
////////////////////////////////////////

#include "commonstuff.hpp"
#include "Shape.hpp"
#include "Bullet.hpp"

#ifndef _UFO_H_
#define _UFO_H_

class Alien: public Shape {
 private:
  bool status;
  int tamano;
 public:
  Alien();
  void setStatus(bool);
  bool getStatus();
  void draw();
  void rotate(float,float,float);
  Bullet* fire();
  void setSize(int);
  void run();
  float getSize();
  void resetpos();
};

#endif