
#include "commonstuff.hpp"
#include "Bullet.hpp"

Bullet::Bullet(float px, float py, float vx, float vy)
{
  pos[X] = px;
  pos[Y] = py;
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = 0;
  rot[Y] = 0;

  rspeed[X] = 0;
  rspeed[Y] = 0;
  rspeed[Z] = 0;

  tspeed[X] = vx;
  tspeed[Y] = vy;
  tspeed[Z] = 0;

  color[R] = 0.9;
  color[G] = 0.9;
  color[B] = 0.9;
}

void Bullet::draw()
{
  predraw();
  glutSolidSphere(0.1,5,5);	
  postdraw();
}


float Bullet::getSize()
{
  return (SIZE_BULLET); // Change on commonstuff.hpp
}
