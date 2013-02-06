#include "RenderScene.h"
#include "glew.h"
#include "wglew.h"
#include <GL/GL.h>
#include <cmath>
#include <vector>
#include <stdio.h>

// data for tetraeder
#define NO_BASIC_VERTICES 4
#define NO_BASIC_FACES    4

//#define EDGE 1.63299316185545 //Umkugelradius=1 => a= 4/sqrt(6)
//#define HEIGHT 1.41421356237310 //sqrt(3)/2 * a

#define ONEOVERSQRT3 0.57735026918963f
#define THREEOVERSQRT5 1.34164078649987
#define RADIUS 1

static float afBasicVertices[NO_BASIC_VERTICES*3] =
{//bei 1,1,1 beginnend, gegen den uhrzeigersinn
//  ONEOVERSQRT3*RADIUS,ONEOVERSQRT3*RADIUS, ONEOVERSQRT3*RADIUS,
//  ONEOVERSQRT3*RADIUS,ONEOVERSQRT3*RADIUS, -ONEOVERSQRT3*RADIUS,
//  -ONEOVERSQRT3*RADIUS,ONEOVERSQRT3*RADIUS, ONEOVERSQRT3*RADIUS,
//  -ONEOVERSQRT3*RADIUS,ONEOVERSQRT3*RADIUS, -ONEOVERSQRT3*RADIUS,
//  -ONEOVERSQRT3*RADIUS,-ONEOVERSQRT3*RADIUS, ONEOVERSQRT3*RADIUS,
//  -ONEOVERSQRT3*RADIUS,-ONEOVERSQRT3*RADIUS, -ONEOVERSQRT3*RADIUS,
//  ONEOVERSQRT3*RADIUS,-ONEOVERSQRT3*RADIUS, ONEOVERSQRT3*RADIUS,
//  ONEOVERSQRT3*RADIUS,-ONEOVERSQRT3*RADIUS, -ONEOVERSQRT3*RADIUS
 -ONEOVERSQRT3*THREEOVERSQRT5, -0.3333333333*THREEOVERSQRT5, 0.3333333333*THREEOVERSQRT5, 
 ONEOVERSQRT3*THREEOVERSQRT5, -0.3333333333*THREEOVERSQRT5, 0.3333333333*THREEOVERSQRT5, 
 0*THREEOVERSQRT5,0.6666666666*THREEOVERSQRT5, 0, 
 0*THREEOVERSQRT5, -0.3333333333*THREEOVERSQRT5, -0.6666666666*THREEOVERSQRT5
};

static const unsigned int auiBasicIndices[NO_BASIC_FACES*3] =
{
  0,1,2,
  0,1,3,
  0,2,3,
  1,2,3
//  0,1,3,
//	0,3,2,
//	2,3,5,
//	2,5,4,
//	0,2,4,
//	0,4,6,
//	0,6,7,
//	0,1,7,
//	1,3,7,
//	3,5,7,
//	4,5,6,
//	5,6,7
};

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

	//std::vector<int> v;
 //   int i;
 //
 //   for (i=0; i<100; ++i) {
 //       v.push_back(i); // Fügt i ans Ende von v an.
 //       ++v[i]; // v[i] muss bereits existieren.
	//}
	//printf("%d", v[2]);
}