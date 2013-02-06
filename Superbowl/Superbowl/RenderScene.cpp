#include "RenderScene.h"
#include "glew.h"
#include "wglew.h"
#include <GL/GL.h>
#include <cmath>
#include <vector>
#include <stdio.h>
#include "Settings.h"


RenderSceneA cRendererA;
RenderSceneB cRendererB;

// constructor
RenderScene::RenderScene()
  : m_iWidth( 800 )
  , m_iHeight( 600 )
  , m_fHeightAngle( 0.4f )
  , m_dNearDistance( 5.0f )
  , m_dFarDistance( 15.0f )
  , m_fRot( 0.0f )
  , m_fTurnX ( 0.0f)
  , m_fTurnY (0.0f)
  , m_bRendered (false)
{}

void
RenderScene::setWindowSize( int width, int height )
{
  m_iWidth = width;
  m_iHeight = height;
  glViewport( 0, 0, m_iWidth, m_iHeight );			// tells OpenGL the new size of the render area
}

void RenderScene::render_initGL()
{
  float afPos[] = { 0.0, 0.0, 1.0, 0.0 }; // light source at infinity
  //-----------------------------------------------------------------
  // init GL
  //-----------------------------------------------------------------
  // set background color to blue
  glClearColor(0.0f,0.0f,0.8f,0.0f);
  // set depth buffer to far plane
  glClearDepth(1.0f);
  // actually clear the framebuffer
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  // enable depth test with the z-buffer
  glEnable(GL_DEPTH_TEST);
  // use Gouraud shading
  glShadeModel( GL_SMOOTH );
  // enable light calculation
  glEnable( GL_LIGHTING );
  // set light 0
  glEnable( GL_LIGHT0 );
  glLightfv( GL_LIGHT0, GL_POSITION, afPos );

  // set material properties from colors
  glEnable( GL_COLOR_MATERIAL );
  glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
  // fill the front side of the polygone and use wireframe for back side
  glPolygonMode(GL_FRONT,GL_LINE);
  glPolygonMode(GL_BACK,GL_LINE);
  // do not use culling
  glDisable(GL_CULL_FACE);
  // enable anti-aliasing
  glEnable( GL_MULTISAMPLE_ARB );
}

void RenderScene::render_camera()
{
  //-----------------------------------------------------------------
  // render camera
  //-----------------------------------------------------------------
  // render camera
  
  if (m_bRendered) {
	glMatrixMode(GL_PROJECTION);
	glRotatef( m_fRot, m_fTurnX, m_fTurnY, 0.0f );
	return;
  }

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  
  double left,right,bottom,top;
  top=m_dNearDistance * tan( m_fHeightAngle/2.0 );
  bottom=-top;
  right=top * (double)m_iWidth/(double)m_iHeight;
  left=-right;
	  
  glFrustum((GLdouble)left,(GLdouble)right,(GLdouble)bottom,(GLdouble)top,(GLdouble)m_dNearDistance,(GLdouble)m_dFarDistance);
  // camera placed at (0 0 10) looking in -z direction
  glTranslatef( 0, 0, -10.0f );
  m_bRendered = true;

  glRotatef( m_fRot, m_fTurnX, m_fTurnY, 0.0f );
}

void RenderScene::render_scene()
{
  //-----------------------------------------------------------------
  // render scene
  //-----------------------------------------------------------------
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor3f( 1.0f, 1.0f, 1.0f );

  // set pointer to vertex data
  glVertexPointer( 3, GL_FLOAT, 0, afBasicVertices );
  // set pointer to normal data
  glNormalPointer( GL_FLOAT, 0, afBasicVertices );
  // enable vertex and normal pointer
  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_NORMAL_ARRAY );

  // draw polygons
  glDrawElements( GL_TRIANGLES, NO_BASIC_FACES*3, GL_UNSIGNED_INT, auiBasicIndices );
}

void 
RenderScene::rotY( float fAngle ) 
  { 
	  m_fRot = fAngle; 
	  m_fTurnY = 1.0;
	  m_fTurnX = 0.0;
  }

void 
RenderScene::rotX ( float fAngle ) 
  {
	  m_fRot = fAngle; 
	  m_fTurnY = 0.0;
	  m_fTurnX = 1.0;
  }

void
RenderScene::Refinement()
{
	/* Beispiel: Verwende das Refinement() von dooda */
	cRendererA.Refinement();
	/* oder doch das andere? */
	//cRendererB.Refinement();
}
