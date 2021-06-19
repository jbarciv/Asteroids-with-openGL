//////////////////////////////////////////////////////////////////////
// mainAsteroids.cpp                                                //
//                                                                  //
// Based on Claudio Rossi implementation, Technical University of   //
//                      Madrid (C) 2015                             //
//                                                                  //
//      ---> Programming an Asteroids Game with Open GL <---        //
//                                                                  //
//                                                                  //
// History:                                                         //
// 2021.05.15                                                       //
// The main.cpp and most of the classes are given by                //
// the author.                                                      //
// 2021.05.25                                                       //
// Josep Barbera - ObjectList class implemented                     //
// 2021.05.30                                                       //
// Gonzalo Quiros - Alien class implemented                         //
// 2021.06.16                                                       //
// Celia Ramos - Angel class implemented                            //
// 2021.06.18                                                       //
// Celia Ramos, Gonzalo Quiros, Josep Barbera - last version        //
//////////////////////////////////////////////////////////////////////

#include "commonstuff.hpp"
#include "ObjectsList.hpp"
#include <time.h>
using namespace std;

///////////////////////////////////////
///////// Function Prototype //////////
///////////////////////////////////////

// Callback of the game logic
void myLogic();

//Callback of draw
void OnDraw(void);	

//Callbacks para teclado y raton
void OnKeyboardDown(unsigned char key, int x, int y);
void OnMouseBtn(int button, int state,int x, int y);
void OnMouseMoveBtn(int x, int y);
void OnSpecKeyboardDown(int key, int x, int y);

void printdata();
void gameover(int score);

///////////////////////////////////////
//////// Global variables /////////////
///////////////////////////////////////

// Position and step of the camara
float cam_pos[6]={0, 0, 27};

// explotion location
float expl_pos[2]={-1000,-1000};

// Mouse mode
int MODE=NONE;

// Global Objects
ObjectsList worldobjects;
Ship *theShip=NULL;
Bullet *theBullet=NULL;
Flame *theFlame=NULL;
Alien *theUFO=NULL;
Angel *theAngel=NULL;

// Very used constants
int shotTime=0;
int nShips=20;
int score=0;
int FlameTime=0;
int FT=20;
time_t timeUFO;
time_t timeAngel = 0;;
time_t ref = 0;

///////////////////////////////////////
//////////// Main program /////////////
///////////////////////////////////////

int main(int argc,char* argv[])
{

  // Initializations
  time(&timeUFO);
  time(&timeAngel);

  // Creation and definition of the window
  glutInit(&argc, argv);
  glutInitWindowSize(WINX,WINY);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Asteroids");

  // Enables lights, rendering, and color of materials
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);    
	
  // Define the projection
  glMatrixMode(GL_PROJECTION);
  gluPerspective( 40.0, WINX/WINY, 0.1, 50);

  // To define the viewpoint
  glMatrixMode(GL_MODELVIEW);	

  // Define call backs of GLUT

  // Display function: contains the draw instrucctions
  glutDisplayFunc(OnDraw);
  // Idle function: contains the game logic
  glutIdleFunc(myLogic);
  
  // Mouse and keyboard Callbacks  
  glutKeyboardFunc(OnKeyboardDown);
  glutSpecialFunc(OnSpecKeyboardDown);
  glutMotionFunc(OnMouseMoveBtn);
  glutMouseFunc(OnMouseBtn);

  
  // Position the viewpoint (camera)
  gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],  // eye position  
	    0.0, 0.0, 0.0,		                   // towards what point it looks  
	    0.0, 1.0, 0.0);                        // "UP" vector (positive vertical)


  // Initial objects creation
  theShip = worldobjects.getShip();
  theUFO = worldobjects.getUFO();
  theAngel = worldobjects.getAngel();

  // ObjectsList is statically declared, it is automatically initialized - it has the asteroides
  
  // infinite loog of Open GL
  glutMainLoop();

  // This is only for the compiler, it will never get here
  return 0;   
}

/************************** END OF MAIN ************************************/

///////////////////////////////////////
///////////// Callbacks ///////////////
///////////////////////////////////////

// Puntuation and the number of Ships are printed
void printdata()
{

  int i,l;
  char buffer[50];
  
  glPushMatrix();

  sprintf(buffer,"Ships: %d       Score: %d",nShips,score);
  l=strlen(buffer); 

  glDisable(GL_LIGHTING);
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos3f(-9, 9,-0.1);
  for( i=0; i < l; i++) 
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]); // Print a character on the screen
  }
  glEnable(GL_LIGHTING);

  glPopMatrix();
}

void gameover(int score)
{
  int i,l;
  char buffer[30];
  
  glPushMatrix();

  sprintf(buffer,"GAME OVER! Points: %d",score);

  l = strlen(buffer); 

  glDisable(GL_LIGHTING);
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos3f(-9, 9,-0.1);
  for( i = 0; i < l; i++) 
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]); // Print a character on the screen
  }
  glEnable(GL_LIGHTING);
  glPopMatrix();
}

