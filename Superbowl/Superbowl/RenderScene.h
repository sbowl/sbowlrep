#ifndef RENDERSCENE_H
#define RENDERSCENE_H

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
  void render();
  // rotate scene
  void rotY( float fAngle ) { m_fRotY += fAngle; }

protected:
  int   m_iWidth;
  int   m_iHeight;

  // vertical viewing angle
  float m_fHeightAngle;

  // near and far distance of scene
  double m_dNearDistance;
  double m_dFarDistance;

  // rotation angle around y-axis
  float  m_fRotY;
};
#endif