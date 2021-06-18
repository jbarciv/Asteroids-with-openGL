
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
void Angel::move()
{
      //Cambia aleatoriamente de dirección cada 4 segundos
  if (time(NULL)-ref > 4){
    time(&ref);
    rot[Y] = RAND_FRAC()*360;
    tspeed[X] = ANGEL_SPEED*sin(D2R*rot[Y]);
    tspeed[Y] = ANGEL_SPEED*cos(D2R*rot[Y]);
    }
}
