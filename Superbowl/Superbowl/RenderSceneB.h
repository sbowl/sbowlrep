#ifndef RENDERSCENEB_H
#define RENDERSCENEB_H

#include "stdafx.h"

class RenderSceneB
{
public:
  // constructor
  RenderSceneB();
  // destructor
  ~RenderSceneB() {};

  void Refinement();

protected:
	void RefinementStep();
};

#endif