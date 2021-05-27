
#include "commonstuff.hpp"
#include "Asteroid.hpp"
using namespace std;

Asteroid::Asteroid(int t)
{
  float tmp;

  size = BIG;
  type = t;

  pos[X] = RAND_DOM(0,SIZEX);
  pos[Y] = RAND_DOM(0,SIZEY);
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = 0;
  rot[Y] = 0;

  rspeed[X] = RAND_FRAC()*0.5;
  rspeed[Y] = RAND_FRAC()*0.5;
  rspeed[Z] = RAND_FRAC()*0.5;

  tmp = RAND_FRAC();
  tspeed[X] = tmp*ASTEROID_SPEED;
  tspeed[Y] = (1-tmp)*ASTEROID_SPEED;
  tspeed[Z] = 0;

  color[R] = 0.9;
  color[G] = 0.2;
  color[B] = 0.1;

  //  printf("Mi no is %d",mynumber);
}


Asteroid::Asteroid(int t, int s, float px, float py)
{
  float tmp;

  size = s;
  type = t;

  pos[X] = px;
  pos[Y] = py;
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = 0;
  rot[Y] = 0;

  rspeed[X] = RAND_FRAC()*0.5;
  rspeed[Y] = RAND_FRAC()*0.5;
  rspeed[Z] = RAND_FRAC()*0.5;

  tmp = RAND_FRAC();
  tspeed[X] = tmp*ASTEROID_SPEED;
  tspeed[Y] = (1-tmp)*ASTEROID_SPEED;
  tspeed[Z] = 0;

  color[R] = 0.9;
  color[G] = 0.2;
  color[B] = 0.1;
}


void Asteroid::draw()
{
    cout << "I'm asteroid::draw" << endl;
  predraw();
  glutSolidSphere(size*0.3,9,8);
  glTranslatef(0,size*0.3,0);	
  glutSolidSphere(size*0.25,7,9);
  //glutSolidCube(size*0.3);	
  /*
  //  glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE ) ;
  glBegin(GL_POLYGON);
  if(type==1)
    {
      glVertex3f(0,0,0);
      glVertex3f(size*0.3,size*0.4,0.1);
      glVertex3f(size*0.5,0,0);
      glVertex3f(size*0.2,size*0.4,0);
      glVertex3f(size*0.5,size*0.7,0.2);
      glVertex3f(size*0.5,size*0.4,0);
      glVertex3f(0,size*0.5,0);
    }
  else 
    if(type==2)
      {
	glVertex3f(0,0,0);
	glVertex3f(size*0.3,size*0.4,0);
	glVertex3f(size*0.5,0,0);
	glVertex3f(size*0.3,size*0.4,0.1);
	glVertex3f(size*0.5,size*0.7,0);
	glVertex3f(size*0.4,size*0.4,-0.1);
	glVertex3f(0,size*0.6,0);
      }
  else 
    if(type==3)
      {
	glVertex3f(0,0,0.1);
	glVertex3f(size*0.2,size*0.4,0);
	glVertex3f(size*0.5,0,0.2);
	glVertex3f(size*0.6,size*0.4,0);
	glVertex3f(size*0.5,size*0.6,0);
	glVertex3f(size*0.5,size*0.4,0);
	glVertex3f(0,size*0.3,0.3);
      }
  
  glEnd();
  */	 

  
  postdraw();
}
 

Asteroid *Asteroid::split()
{
  Asteroid *tmp;

  tmp = new Asteroid(1,size-1,pos[X],pos[Y]);
  size--;

  return tmp;
}
 
float Asteroid::getSize()
{
  return (0.3*size);
}

void Asteroid::reposition()
{
  pos[X] += 1+3*RAND_FRAC();
  pos[Y] += 1+3*RAND_FRAC();

}
