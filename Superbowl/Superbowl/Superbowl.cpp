// Superbowl.cpp: Hauptprojektdatei.

//#include "stdafx.h"

//using namespace System;

#include "glew.h"
#include "wglew.h"
#include <GL/GL.h>
#include "freeglut.h"

#include "RenderScene.h"

#include <iostream>
#include <time.h>


// define prototypes
void displayCallback(void);
void reshapeCallback( int width, int height );
void keyboardCallback( unsigned char key, int x, int y);

// global variable :(
// uncomment to render a particular scene
RenderScene	 cRenderer;

void DebugDialog(wchar_t *title, int num1, int num2) {
	wchar_t txt1[100];
	char txt2[100];
	int cp = -1;

	/* sprintf verlangt char.. */
	sprintf_s(txt2, "%d,%d", num1, num2);

	/* convert char to wchar_t... */
	do {
			cp++;
			txt1[cp] = txt2[cp];
	} while(txt2[cp]);

	/* msgbox verlangt wchar_t.... */
	MessageBox(HWND_DESKTOP, txt1, title, MB_OK);
}

void DebugDialogf(wchar_t *title, float num1, float num2) {
	wchar_t txt1[100];
	char txt2[100];
	int cp = -1;

	/* sprintf verlangt char.. */
	sprintf_s(txt2, "%f,%f", num1, num2);

	/* convert char to wchar_t... */
	do {
			cp++;
			txt1[cp] = txt2[cp];
	} while(txt2[cp]);

	/* msgbox verlangt wchar_t.... */
	MessageBox(HWND_DESKTOP, txt1, title, MB_OK);
}

/* Loop um alle 1/fps Sekunden irgendwas zu machen */
#define FPS 25
void nebenher_zeug(void) {
	clock_t t = clock();
    if (t - fps_timer < CLOCKS_PER_SEC / FPS) return;
	fps_timer = t;

	/* disable? */
	//return;

	/* Zeug machen.. */

	//rotate little sphere
	glVertexPointer( 3, GL_FLOAT, 0, afVerticesSphere );
	glMatrixMode(GL_MODELVIEW);
	glRotatef(1.0f,0.0f,1.0f,0.0f);


	/* X-rotation */
	glMatrixMode(GL_PROJECTION);
	glRotatef( 1.0f, 0.0f, 1.0f, 0.0f);


#if 1
	/* algo:
	schwenkstrecke merken, halbieren, mittelpunkt bestimmen:
	schwank started auf '0' (x^2) und geht bis mittelpunkt auf zb '1' (x^2) (je nach gewünschter agressivität),
	und ab mittelpunkt wird negiert zu zb(fest) '-1' (x^2) und geht bis zum schwenk-endpunkt hoch auf '0' (x^2). */
	/* Y-rotation */
	static float vrot_goal = 0.0f, vrot_cur = 0.0f, vrot_speed = 0.0f, vrot_mid = 0.0f;
	static bool vrot_inverse = false;
	float vrot_cur_old = vrot_cur, vrot_speed_eff, vrot_cur_norm;
	if (vrot_cur < vrot_goal) {
		/* speed aus x^n algo bestimmen */
#if 0
		if (vrot_cur < vrot_mid) {
			vrot_cur_norm = vrot_cur / vrot_mid;//normalise
		} else {
			vrot_cur_norm = (vrot_goal - vrot_cur) / vrot_mid;//normalise
		}
		vrot_cur_norm /= 2;
		vrot_speed_eff = vrot_speed * (0.1f + vrot_cur_norm * vrot_cur_norm);//avoid 0 speed
#endif
#if 1
		vrot_cur_norm = vrot_cur / vrot_mid - 1;//normalise
		vrot_speed_eff = vrot_speed * (0.1f + 1 - vrot_cur_norm * vrot_cur_norm);//avoid 0 speed
#endif

		/* virtuelle positionierung */
		vrot_cur += abs(vrot_speed_eff);
		/* nicht über's Ziel hinausschießen */
		if (vrot_cur > vrot_goal) vrot_cur = vrot_goal;
	} else {
		/* neues Ziel + speed setzen */
		vrot_cur = 0.0f;

		/* sub-algorithmus für zielpunkt */
#if 0 /* normal: random ziel */
		vrot_goal = 40.0f + (float)(rand() % 140);
		vrot_speed = (1.0f + (float)(rand() % 50) / 50) * 2;
		/* inverse richtung? */
		if (vrot_inverse) vrot_speed = -vrot_speed;
		vrot_inverse = !vrot_inverse;
#endif
#if 1 /* pendel */
		if (!vrot_inverse) {
			vrot_goal = 50 + (float)(rand() % 50);
			vrot_speed = (1.0f + (float)(rand() % 50) / 50) * 2;
		}
		/* inverse richtung? */
		if (vrot_inverse) vrot_speed = -vrot_speed;
		vrot_inverse = !vrot_inverse;
#endif

		/* mittelpunkt bestimmen für x^n geschwindigkeitsalgorithmus */
		vrot_mid = vrot_goal / 2;
	}
	/* rotieren */
	glMatrixMode(GL_PROJECTION);
	glRotatef(vrot_speed_eff, 1.0f, 0.0f, 0.0f);
#endif

	/* redraw */
    cRenderer.rotNone();
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
  int win;
  const unsigned int uiWidth = 800;
  const unsigned int uiHeight = 600;

  initSettings();

  glutInit( &argc, argv );				                              // initialize library
  glutInitWindowSize( uiWidth, uiHeight );			                // set desired window size
  cRenderer.setWindowSize( uiWidth, uiHeight );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE );  
  // asks for double buffering and z-buffer as well as anti-aliasing support
  win = glutCreateWindow(  "OpenGL Example Program" );	        // set the window name and create window

  glutDisplayFunc( &displayCallback );		                      // sets the callback for redrawing
  glutReshapeFunc( &reshapeCallback );		                      // set the callback in case of window resizing
  glutKeyboardFunc( &keyboardCallback );		                    // set the callback for key presses
  glewInit();

  std::cout << "press q to quit" << std::endl;
  std::cout << "press k to turn left" << std::endl;
  std::cout << "press l to turn right" << std::endl;

  glutIdleFunc(nebenher_zeug);

  glutMainLoop();
  // never reached
  return 0;
}

