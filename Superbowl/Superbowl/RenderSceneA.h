#ifndef RENDERSCENEA_H
#define RENDERSCENEA_H

#include "stdafx.h"

class RenderSceneA
{
public:
  // constructor
  RenderSceneA();
  // destructor
  ~RenderSceneA() {};

  void Refinement();

  void Plane();

  void SwitchTexture();

protected:
	
	int TextureMode; //1 = wire, 2 = fill, 3 = texture
	

};
#endif