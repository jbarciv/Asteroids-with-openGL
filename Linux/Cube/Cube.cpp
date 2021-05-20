
/* ----------------------------------------------------------------------------
 *       --> Drawing a CUBE with OpenGL <--
 * It is a first getting in touch example with OpenGL
 * Provided by: Claudio Rossi, Technical University of Madrid (UPM)
 * Translated/adapted by: Josep Maria Barbera
 * -------------------------------------------------------------------------- */

#ifdef linux
#include <GL/glut.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <stdlib.h>
#endif
#ifdef _WIN32
#include <windows.h>
#include "glut.h"
#endif

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ESC 27
#define WINX 1024   // Windows dimensions
#define WINY 800
using namespace std;

// Functions prototype 
void myLogic();
void DrawCube();

//Callback for mouse and keyboard
void OnKeyboardDown(unsigned char key, int x, int y);
void OnSpecKeyboardDown(int key, int x, int y);

//Callbacks of draw
void OnDraw(void);	

// Position and step of the camera
float cam_pos[6]={0, 0, 27};

float rot=0;
float vel=0.25;

/**************************************************************/
int main(int argc,char* argv[]){

    // Initializations

    // Window creation and definition
    glutInit(&argc, argv);
    glutInitWindowSize(WINX,WINY);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Asteroids GL"); // Window's name

    // Enable lights, rendering, and color of materials
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);


    //define the projection
    glMatrixMode(GL_PROJECTION);
    gluPerspective( 40.0, WINX/WINY, 0.1, 50);


    // define call backs to GLUT
    glutDisplayFunc(OnDraw);
    glutIdleFunc(myLogic);

    glutKeyboardFunc(OnKeyboardDown);
    glutSpecialFunc(OnSpecKeyboardDown);
    
    
    //To define the viewpoint
    glMatrixMode(GL_MODELVIEW);	
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);    
    
    
    // posicciona the viewpoint
    gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],  // posicion del  ojo  
    	    0.0, 0.0, 0.0,		        // hacia que punto mira  
    	    0.0, 1.0, 0.0);         // vector "UP"  (vertical positivo)


    // program loop
    glutMainLoop();
    
    return 0;   
}
/**************************************************************/

void myLogic(){
    rot += vel;

    if(rot>360) rot=0;
}
 
/**************************************************************/
void OnDraw(void){ 
    //Clearing the screen	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DrawCube();

    // posicciona the viewpoint
    glLoadIdentity();
    gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],  // posicion del  ojo  
    	    0.0, 0.0, 0.0,		        // hacia que punto mira  
    	    0.0, 1.0, 0.0);             // vector "UP"  (vertical positivo)


    //At the end, change the buffer
    glutSwapBuffers();
    glutPostRedisplay();//prompted to redraw the screen
}
/**************************************************************/

void OnKeyboardDown(unsigned char key, int x, int y){ 
    int mod;
    mod=glutGetModifiers();

    switch(key){
        case 'q':
        case ESC:
            exit(1);
        case ' ':
            if(vel>0)
    	        vel=0;
            else
    	        vel=0.25;	
            break;
        case '-':  break;
        case ',': break;
        case 'w': break;
        case 'z': break;
        case 'a': break;
        case 's': break;
        case '>': break;
        case '<': break;
    }		
}

void OnSpecKeyboardDown(int key, int x, int y){ 
    switch(key){
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_LEFT:  
            break;
        case GLUT_KEY_RIGHT: 
            break;
        case GLUT_KEY_PAGE_DOWN:
            break;
        case GLUT_KEY_PAGE_UP:
            break;
    }		
}

void DrawCube(void){
  glPushMatrix();
  glTranslatef(0,1,0);
  glRotatef(rot,1,0,0);
  glRotatef(rot,0,1,0);
  glRotatef(0,0,0,1);
  glColor3f(0,1,0);
  glutSolidCube(3);
  glPopMatrix();
}
