#include "stdafx.h"

const float afBasicVertices[NO_BASIC_VERTICES*3] =
{
 -ONEOVERSQRT3*THREEOVERSQRT5*1.0f, -0.3333333333f*THREEOVERSQRT5, 0.3333333333f*THREEOVERSQRT5, 
 ONEOVERSQRT3*THREEOVERSQRT5*1.0f, -0.3333333333f*THREEOVERSQRT5, 0.3333333333f*THREEOVERSQRT5, 
 0.0f*THREEOVERSQRT5,0.6666666666f*THREEOVERSQRT5, 0.0f, 
 0.0f*THREEOVERSQRT5, -0.3333333333f*THREEOVERSQRT5, -0.6666666666f*THREEOVERSQRT5
};

const unsigned int auiBasicIndices[NO_BASIC_FACES*3] =
{
  0,1,2,
  0,1,3,
  0,2,3,
  1,2,3
};

float afVertices[NO_VERTICES_MAX*3];
int auiIndices[NO_FACES_MAX*3];

int m_iNoVertices = NO_BASIC_VERTICES;
int m_iNoFaces = NO_BASIC_FACES;

int refinementLevelNew = 0;
int refinementLevel = 0;

/* initialise everything with default settings */
void initSettings(void) {
	int i;

	refinementLevel = 0;
	refinementLevelNew = 0;

	m_iNoVertices = NO_BASIC_VERTICES;
	m_iNoFaces = NO_BASIC_FACES;

	for (i = 0; i < NO_BASIC_VERTICES*3; i++)
		afVertices[i] = afBasicVertices[i];

	for (i = 0; i < NO_BASIC_FACES*3; i++)
		auiIndices[i] = auiBasicIndices[i];
}
