
#include "Utility.h"
#include "Model.h"
#include "View.h"
#include "ECSCoordinator.h"
#include "GL/glut.h"


ECSCoordinator gCoordinator;
View view;

//
// Keyboard callback routine.
// Send model and view commands based on key presses
//
void handleKey(unsigned char key, int x, int y){
  const int ESC = 27;
  
  switch(key){
    case 'k':           // toggle key light on and off
      view.toggleKeyLight();
      break;
      
    case 'f':           // toggle fill light on and off
      view.toggleFillLight();
      break;
      
    case 'r':           // toggle back light on and off
      view.toggleBackLight();
      break;
      
    case 'g':           // toggle background color from grey to black
      view.toggleBackColor();
      break;

    case 'i':			// I -- reinitialize view
    case 'I':
      view.setInitialView();
      break;
      
    case 'q':			// Q or Esc -- exit program
    case 'Q':
    case ESC:
      exit(0);
  }
  
  // always refresh the display after a key press
  glutPostRedisplay();
}

//
// let the View handle mouse button events
// but pass along the state of the shift key also
//
void handleButtons(int button, int state, int x, int y) {
  bool shiftkey = (glutGetModifiers() == GLUT_ACTIVE_SHIFT);

	view.handleButtons(button, state, x, y, shiftkey);
  glutPostRedisplay();
}

//
// let the View handle mouse motion events
//
void handleMotion(int x, int y) {
  view.handleMotion(x, y);
  glutPostRedisplay();
}

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
// let the View handle reshape events
//
void doReshape(int width, int height){
  view.reshapeWindow(width, height);
}

//
// Draws the scene through each Render System\
//
void draw_func(){
	view.updateDisplay();
}


int main(int argc, char* argv[]){
	_init_gCoordinator();
	
	build_model();
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(view.getWidth(), view.getHeight());
	glutCreateWindow("3D Bouncing Ball");
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.66, 0.66, 0.66, 1.0);

	glutDisplayFunc(draw_func);
	glutReshapeFunc(doReshape);
	glutKeyboardFunc(handleKey);
	glutMotionFunc(handleMotion);
	glutMouseFunc(handleButtons);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_NORMALIZE);

	glutIdleFunc(draw_func);
	
	view.setInitialView();


	glutMainLoop();

	return 0;
}