#include "RenderScene.h"
#include "glew.h"
#include "wglew.h"
#include <GL/GL.h>
#include <cmath>

// data for icosahedron
#define NO_VERTICES 12
#define NO_FACES    20

#define XISO .525731112119133606f
#define ZISO .850650808352039932f

static float afVertices[NO_VERTICES*3] =
{
  -XISO, 0.0, ZISO,
  XISO, 0.0, ZISO,
  -XISO, 0.0, -ZISO,
  XISO, 0.0, -ZISO,
  0.0, ZISO, XISO,
  0.0, ZISO, -XISO,
  0.0, -ZISO, XISO,
  0.0, -ZISO, -XISO,
  ZISO, XISO, 0.0,
  -ZISO, XISO, 0.0,
  ZISO, -XISO, 0.0,
  -ZISO, -XISO, 0.0
};

static const unsigned int auiIndices[NO_FACES*3] =
{
  0,4,1,
  0,9,4,
  9,5,4,
  4,5,8,
  4,8,1,
  8,10,1,
  8,3,10,
  5,3,8,
  5,2,3,
  2,7,3,
  7,10,3,
  7,6,10,
  7,11,6,
  11,0,6,
  0,1,6,
  6,1,10,
  9,0,11,
  9,11,2,
  9,2,5,
  7,2,11
};

// constructor
RenderScene::RenderScene()
  : m_iWidth( 800 )
  , m_iHeight( 600 )
  , m_fHeightAngle( 0.4f )
  , m_dNearDistance( 5.0f )
  , m_dFarDistance( 15.0f )
  , m_fRotY( 0.0f )
{}

void
RenderScene::setWindowSize( int width, int height )
{
  m_iWidth = width;
  m_iHeight = height;
  glViewport( 0, 0, m_iWidth, m_iHeight );			// tells OpenGL the new size of the render area
}

void
RenderScene::render()
{
  float afPos[] = { 0.0, 0.0, 1.0, 0.0 }; // light source at infinity
  //-----------------------------------------------------------------
  // init GL
  //-----------------------------------------------------------------
  // set background color to blue
  glClearColor(0.0f,0.0f,0.4f,0.0f);
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
  glPolygonMode(GL_FRONT,GL_FILL);
  glPolygonMode(GL_BACK,GL_FILL);
  // do not use culling
  glDisable(GL_CULL_FACE);
  // enable anti-aliasing
  glEnable( GL_MULTISAMPLE_ARB );
  //-----------------------------------------------------------------
  // render camera
  //-----------------------------------------------------------------
  // render camera
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
  glRotatef( m_fRotY, 0.0f, 1.0f, 0.0f );

  //-----------------------------------------------------------------
  // render scene
  //-----------------------------------------------------------------
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor3f( 1.0f, 1.0f, 1.0f );

  // set pointer to vertex data
  glVertexPointer( 3, GL_FLOAT, 0, afVertices );
  // set pointer to normal data
  glNormalPointer( GL_FLOAT, 0, afVertices );
  // enable vertex and normal pointer
  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_NORMAL_ARRAY );

  // draw polygons
  glDrawElements( GL_TRIANGLES, NO_FACES*3, GL_UNSIGNED_INT, auiIndices );
}

