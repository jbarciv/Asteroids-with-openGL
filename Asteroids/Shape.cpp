///////////////////////////////////////////////////
// Shape.cpp                                     //
// Methods of the Shape class (pure virtual)     //
///////////////////////////////////////////////////

#include "Shape.hpp"

Shape::Shape()
{
  mynumber = RAND_DOM(0,1000000);
  // TBD: check mynumber is not repeated
}

void  Shape::getPos(float *p)
{
  p[X] = pos[X];
  p[Y] = pos[Y];
  p[Z] = pos[Z];
}

int Shape::getNo()
{
  return mynumber;
}

void Shape::predraw()
{
  glPushMatrix();
  glTranslatef(pos[X],pos[Y],pos[Z]);
  glRotatef(rot[X],1,0,0);
  glRotatef(rot[Y],0,1,0);
  glRotatef(rot[Z],0,0,1);

  glColor3f(color[R],color[G],color[B]);
}

void Shape::postdraw()
{
  glPopMatrix();
}

void Shape::move()
{
  int crash=0;

  //  crash = detect_collision(others);

  if(!crash)
    {
      pos[X] += tspeed[X];
      pos[Y] += tspeed[Y];
      pos[Z] += tspeed[Z];
      rot[X] += rspeed[X];
      rot[Y] += rspeed[Y];
      rot[Z] += rspeed[Z];
      
      // check world boundaries
      if(pos[X]<-SIZEX2) pos[X] = SIZEX2;
      if(pos[Y]<-SIZEY2) pos[Y] = SIZEY2;
      if(pos[Z]<-SIZEZ2) pos[Z] = SIZEZ2;

      if(pos[X]>SIZEX2) pos[X] = -SIZEX2;
      if(pos[Y]>SIZEX2) pos[Y] = -SIZEX2;
      if(pos[Z]>SIZEX2) pos[Z] = -SIZEX2;

      if(rot[X]>360) rot[X] -= 360;
      if(rot[Y]>360) rot[Y] -= 360;
      if(rot[Z]>360) rot[Z] -= 360;

      if(rot[X]<0) rot[X] += 360;
      if(rot[Y]<0) rot[Y] += 360;
      if(rot[Z]<0) rot[Z] += 360;
	
    }
}
