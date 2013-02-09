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

  void Plane();

  void SwitchTexture();

  void CreateScene();

  void UpdateTextureCoord(float *auiTextureCoord);

  void CalculateTextureCoord();

protected:
	
	int TextureMode; //1 = wire, 2 = fill, 3 = texture
	

};
#endif