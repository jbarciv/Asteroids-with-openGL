/////////////////////////////////////
// Angel.cpp                    //
// Methods of the Angel class      //
/////////////////////////////////////

#include "commonstuff.hpp"
#include "Angel.hpp"

Angel::Angel()
 {
  pos[X] = RAND_DOM(0,SIZEX);
  pos[Y] = RAND_DOM(0,SIZEY);
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

  color[R] = 1; 
  color[G] = 0.0;
  color[B] = 1;

  status = INACTIVE;
}

void Angel::setStatus(bool estado)
{
  status = estado;
}

bool Angel::getStatus ()
{
  return status;
}

void Angel::setSize(int dim)
{
  tamano = dim;
}

float Angel::getSize()
{
    return (tamano*SIZE_ANGEL);
}

void Angel::teleport()
{
    rot[Y] = RAND_FRAC()*360;
    pos[X] = RAND_DOM(0, WINX-10);
    pos[Y] = RAND_DOM(0, WINY-10);
}

void Angel::draw()
{
    predraw();
    glutSolidTeapot(tamano*SIZE_ANGEL);
    postdraw();
}

void Angel::reposition()
{
  pos[X] += 1+3*RAND_FRAC();
  pos[Y] += 1+3*RAND_FRAC();

}
