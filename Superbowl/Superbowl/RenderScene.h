#ifndef RENDERSCENE_H
#define RENDERSCENE_H

#include "stdafx.h"


class RenderScene
{
public:
  // constructor
  RenderScene();
  // destructor
  ~RenderScene() {};

  // set the size of the window
  void setWindowSize( int width, int height );
  // render the scene
  void render_initGL_init();
  void render_initGL();
  void render_camera_init();
  void render_camera();
  void render_scene();
  // rotate scene
  void rotY( float fAngle ) ;
  void rotX ( float fAngle ) ;
  void rotNone (void);

  void Refinement();

  void SwitchTexture();
  void SwitchProjection();

protected:
  int   m_iWidth;
  int   m_iHeight;

  // vertical viewing angle
  float m_fHeightAngle;

  // near and far distance of scene
  double m_dNearDistance;
  double m_dFarDistance;

  // rotation angle around y-axis
  float  m_fRot;
  float  m_fTurnX;
  float  m_fTurnY;
};
#endif