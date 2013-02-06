#ifndef RENDERSCENEA_H
#define RENDERSCENEA_H

#include "Settings.h"

class RenderSceneA
{
public:
  // constructor
  RenderSceneA();
  // destructor
  ~RenderSceneA() {};

  void Refinement();

protected:
  int m_iNoVerticesNew;
  int m_iNoFacesNew;

};
#endif