//***********************
// Asteroids Open GL
// Claudio Rossi, Universidad Polit�cnica de Madrid 
// (C) 2015 
//***********************


#include "commonstuff.hpp"
#include "Shape.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Ship.hpp"
#include "ObjectsList.hpp"
#include "Flame.hpp"
using namespace std;


//***********************
// Prototipos de funciones 
//***********************

// Callback de la logica del juego
void myLogic();

//Callback de dibujo
void OnDibuja(void);	

//Callbacks para teclado y raton
void OnKeyboardDown(unsigned char key, int x, int y);
void OnMouseBtn(int button, int state,int x, int y);
void OnMouseMoveBtn(int x, int y);
void OnSpecKeyboardDown(int key, int x, int y);


void printdata();
void gameover(int score);

  
//***********************
// Variables globales
//***********************

// Posicion y step de la camara
float cam_pos[6]={0, 0, 27};

// posici�n de la explosi�n
float expl_pos[2]={-1000,-1000};

// Modo del Mouse
int MODE=NONE;

// Objetos globales

ObjectsList worldobjects;
// list<Shape*> worldobjects;
Ship *theShip=NULL;
Bullet *theBullet=NULL;
Flame *theFlame=NULL;

// Varias constantes usadas en el programa
int shotTime=0;
int nShips=3;
int score=0;
int FlameTime=0;
int FT=20;


//***********************
// Programa principal
//***********************


int main(int argc,char* argv[])
{

  // inicializaciones

  //Creacion y definicion de la ventana
  glutInit(&argc, argv);
  glutInitWindowSize(WINX,WINY);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Asteroids GL");

  //Habilita las luces, la renderizacion y el color de los materiales
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);    
	
  //Define la proyeccion
  glMatrixMode(GL_PROJECTION);
  gluPerspective( 40.0, WINX/WINY, 0.1, 50);

  //Para definir el punto de vista
  glMatrixMode(GL_MODELVIEW);	

  // Define call backs te GLUT

  // Display function: contiene las instrucciones de dibujo
  glutDisplayFunc(OnDibuja);
    // Idle function: contiene la logica del juego
  glutIdleFunc(myLogic);
  
  // Callbacks de teclado y rat�n
  glutKeyboardFunc(OnKeyboardDown);
  glutSpecialFunc(OnSpecKeyboardDown);
  glutMotionFunc(OnMouseMoveBtn);
  glutMouseFunc(OnMouseBtn);

  
  // Posicciona el punto de vista (c�mara)
  gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],  // posicion del  ojo  
	    0.0, 0.0, 0.0,		        // hacia que punto mira  
	    0.0, 1.0, 0.0);         // vector "UP"  (vertical positivo)


  // Creacci�n de los objetos iniciales
  theShip = worldobjects.getShip();
  // ObjectsList es declarada est�tica, se inicializa "automaticamente" - contiene los asteroides
  
  // bucle infinito de Open GL
  glutMainLoop();

  // Esto solo sirve para que el compilador no proteste, nunca se llegar� aqu�
  return 0;   

}

/************************** FIN DEL MAIN ************************************/


//***********************
// Callbacks
//***********************


// Imprime puntuacci�n y num. de naves
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


//no usada
void gameover(int score)
{
  int i,l;
  char buffer[30];
  
  glPushMatrix();

    sprintf(buffer,"GAME OVER! Points: %d",score);

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


// Logica del juego: mueve los objeto mandando el mensaje "move"
void myLogic()
{

  int res;

  // borra el proyectil despues de cierto tiempo si no ha dado con nada
  if(shotTime++ > MAXSHOTTIME)
    {
      worldobjects.remove(theBullet);    
      theBullet = NULL;
      shotTime = 0;
    }

  // Pide al mundo que mueve los objetos
  worldobjects.move();

  // Pide si ha habido colision, pasa referencia a proyectil y nave, retorna tipo de colision y posicion de la colision
  // res==0:  No ha colision
  // res==1:  Asteroide/Nave
  // res>=2:  Asteroide/Proyectil, depende del tipo de asteroide (grande/mediano/pequeno)
  res = worldobjects.collisions(theBullet, theShip, expl_pos);  

  // Explosion
  if(res > 0 || FlameTime > 0)
    {
      FlameTime++;
      if(!theFlame)
        {
          theFlame = new Flame(expl_pos);
          worldobjects.add(theFlame);
        }else
	        if(FlameTime > FT)
	        {
	            worldobjects.remove(theFlame);
	            theFlame = NULL;
	            FlameTime = 0;
	        }
    }
  
  if(res == 1)    
    {
      nShips--;
      
      // Esto habria que mejorarlo...
      if(nShips == 0) exit(1);
      theShip -> resetpos();
      worldobjects.reposition(theShip);
    }

  if(res >= 2)    
    {
      theBullet = NULL;
      shotTime = 0;
      score += 100*(res - 1);
    }

}
 
/**************************************************************/ 

void OnDibuja(void)
{ 
  //Borrado de la pantalla	
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Manda el mensaje "draw" al mundo
  worldobjects.draw();    
  // imprime datos
  printdata();
 
  //Al final, cambiar el buffer
  glutSwapBuffers();
  glutPostRedisplay();//se le indica que redibuje la pantalla
  /**************************************************************/}



void OnKeyboardDown(unsigned char key, int x, int y)
{ 
  int mod;

  mod=glutGetModifiers();

  switch(key)
    {
    case 'q':
    case ESC:
      exit(1);
    case ' ':
    // Si no hay proyectil, lo crea
        if(!theBullet)
	    {
	        theBullet=theShip->fire(); 
	        worldobjects.add(theBullet);
	    }
        break;
    case '-': theShip->thrust(SHIPSPEED); break;  // accelara
    case ',': theShip->hyperjump(); break;  // hyper jump (mueve la nave a una posici�n random
    }		
}

void OnSpecKeyboardDown(int key, int x, int y)
{ 
  switch(key)
    {
    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_LEFT: theShip->rotate(0,-5,0);
      break;
    case GLUT_KEY_RIGHT: theShip->rotate(0,5,0);
      break;
    case GLUT_KEY_PAGE_DOWN:
      break;
    case GLUT_KEY_PAGE_UP:
      break;
    }		
}

// No usada
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
    printf("MOUSE!\n");
}

// No usada
void  OnMouseMoveBtn  (int x, int y)
{

  //  printf("MOUSE MOVES!\n");
    
  if(MODE==TRANS)
    {
     
    }
  else
    {
     
    }
}
