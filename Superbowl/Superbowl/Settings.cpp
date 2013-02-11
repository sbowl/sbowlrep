#include "stdafx.h"

bool render_init = false;

const float afBasicVertices[NO_BASIC_VERTICES * 3] =
{
	-ONEOVERSQRT3*THREEOVERSQRT5 * 1.0f, -0.3333333333f * THREEOVERSQRT5, 0.3333333333f * THREEOVERSQRT5, 
	ONEOVERSQRT3*THREEOVERSQRT5 * 1.0f, -0.3333333333f * THREEOVERSQRT5, 0.3333333333f * THREEOVERSQRT5, 
	0.0f * THREEOVERSQRT5 ,1.0f, 0.0f,
	0.0f * THREEOVERSQRT5,  -0.3333333333f * THREEOVERSQRT5, -0.6666666666f * THREEOVERSQRT5
};

const unsigned int auiBasicIndices[NO_BASIC_FACES*3] =
{
  0, 1, 2,
  0, 1, 3,
  0, 2, 3,
  1, 2, 3
};

float *afVertices = new float[NO_VERTICES_MAX * 3];
float *afVertices_mod = new float[NO_VERTICES_MAX * 3];
float *afVertices_org = new float[NO_VERTICES_MAX * 3];
int *auiIndices = new int[NO_FACES_MAX * 3];


float *afVerticesSphere = new float[NO_VERTICES_SPHERE * 3];
unsigned int *auiIndicesSphere = new unsigned int[NO_FACES_SPHERE * 3];

int m_iNoVertices = NO_BASIC_VERTICES;
int m_iNoFaces = NO_BASIC_FACES;

int refinementLevelNew = 0;
int refinementLevel = 0;

int BallMod = 0;
int CamMoveV = 0;
int CamMoveH = 1;
float LightMove = 0.0f;
int LightMod = 1, LightModCtrl = 1, LightModCol = 0;

int fps_timer = 0;

/* initialise everything with default settings */
void initSettings(void) {
	int i;

	refinementLevel = 0;
	refinementLevelNew = 0;

	m_iNoVertices = NO_BASIC_VERTICES;
	m_iNoFaces = NO_BASIC_FACES;

	for (i = 0; i < NO_BASIC_VERTICES * 3; i++) {
		afVertices_org[i] = afBasicVertices[i];
		afVertices_mod[i] = afBasicVertices[i] * MOD_CRUNCHY;

		if (BallMod == 0) afVertices[i] = afVertices_org[i];
		else afVertices[i] = afVertices_mod[i];
	}

	for (i = 0; i < NO_BASIC_FACES * 3; i++)
		auiIndices[i] = auiBasicIndices[i];
}




