//////////////////////////////////////
// Alien.cpp                     //
// Methods of the Alies class       //
//////////////////////////////////////

#include "commonstuff.hpp"
#include "Alien.hpp"
#include "Bullet.hpp"

extern time_t ref;

Alien::Alien()
{
  pos[X] = RAND_DOM(0, SIZEX);
  pos[Y] = RAND_DOM(0, SIZEY);
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = -90;
  rot[Y] = 0;

  rspeed[X] = 0;
  rspeed[Y] = 0;
  rspeed[Z] = 0;

  tspeed[X] = 0;
  tspeed[Y] = 0;
  tspeed[Z] = 0;

  color[R] = 0.2;
  color[G] = 0.4;
  color[B] = 0.3;

  status = DESTROYED;
}

void Alien::setStatus(bool estado)
{
  status = estado;
}

bool Alien::getStatus()
{
  return status;
}

void Alien::rotate(float rx, float ry, float rz)
{
  rot[X] += rx;  rot[Y] += ry;  rot[Z] += rz;
}

void Alien::run()
{ 
  if (time(NULL)-ref > 3){
    time(&ref);
    rot[Y] = RAND_FRAC()*360;
    tspeed[X] = ALIEN_SPEED*sin(D2R*rot[Y]);
    tspeed[Y] = ALIEN_SPEED*cos(D2R*rot[Y]);
  }
}

void Alien::setSize(int dim)
{
  tamano = dim;
}

void Alien::draw()
{
  predraw();
  glutSolidIcosahedron();
  postdraw();
  run();
}

float Alien::getSize()
{
  return (tamano*SIZE_UFO);
}

void Alien::reposition()
{
  pos[X] += 1+3*RAND_FRAC();
  pos[Y] += 1+3*RAND_FRAC();
}
