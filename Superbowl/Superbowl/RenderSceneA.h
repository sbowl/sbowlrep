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
  void SwitchProjection();

  void CreateScene();
  void RenderScene();

  void UpdateTextureCoord(float *auiTextureCoord);

  float CalculateTextureCoordX(int VertexIndex);
  float CalculateTextureCoordY(int VertexIndex);
  float CalculateLongitude(int VertexIndex);
  float CalculateLatitude(int VertexIndex);

protected:
	
	int TextureMode; //1 = wireframe, 2 = fill, 3 = texture
	int intProjMode; //0 = without Mercator, 1 = with Mercator

};
#endif