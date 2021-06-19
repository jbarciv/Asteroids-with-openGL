//////////////////////////////////////
// Flame.cpp                        //
// Methods of the Flame class       //
//////////////////////////////////////

#include "commonstuff.hpp"
#include "Flame.hpp" 

Flame::Flame(float *p)
{
  pos[X] = p[X];
  pos[Y] = p[Y];
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = 0;
  rot[Y] = 0;

  rspeed[X] = 0;
  rspeed[Y] = 0;
  rspeed[Z] = 0;

  tspeed[X] = 0;
  tspeed[Y] = 0;
  tspeed[Z] = 0;

  color[R] = 0.1;
  color[G] = 0.8;
  color[B] = 0.0;

  size = 1;
  dir = 1;
}

void Flame::draw()
{
  size += dir;
  if (size > 5) dir = -1;
  if (size < 1) dir = 1;
  
  predraw();
  glutSolidTorus(0.1*size,0.25*size,20,20);	
  postdraw();
} 

float Flame::getSize()
{
  return (0.25);
}

