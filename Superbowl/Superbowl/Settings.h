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

/* für "mods" */
#define MOD_CRUNCHY ((110.0f - ((float)(rand() % 21))) / 100.0f)

extern const float afBasicVertices[NO_BASIC_VERTICES * 3];
extern const unsigned int auiBasicIndices[NO_BASIC_FACES * 3];

extern float *afVertices;
extern float *afVertices_mod, *afVertices_org;
extern int *auiIndices;
extern float *auiTextureCoord;

extern int m_iNoVertices;
extern int m_iNoFaces;

extern int refinementLevelNew;
extern int refinementLevel;
extern int BallMod;

extern int fps_timer;

extern void initSettings(void);

//Texture
const unsigned int TEXTURE_WIDTH  = 256;
const unsigned int TEXTURE_HEIGHT = 256;

//Compile
#define _CRT_SECURE_NO_WARNINGS 1
#endif
