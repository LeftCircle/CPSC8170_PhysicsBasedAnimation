
#include "Utility.h"
#include "Model.h"
#include "View.h"
#include "ECSCoordinator.h"
#include "GL/glut.h"


ECSCoordinator gCoordinator;



void _register_components(){
	gCoordinator.RegisterComponent<ElementBuffer>();
}

void _register_systems(){
	gCoordinator.RegisterSystem<RenderElementBufferSystem>();
}


void _init_gCoordinator(){
	gCoordinator.Init();
	_register_components();
	_register_systems();
	gCoordinator.set_system_signatures();
}

//
// Draws the scene through each Render System\
//
void draw_func(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	gCoordinator.update_system<RenderElementBufferSystem>();
	
	glutSwapBuffers();
}

//
// Keypress handling
//
void handleKey(unsigned char key, int x, int y){
  
  switch(key){
    case 'q':		// q - quit
    case 'Q':
    case 27:		// esc - quit
      exit(0);
      
    default:		// not a valid key -- just ignore it
      return;
  }
}

int main(int argc, char* argv[]){
	_init_gCoordinator();
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(960, 540);
	glutCreateWindow("3D Bouncing Ball");
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.66, 0.66, 0.66, 1.0);

	glutReshapeFunc(NULL);
	glutDisplayFunc(draw_func);
	glutIdleFunc(draw_func);
	glutKeyboardFunc(handleKey);
	glutMouseFunc(NULL);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_NORMALIZE);

	glutMainLoop();

	return 0;
}