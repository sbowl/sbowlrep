#ifndef RENDERSCENEB_H
#define RENDERSCENEB_H

#include "Settings.h"

class RenderSceneB
{
public:
  // constructor
  RenderSceneB();
  // destructor
  ~RenderSceneB() {};

  void Refinement();

protected:
  int m_iNoVerticesNew;
  int m_iNoFacesNew;

};
#endif