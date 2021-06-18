
#include "Angel.hpp"

extern time_t ref;

Angel::Angel()
 {
  pos[X] = 0;
  pos[Y] = 0;
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

  color[R] = 255; 
  color[G] = 150;
  color[B] = 150;

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
      //Cambia aleatoriamente de posicion cada 10 segundos
  if (time(NULL)-ref > 10){
    time(&ref);
    rot[Y] = RAND_FRAC()*360;
    pos[X] = RAND_DOM(0, WINX);
    pos[Y] = RAND_DOM(0, WINY);
}
}