// Game logic: it moves the objects sending the "move" message
void myLogic()
{
  int dim;
  int res;

  // The bullet is erased after a certain time if it has not found anything
  if(shotTime++ > MAXSHOTTIME)
  {
    worldobjects.removes(theBullet);    
    theBullet = NULL;
    shotTime = 0;
  }
  if (time(NULL)-timeUFO > 20 && theUFO -> getStatus() == DESTROYED)
  {
    dim = (int)(RAND_FRAC()*2.99 + 1);
    theUFO ->setSize(dim);
    worldobjects.add(theUFO);
    theUFO -> setStatus(ACTIVE);
  }

  if (time(NULL)-timeAngel > 40 && theAngel -> getStatus() == INACTIVE)
  {
    theAngel -> resetpos();
    dim = (int)(RAND_FRAC()*2.99 + 1);
    theAngel ->setSize(dim);
    worldobjects.add(theAngel);
    theAngel -> setStatus(ACTIVE);
  }

  // It asks the world to move the objects
  worldobjects.move();

  // It asks if there has been a collision, passing the reference to the Bullet and the Ship, 
  // returning the kind and the location of that (suppossed) collision.
  // res == 0:  There is not collision
  // res == 1:  Asteroid/Ship
  // res >= 2 && res <= 4:  Asteroid/Bullet, it depends on the Asteroids size (big/medium/small)
  // res == 5: UFO/Ship
  // res == 6: Angel/Ship
  // res == 7: UFO/Bullet
  // res == 8: Angel/Bullet

  res = worldobjects.collisions(theBullet, theShip, theUFO, theAngel, expl_pos);  
  
  // First the explosion is checked
  if(res > 0 && res != 6 || FlameTime > 0) // There is not explosion with the Angel/Ship collision
  {
    FlameTime++;
    if(!theFlame)
    {
      theFlame = new Flame(expl_pos);
      worldobjects.add(theFlame);
    } else if(FlameTime > FT)
      {
        worldobjects.removes(theFlame);
        theFlame = NULL;
        FlameTime = 0;
      }
  }

  if(res == 1)  // res == 1:  Asteroid/Ship
    {
      nShips--;
      if(nShips == 0) exit(1); // The Game ends
      theShip -> resetpos();
      worldobjects.reposition(theShip, theUFO, theAngel);
    }                                  

  if(res >= 2 && res <= 4)    
    {
      theBullet = NULL;
      shotTime = 0;
      score += 100*(res - 1);
    }
  
  if (res == 5) // res == 5: UFO/Ship
    {
      nShips--;
      if (nShips == 0) exit(1);// The Game ends
      theUFO -> setStatus(DESTROYED);
      timeUFO = time(NULL);
      dim = theUFO ->getSize();
      score -= dim*100;
    }
  
  if (res == 6) // res == 6: Angel/Ship
  {
    nShips++; // We receive a extra life
    theAngel -> setStatus(INACTIVE);
    timeAngel = time(NULL);
  }
  
  if (res == 7) // res == 7: UFO/Bullet
  {
    theUFO -> setStatus(DESTROYED);
    timeUFO = time(NULL);
    dim = theUFO ->getSize();
    score += dim*100;
  }

  if (res == 8) //res == 8: Angel/Bullet
  {
    theAngel -> setStatus(DESTROYED);
    timeAngel = time(NULL);
    dim = theAngel->getSize();
    score -= dim*10;
  }
}

void OnDraw(void)
{ 
  // Clearing the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Send the message "draw" to the world
  worldobjects.draw();    
  // Prints the data
  printdata();
  // At the end, changes the buffer
  glutSwapBuffers();
  // It redraws the window
  glutPostRedisplay();
}

void OnKeyboardDown(unsigned char key, int x, int y)
{ 
  int mod;

  mod = glutGetModifiers();

  switch(key)
    {
    case 'q':
    case ESC: exit(1);
    case ' ':
        if(!theBullet)                   // If there is not a bullet it is created
	    {
	        theBullet=theShip->fire(); 
	        worldobjects.add(theBullet);
	    }
        break;
    case '-': theShip->thrust(SHIPSPEED);// Accelerates 
        break;  
    case ',': theShip->hyperjump();      // That is the Hyper Jump (moves the Ship to a random position) 
        break;
    }		
}

void OnSpecKeyboardDown(int key, int x, int y)
{ 
  switch(key)
    {
    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_UP: theShip->thrust(SHIPSPEED);
      break;
    case GLUT_KEY_LEFT: theShip->rotate(0,-20,0);
      break;
    case GLUT_KEY_RIGHT: theShip->rotate(0,20,0);
      break;
    case GLUT_KEY_PAGE_DOWN:
      break;
    case GLUT_KEY_PAGE_UP:
      break;
    }		
}

// It is not used
void OnMouseBtn(int button, int state,int x, int y)
{
  if(state==GLUT_DOWN)
    if(button==GLUT_LEFT_BUTTON)
      MODE=TRANS;
    else
      if(button==GLUT_RIGHT_BUTTON)
        MODE=ROT;
      else
        MODE=NONE;
}

// It is not used
void  OnMouseMoveBtn  (int x, int y)
{
  if(MODE==TRANS){ }
  else{ }
}
