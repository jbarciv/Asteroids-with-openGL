
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ESC 27
#define WINX 1024   // Dimensiones de la ventana
#define WINY 800
using namespace std;

// Prototipos de funciones 
void myLogic();
void DibujarCubo();

//Callback para teclado y raton
void OnKeyboardDown(unsigned char key, int x, int y);
void OnSpecKeyboardDown(int key, int x, int y);

//Callbacks de dibujo
void OnDibuja(void);	

// Posicion y step de la camara
float cam_pos[6]={0, 0, 27};

float rot=0;
float vel=0.25;

/**************************************************************/
int main(int argc,char* argv[]){

    // Inicializaciones

    //Creacion y definicion de la ventana
    glutInit(&argc, argv);
    glutInitWindowSize(WINX,WINY);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Asteroids GL"); // Nombre de la ventana

    //Habilitar las luces, la renderizacion y el color de los materiales
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);


    //definir la proyeccion
    glMatrixMode(GL_PROJECTION);
    gluPerspective( 40.0, WINX/WINY, 0.1, 50);


    // define call backs to GLUT
    glutDisplayFunc(OnDibuja);
    glutIdleFunc(myLogic);

    glutKeyboardFunc(OnKeyboardDown);
    glutSpecialFunc(OnSpecKeyboardDown);
    
    
    //Para definir el punto de vista
    glMatrixMode(GL_MODELVIEW);	
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);    
    
    
    // posicciona el punto de vista 
    gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],  // posicion del  ojo  
    	    0.0, 0.0, 0.0,		        // hacia que punto mira  
    	    0.0, 1.0, 0.0);         // vector "UP"  (vertical positivo)


    // bucle del programa
    glutMainLoop();
    
    return 0;   
}
/**************************************************************/

void myLogic(){
    rot += vel;

    if(rot>360) rot=0;
}
 
/**************************************************************/
void OnDibuja(void){ 
    //Borrado de la pantalla	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DibujarCubo();

    // posicciona el punto de vista
    glLoadIdentity();
    gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],  // posicion del  ojo  
    	    0.0, 0.0, 0.0,		        // hacia que punto mira  
    	    0.0, 1.0, 0.0);             // vector "UP"  (vertical positivo)


    //Al final, cambiar el buffer
    glutSwapBuffers();
    glutPostRedisplay();//se le indica que redibuje la pantalla
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

void DibujarCubo(void){
  glPushMatrix();
  glTranslatef(0,1,0);
  glRotatef(rot,1,0,0);
  glRotatef(rot,0,1,0);
  glRotatef(0,0,0,1);
  glColor3f(0,1,0);
  glutSolidCube(3);
  glPopMatrix();
}
