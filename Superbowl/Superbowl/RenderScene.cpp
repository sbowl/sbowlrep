#include "stdafx.h"


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
{}

void
RenderScene::setWindowSize( int width, int height )
{
  m_iWidth = width;
  m_iHeight = height;
  glViewport( 0, 0, m_iWidth, m_iHeight );			// tells OpenGL the new size of the render area
}

void RenderScene::render_initGL_init()
{
  float afPos[] = { 0.0, 0.0, 1.0, 0.0 }; // light source at infinity
  //-----------------------------------------------------------------
  // init GL
  //-----------------------------------------------------------------
  glClearColor(0.0f,0.0f,0.8f,0.0f); // set background color to blue
  glClearDepth(1.0f); // set depth buffer to far plane
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // actually clear the framebuffer
  glEnable(GL_DEPTH_TEST); // enable depth test with the z-buffer
  glShadeModel( GL_SMOOTH ); // use Gouraud shading
  glEnable( GL_LIGHTING ); // enable light calculation
  glEnable( GL_LIGHT0 ); // set light 0
  glLightfv( GL_LIGHT0, GL_POSITION, afPos );
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); lichteffekte etc fuer textur

	// set material properties from colors
	//glEnable(GL_TEXTURE_2D); // OpenGL Texturen aktivieren
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glPolygonMode(GL_FRONT,GL_LINE); // wireframe for the front side of the polygone
	glPolygonMode(GL_BACK,GL_LINE); //and for the back side
	glDisable(GL_CULL_FACE); // do not use culling
	glEnable( GL_MULTISAMPLE_ARB ); // enable anti-aliasing
}

void RenderScene::render_initGL()
{
  float afPos[] = { 0.0, 0.0, 1.0, 0.0 }; // light source at infinity
  //-----------------------------------------------------------------
  // init GL
  //-----------------------------------------------------------------
  glClearColor(0.0f,0.0f,0.8f,0.0f); // set background color to blue
  glClearDepth(1.0f); // set depth buffer to far plane
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // actually clear the framebuffer
  glEnable(GL_DEPTH_TEST); // enable depth test with the z-buffer
  glShadeModel( GL_SMOOTH ); // use Gouraud shading
  glEnable( GL_LIGHTING ); // enable light calculation
  glEnable( GL_LIGHT0 ); // set light 0
  glLightfv( GL_LIGHT0, GL_POSITION, afPos );
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); lichteffekte etc fuer textur
}

void RenderScene::render_camera_init()
{
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
  render_init = true;

  glRotatef( m_fRot, m_fTurnX, m_fTurnY, 0.0f );
}

void RenderScene::render_camera()
{
	glMatrixMode(GL_PROJECTION);
	glRotatef( m_fRot, m_fTurnX, m_fTurnY, 0.0f );
}

void RenderScene::render_scene()
{
  //-----------------------------------------------------------------
  // render scene
  //-----------------------------------------------------------------
  
  cRendererA.CreateScene();

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
RenderScene::rotNone (void) 
  {
	  m_fRot = 0; 
	  m_fTurnY = 0.0;
	  m_fTurnX = 0.0;
  }

void
RenderScene::Refinement()
{
	cRendererB.Refinement();
}

void RenderScene::SwitchTexture()
{
	cRendererA.SwitchTexture();
}

void RenderScene::SwitchProjection()
{
	cRendererA.SwitchProjection();
}
