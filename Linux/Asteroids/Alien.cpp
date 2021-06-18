
#include "commonstuff.hpp"
#include "Alien.hpp"
#include "Bullet.hpp"
using namespace std;

extern time_t ref;

Alien::Alien()
{
  cout << "soy un Alien" << endl;
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

  color[R] = 0.2;
  color[G] = 0.4;
  color[B] = 0.3;

  status = DESTROYED;
}

void Alien::setStatus(bool estado)
{
  status = estado;
}

bool Alien::getStatus ()
{
  return status;
}

void Alien::rotate(float rx, float ry, float rz)
{
  rot[X] += rx;  rot[Y] += ry;  rot[Z] += rz;
}

Bullet* Alien::fire()
{
  Bullet *tmp;
  float direction = RAND_FRAC()*360;
  tmp = new Bullet(pos[X],pos[Y],BULLETSPEED*sin(D2R*direction),BULLETSPEED*cos(D2R*direction));

  return tmp;
}


void Alien::run()
{ 
  //Cambia aleatoriamente de dirección cada 3 segundos
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
  cout << "I'm Alien::draw" << endl;
  predraw();
  glutSolidCube(tamano*SIZE_UFO);
  // glTranslatef(0,-0.5,0);
  // glutWireSphere(0.5,8,8);
  postdraw();
  run();
  fire();
}
  

float Alien::getSize()
{
  return (tamano*SIZE_UFO);
}


//Creo que hay que modificar esta función para que los aliens aparezcan solo por los bordes...
//pero aun no se me ha ocurrido como hacerlo bien, para que aparezca cuando no haya un asteroide
void Alien::resetpos()
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

  color[R] = 0.2;
  color[G] = 0.4;
  color[B] = 0.3;
}
