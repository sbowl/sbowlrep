// Superbowl.cpp: Hauptprojektdatei.

//#include "stdafx.h"

//using namespace System;

#include "glew.h"
#include "wglew.h"
#include <GL/GL.h>
#include "freeglut.h"

#include "RenderScene.h"

#include <iostream>


// define prototypes
void displayCallback(void);
void reshapeCallback( int width, int height );
void keyboardCallback( unsigned char key, int x, int y);

// global variable :(
// uncomment to render a particular scene
RenderScene	 cRenderer;
//RenderScene2 cRenderer;

int main(int argc, char* argv[])
{
  int win;
  const unsigned int uiWidth = 800;
  const unsigned int uiHeight = 600;

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

  glutMainLoop();
  // never reached
  return 0;
}

void displayCallback()
{
  // render the scene
  cRenderer.render();
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

  case 'k':
    cRenderer.rotY( 5.0f );
    glutPostRedisplay();				            // creates an event for redrawing (calls displayCallback() )
    break;

  case 'l':
    cRenderer.rotY( -5.0f );
    glutPostRedisplay();				            // creates an event for redrawing (calls displayCallback() )
    break;

  case 'o':
    //cRenderer.CamChange();
    glutPostRedisplay();				            // creates an event for redrawing (calls displayCallback() )
    break;
  }
}








