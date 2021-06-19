/////////////////////////////////////
// Angel.cpp                    //
// Methods of the Angel class      //
/////////////////////////////////////

#include "commonstuff.hpp"
#include "Angel.hpp"

extern time_t ref;

Angel::Angel()
 {
  pos[X] = 0;
  pos[Y] = 0;
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
  color[B] = 0.0;

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

void Angel::draw()
{
    predraw();
    glutSolidTeapot(tamano*SIZE_ANGEL);
    postdraw();
}
void Angel::teleport()
{
  if (time(NULL)-ref > 10)
  {
    time(&ref);
    rot[Y] = RAND_FRAC()*360;
    pos[X] = RAND_DOM(0, WINX);
    pos[Y] = RAND_DOM(0, WINY);
  }
}
