
#include "commonstuff.hpp"
#include "Alien.hpp"
#include "Bullet.hpp"
using namespace std;

Alien::Alien()
{
  cout << "soy un Alien" << endl;
  pos[X] = -SIZEX2;
  pos[Y] = RAND_FRAC()*(SIZEY) - SIZEY2;
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

//Podemos reciclar esta función haciendo que howmuch sea un valor random que cambie cad x segundos
//desde la lógica del main
void Alien::thrust(double howmuch)
{ 
  tspeed[X] += howmuch*sin(D2R*rot[Y]);
  tspeed[Y] += howmuch*cos(D2R*rot[Y]);
}


void Alien::draw()
{
    cout << "I'm Alien::draw" << endl;
  predraw();
  glutSolidCube(1.5);
  glTranslatef(0,-0.5,0);
  glutWireSphere(0.5,8,8);
  postdraw();
}
  

float Alien::getSize()
{
  return (SIZE_ASTEROID);
}


//Creo que hay que modificar esta función para que los aliens aparezcan solo por los bordes...
//pero aun no se me ha ocurrido como hacerlo bien, para que aparezca cuando no haya un asteroide
void Alien::resetpos()
{
  pos[X] = -SIZEX2;
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