extern const float afVerticesSphereStart[NO_VERTICES_SPHERE*3] =
{
	-0.774597f, -0.447214f, 0.447214f, 
0.774597f, -0.447214f, 0.447214f, 
0.000000f, 1.000000f, 0.000000f, 
0.000000f, -0.447214f, -0.894427f, 
0.000000f, -0.707107f, 0.707107f, 
0.736685f, 0.525731f, 0.425325f, 
-0.736685f, 0.525731f, 0.425325f, 
0.612372f, -0.707107f, -0.353553f, 
-0.612372f, -0.707107f, -0.353553f, 
0.000000f, 0.525731f, -0.850651f, 
-0.428687f, -0.638838f, 0.638838f, 
-0.540454f, -0.133062f, 0.830785f, 
-0.865150f, 0.044948f, 0.499495f, 
0.428687f, -0.638838f, 0.638838f, 
0.865150f, 0.044948f, 0.499495f, 
0.540454f, -0.133062f, 0.830785f, 
0.000000f, 0.777437f, 0.628960f, 
0.421724f, 0.873422f, 0.243482f, 
-0.421724f, 0.873422f, 0.243482f, 
-0.387298f, -0.894427f, 0.223607f, 
-0.767593f, -0.638838f, 0.051835f, 
0.767593f, -0.638838f, 0.051835f, 
0.387298f, -0.894427f, 0.223607f, 
0.000000f, -0.894427f, -0.447214f, 
0.338907f, -0.638838f, -0.690673f, 
-0.338907f, -0.638838f, -0.690673f, 
-0.989708f, -0.133062f, 0.052654f, 
0.000000f, 0.873422f, -0.486965f, 
-0.544695f, 0.777437f, -0.314480f, 
-0.449254f, -0.133062f, -0.883439f, 
0.000000f, 0.044948f, -0.998989f, 
0.989708f, -0.133062f, 0.052654f, 
0.544695f, 0.777437f, -0.314480f, 
0.449254f, -0.133062f, -0.883439f, 
-0.616711f, -0.556627f, 0.556627f, 
-0.709816f, -0.325816f, 0.624504f, 
-0.847118f, -0.207816f, 0.489084f, 
-0.219712f, -0.689828f, 0.689828f, 
-0.294706f, -0.458140f, 0.838604f, 
-0.504183f, -0.401571f, 0.764552f, 
-0.725548f, -0.045483f, 0.686667f, 
-0.696417f, 0.214120f, 0.684950f, 
-0.827533f, 0.294822f, 0.477776f, 
0.219712f, -0.689828f, 0.689828f, 
0.504183f, -0.401571f, 0.764552f, 
0.294706f, -0.458140f, 0.838604f, 
0.616711f, -0.556627f, 0.556627f, 
0.847118f, -0.207816f, 0.489084f, 
0.709816f, -0.325816f, 0.624504f, 
0.725548f, -0.045483f, 0.686667f, 
0.827533f, 0.294822f, 0.477776f, 
0.696417f, 0.214120f, 0.684950f, 
0.000000f, -0.158149f, 0.987415f, 
0.402346f, 0.711734f, 0.575805f, 
0.320804f, 0.382490f, 0.866479f, 
-0.320804f, 0.382490f, 0.866479f, 
-0.402346f, 0.711734f, 0.575805f, 
-0.220308f, 0.862406f, 0.455763f, 
-0.598452f, 0.722824f, 0.345516f, 
0.598452f, 0.722824f, 0.345516f, 
0.220308f, 0.862406f, 0.455763f, 
0.000000f, 0.963271f, 0.268530f, 
0.217869f, 0.967838f, 0.125787f, 
-0.217869f, 0.967838f, 0.125787f, 
-0.635764f, -0.679022f, 0.367059f, 
-0.790409f, -0.556627f, 0.255774f, 
-0.204661f, -0.846302f, 0.491819f, 
-0.420782f, -0.790664f, 0.444740f, 
-0.595547f, -0.790664f, 0.142038f, 
-0.528258f, -0.846302f, -0.068668f, 
-0.707265f, -0.689828f, -0.154638f, 
0.420782f, -0.790664f, 0.444740f, 
0.204661f, -0.846302f, 0.491819f, 
0.790409f, -0.556627f, 0.255774f, 
0.635764f, -0.679022f, 0.367059f, 
0.595547f, -0.790664f, 0.142038f, 
0.707265f, -0.689828f, -0.154638f, 
0.528258f, -0.846302f, -0.068668f, 
0.000000f, -0.970142f, 0.242536f, 
0.323597f, -0.846302f, -0.423151f, 
0.210042f, -0.970142f, -0.121268f, 
-0.210042f, -0.970142f, -0.121268f, 
-0.323597f, -0.846302f, -0.423151f, 
-0.174765f, -0.790664f, -0.586777f, 
-0.487553f, -0.689828f, -0.535190f, 
0.487553f, -0.689828f, -0.535190f, 
0.174765f, -0.790664f, -0.586777f, 
0.000000f, -0.679022f, -0.734118f, 
0.173698f, -0.556627f, -0.812401f, 
-0.173698f, -0.556627f, -0.812401f, 
-0.895745f, -0.325816f, 0.302466f, 
-0.941392f, 0.214120f, 0.260640f, 
-0.957445f, -0.045483f, 0.285009f, 
-0.914213f, -0.401571f, 0.054359f, 
-0.873605f, -0.458140f, -0.164079f, 
-0.504856f, 0.862406f, -0.037089f, 
-0.699835f, 0.711735f, 0.060539f, 
0.000000f, 0.967838f, -0.251573f, 
-0.232553f, 0.963271f, -0.134265f, 
-0.284548f, 0.862406f, -0.418674f, 
0.000000f, 0.722824f, -0.691033f, 
-0.297489f, 0.711734f, -0.636344f, 
-0.910795f, 0.382490f, -0.155415f, 
-0.244976f, 0.214120f, -0.945590f, 
-0.589991f, 0.382490f, -0.711064f, 
-0.855127f, -0.158149f, -0.493708f, 
-0.578899f, -0.458140f, -0.674525f, 
-0.410030f, -0.401571f, -0.818911f, 
0.000000f, 0.294822f, -0.955552f, 
-0.231897f, -0.045483f, -0.971676f, 
-0.185929f, -0.325816f, -0.926971f, 
0.000000f, -0.207816f, -0.978168f, 
0.895745f, -0.325816f, 0.302466f, 
0.941392f, 0.214120f, 0.260640f, 
0.957445f, -0.045483f, 0.285009f, 
0.914213f, -0.401571f, 0.054359f, 
0.873605f, -0.458140f, -0.164079f, 
0.504856f, 0.862406f, -0.037089f, 
0.699835f, 0.711735f, 0.060539f, 
0.232553f, 0.963271f, -0.134265f, 
0.284548f, 0.862406f, -0.418674f, 
0.297489f, 0.711734f, -0.636344f, 
0.910795f, 0.382490f, -0.155415f, 
0.244976f, 0.214120f, -0.945590f, 
0.589991f, 0.382490f, -0.711064f, 
0.855127f, -0.158149f, -0.493708f, 
0.578899f, -0.458140f, -0.674525f, 
0.410030f, -0.401571f, -0.818911f, 
0.231897f, -0.045483f, -0.971676f, 
0.185929f, -0.325816f, -0.926971f
};
extern const unsigned int auiIndicesSphereStart[NO_FACES_SPHERE*3] = 
{
		0, 34, 36, 
34, 10, 35, 
34, 35, 36, 
36, 35, 12, 
10, 37, 39, 
37, 4, 38, 
37, 38, 39, 
39, 38, 11, 
10, 39, 35, 
39, 11, 40, 
39, 40, 35, 
35, 40, 12, 
12, 40, 42, 
40, 11, 41, 
40, 41, 42, 
42, 41, 6, 
4, 43, 45, 
43, 13, 44, 
43, 44, 45, 
45, 44, 15, 
13, 46, 48, 
46, 1, 47, 
46, 47, 48, 
48, 47, 14, 
13, 48, 44, 
48, 14, 49, 
48, 49, 44, 
44, 49, 15, 
15, 49, 51, 
49, 14, 50, 
49, 50, 51, 
51, 50, 5, 
4, 45, 38, 
45, 15, 52, 
45, 52, 38, 
38, 52, 11, 
15, 51, 54, 
51, 5, 53, 
51, 53, 54, 
54, 53, 16, 
15, 54, 52, 
54, 16, 55, 
54, 55, 52, 
52, 55, 11, 
11, 55, 41, 
55, 16, 56, 
55, 56, 41, 
41, 56, 6, 
6, 56, 58, 
56, 16, 57, 
56, 57, 58, 
58, 57, 18, 
16, 53, 60, 
53, 5, 59, 
53, 59, 60, 
60, 59, 17, 
16, 60, 57, 
60, 17, 61, 
60, 61, 57, 
57, 61, 18, 
18, 61, 63, 
61, 17, 62, 
61, 62, 63, 
63, 62, 2, 
0, 34, 65, 
34, 10, 64, 
34, 64, 65, 
65, 64, 20, 
10, 37, 67, 
37, 4, 66, 
37, 66, 67, 
67, 66, 19, 
10, 67, 64, 
67, 19, 68, 
67, 68, 64, 
64, 68, 20, 
20, 68, 70, 
68, 19, 69, 
68, 69, 70, 
70, 69, 8, 
4, 43, 72, 
43, 13, 71, 
43, 71, 72, 
72, 71, 22, 
13, 46, 74, 
46, 1, 73, 
46, 73, 74, 
74, 73, 21, 
13, 74, 71, 
74, 21, 75, 
74, 75, 71, 
71, 75, 22, 
22, 75, 77, 
75, 21, 76, 
75, 76, 77, 
77, 76, 7, 
4, 72, 66, 
72, 22, 78, 
72, 78, 66, 
66, 78, 19, 
22, 77, 80, 
77, 7, 79, 
77, 79, 80, 
80, 79, 23, 
22, 80, 78, 
80, 23, 81, 
80, 81, 78, 
78, 81, 19, 
19, 81, 69, 
81, 23, 82, 
81, 82, 69, 
69, 82, 8, 
8, 82, 84, 
82, 23, 83, 
82, 83, 84, 
84, 83, 25, 
23, 79, 86, 
79, 7, 85, 
79, 85, 86, 
86, 85, 24, 
23, 86, 83, 
86, 24, 87, 
86, 87, 83, 
83, 87, 25, 
25, 87, 89, 
87, 24, 88, 
87, 88, 89, 
89, 88, 3, 
0, 36, 65, 
36, 12, 90, 
36, 90, 65, 
65, 90, 20, 
12, 42, 92, 
42, 6, 91, 
42, 91, 92, 
92, 91, 26, 
12, 92, 90, 
92, 26, 93, 
92, 93, 90, 
90, 93, 20, 
20, 93, 70, 
93, 26, 94, 
93, 94, 70, 
70, 94, 8, 
6, 58, 96, 
58, 18, 95, 
58, 95, 96, 
96, 95, 28, 
18, 63, 98, 
63, 2, 97, 
63, 97, 98, 
98, 97, 27, 
18, 98, 95, 
98, 27, 99, 
98, 99, 95, 
95, 99, 28, 
28, 99, 101, 
99, 27, 100, 
99, 100, 101, 
101, 100, 9, 
6, 96, 91, 
96, 28, 102, 
96, 102, 91, 
91, 102, 26, 
28, 101, 104, 
101, 9, 103, 
101, 103, 104, 
104, 103, 29, 
28, 104, 102, 
104, 29, 105, 
104, 105, 102, 
102, 105, 26, 
26, 105, 94, 
105, 29, 106, 
105, 106, 94, 
94, 106, 8, 
8, 106, 84, 
106, 29, 107, 
106, 107, 84, 
84, 107, 25, 
29, 103, 109, 
103, 9, 108, 
103, 108, 109, 
109, 108, 30, 
29, 109, 107, 
109, 30, 110, 
109, 110, 107, 
107, 110, 25, 
25, 110, 89, 
110, 30, 111, 
110, 111, 89, 
89, 111, 3, 
1, 47, 73, 
47, 14, 112, 
47, 112, 73, 
73, 112, 21, 
14, 50, 114, 
50, 5, 113, 
50, 113, 114, 
114, 113, 31, 
14, 114, 112, 
114, 31, 115, 
114, 115, 112, 
112, 115, 21, 
21, 115, 76, 
115, 31, 116, 
115, 116, 76, 
76, 116, 7, 
5, 59, 118, 
59, 17, 117, 
59, 117, 118, 
118, 117, 32, 
17, 62, 119, 
62, 2, 97, 
62, 97, 119, 
119, 97, 27, 
17, 119, 117, 
119, 27, 120, 
119, 120, 117, 
117, 120, 32, 
32, 120, 121, 
120, 27, 100, 
120, 100, 121, 
121, 100, 9, 
5, 118, 113, 
118, 32, 122, 
118, 122, 113, 
113, 122, 31, 
32, 121, 124, 
121, 9, 123, 
121, 123, 124, 
124, 123, 33, 
32, 124, 122, 
124, 33, 125, 
124, 125, 122, 
122, 125, 31, 
31, 125, 116, 
125, 33, 126, 
125, 126, 116, 
116, 126, 7, 
7, 126, 85, 
126, 33, 127, 
126, 127, 85, 
85, 127, 24, 
33, 123, 128, 
123, 9, 108, 
123, 108, 128, 
128, 108, 30, 
33, 128, 127, 
128, 30, 129, 
128, 129, 127, 
127, 129, 24, 
24, 129, 88, 
129, 30, 111, 
129, 111, 88, 
88, 111, 3
};