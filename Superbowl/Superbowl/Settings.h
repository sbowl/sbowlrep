#ifndef SETTINGS_H
#define SETTINGS_H

// data for tetraeder
#define NO_BASIC_VERTICES 4
#define NO_BASIC_FACES    4
#define NO_VERTICES_MAX 1000

#define ONEOVERSQRT3 0.57735026918963f
#define THREEOVERSQRT5 1.34164078649987f
#define RADIUS 1.0f

extern const float afBasicVertices[NO_BASIC_VERTICES*3];
extern const unsigned int auiBasicIndices[NO_BASIC_FACES*3];

extern float afVertices[NO_VERTICES_MAX*3];
extern int auiIndices[NO_VERTICES_MAX*3];

extern int m_iNoVertices;
extern int m_iNoFaces;

extern int refinementLevelNew;
extern int refinementLevel;
  
#endif
