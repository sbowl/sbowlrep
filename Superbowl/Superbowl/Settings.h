#ifndef SETTINGS_H
#define SETTINGS_H

extern bool render_init;

// data for tetraeder
#define NO_BASIC_VERTICES	4
#define NO_BASIC_FACES		4
#define NO_MAX_REFINEMENTS	8	/* [8] */

#define NO_VERTICES_MAX		(4 *4*4*4*4 *4*4*4*4)
#define NO_FACES_MAX		(2 * (NO_VERTICES_MAX - 2))

#define ONEOVERSQRT3 0.57735026918963f
#define THREEOVERSQRT5 1.34164078649987f
#define RADIUS 1.0f
#define pi 3.141592f;

/* für "mods" */
//#define MOD_CRUNCHY ((110.0f - ((float)(rand() % 21))) / 100.0f)
//etwas geringerer Radius (nur bis zu +5% statt +10%) damit der Boden besser paßt..
#define MOD_CRUNCHY ((105.0f - ((float)(rand() % 11))) / 100.0f)

extern const float afBasicVertices[NO_BASIC_VERTICES * 3];
extern const unsigned int auiBasicIndices[NO_BASIC_FACES * 3];

extern float *afVertices;
extern float *afVertices_mod, *afVertices_org;
extern int *auiIndices;
extern float *auiTextureCoord;

extern int m_iNoVertices;
extern int m_iNoFaces;


#define NO_VERTICES_SPHERE 130
#define NO_FACES_SPHERE 256
extern const float afVerticesSphereStart[NO_VERTICES_SPHERE*3];
extern const unsigned int auiIndicesSphereStart[NO_FACES_SPHERE*3];
extern float *afVerticesSphere;
extern unsigned int *auiIndicesSphere;


extern int refinementLevelNew;
extern int refinementLevel;
extern int BallMod;
extern int CamMoveV;
extern int CamMoveH;
extern float LightMove;
extern int LightMod, LightModCtrl, LightModCol;
extern float SphereMove;

extern int fps_timer;

extern void initSettings(void);

//Texture
const unsigned int TEXTURE_WIDTH  = 256;
const unsigned int TEXTURE_HEIGHT = 256;

//Compile
#define _CRT_SECURE_NO_WARNINGS 1
#endif
