
#include "commonstuff.hpp"
#include "Ovni.hpp"
#include "Bullet.hpp"
using namespace std;

Ovni::Ovni()
{
  cout << "soy un Ovni" << endl;
  pos[X] = 0;
  pos[Y] = 0;
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = -90;
  rot[Y] = 0;

  rspeed[X] = 0.0;
  rspeed[Y] = 0.0;
  rspeed[Z] = 0.0;

  tspeed[X] = 0.0;
  tspeed[Y] = 0.0;
  tspeed[Z] = 0.0;

  color[R] = 0.2;
  color[G] = 0.4;
  color[B] = 0.3;
}

void Ovni::rotate(float rx, float ry, float rz)
{
  rot[X] += rx;  rot[Y] += ry;  rot[Z] += rz;
}

 Bullet* Ovni::fire()
 {
   Bullet *tmp;

   tmp = new Bullet(pos[X],pos[Y],BULLETSPEED*sin(D2R*rot[Y]),BULLETSPEED*cos(D2R*rot[Y]));

   return tmp;
 }

 void Ovni::thrust(double howmuch)
 { 
   tspeed[X] += howmuch*sin(D2R*rot[Y]);
   tspeed[Y] += howmuch*cos(D2R*rot[Y]);
}

void Ovni::draw()
{
    cout << "I'm Ovni::draw" << endl;
  predraw();
  glutSolidTetrahedron();
  postdraw();
}
  

float Ovni::getSize()
{
  return (SIZE_ASTEROID); // cambiar por size ovni
}

void Ovni::resetpos()
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