void displayCallback()
{
  // render the scene
  if (!render_init) {
	cRenderer.render_initGL_init();
	cRenderer.render_camera_init();
	cRenderer.create_scene();
  } else {
	cRenderer.render_initGL();
	cRenderer.render_camera();
  }
  cRenderer.render_scene();
  // flush the command stream
  glFlush();
  // causes double buffered windows to show rendered content
  glutSwapBuffers();				              
}

void reshapeCallback( int width, int height )
{
  cRenderer.setWindowSize( width, height );
  glutPostRedisplay();				                 // creates an event for redrawing (calls displayCallback() )
}

void keyboardCallback( unsigned char key, int x, int y)
{
  switch( key ) 
  {
  case 'q':
    exit(0);
    break;

	//turn left
  case 'a':
    cRenderer.rotY( 5.0f );
    glutPostRedisplay();				            // creates an event for redrawing (calls displayCallback() )
    break;

	//turn right
  case 'd':
    cRenderer.rotY( -5.0f );
    glutPostRedisplay();				            // creates an event for redrawing (calls displayCallback() )
    break;
	
	//turn upwards
  case 'w':
    cRenderer.rotX( -5.0f );
    glutPostRedisplay();				            // creates an event for redrawing (calls displayCallback() )
    break;
	
	//turn downwards
  case 'x':
    cRenderer.rotX( 5.0f );
    glutPostRedisplay();				            // creates an event for redrawing (calls displayCallback() )
    break;

	//less vertices
  case '-':
	  cRenderer.rotNone();
	  refinementLevelNew = refinementLevel - 1;
	  cRenderer.Refinement();
	  glutPostRedisplay();				            // creates an event for redrawing (calls displayCallback() )
	  break;
	
	  //moar vertices
  case '+':
	  cRenderer.rotNone();
	  refinementLevelNew = refinementLevel + 1;
	  cRenderer.Refinement();
	  glutPostRedisplay();				            // creates an event for redrawing (calls displayCallback() )
	  break;
  //line -> full -> textur -> line
  case 't':
	  cRenderer.rotNone();
	  cRenderer.SwitchTexture();
	  glutPostRedisplay();				            // creates an event for redrawing (calls displayCallback() )
	  break;

	/* ball -> crunchy */
  case 'm':
	  BallMod = (BallMod + 1) % 2;
	  if (BallMod == 0) memcpy(afVertices, afVertices_org, sizeof(float) * m_iNoVertices * 3);
	  else memcpy(afVertices, afVertices_mod, sizeof(float) * m_iNoVertices * 3);
	  break;
	  
	//change mode of projection
  case 'p':
	  cRenderer.SwitchProjection();
	  glutPostRedisplay();
	  break;
  }
}








