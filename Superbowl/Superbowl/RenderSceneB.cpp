/* extra stuff from doodb */
#include "stdafx.h"

RenderSceneB::RenderSceneB()
{
}

#define REFINEMENT_DEBUG
void RenderSceneB::Refinement()
{
#ifdef REFINEMENT_DEBUG
	wchar_t txt1[100];
	char txt2[100];
	int cp = -1;
#endif
	
	if (refinementLevelNew < 0) refinementLevelNew = 0;
	if (refinementLevelNew > 10) refinementLevelNew = 10;

#ifdef REFINEMENT_DEBUG
	sprintf(txt2, "%d,%d", refinementLevel, refinementLevelNew);
	/* convert char to wchar_t ... */
	do {
			cp++;
			txt1[cp] = txt2[cp];
	} while(txt2[cp]);
	MessageBox(HWND_DESKTOP,txt1,L"refinementLevel(New)",MB_OK);
#endif

	while (refinementLevelNew > refinementLevel)
	RefinementStep();
}

void RenderSceneB::RefinementStep()
{

#if 0 /* we're gonna rebuild the arrays from scratch? */

	int i;
	float afVerticesOld[NO_VERTICES_MAX*3];
	int auiIndicesOld[NO_FACES_MAX*3];

	/* backup current indexed shape set */
	for (i = 0; i < NO_VERTICES_MAX*3; i++)
		afVerticesOld[i] = afVertices[i];
	for (i = 0; i < NO_FACES_MAX*3; i++)
		auiIndicesOld[i = auiIndices[i];
	
	/* reset current indexed shape set */
	m_iNoVertices = 0;
	m_iNoFaces = 0;

	/* rebuild current iss from backed up iss, while refining 1 step */

#else /* just append additional stuff to the arrays */
	
	int i, j;

	/* tempor�re vars f�r coords */
	int vInd;
	float vx, vy, vz;

	int vertexInd = m_iNoVertices - 1;
	int m_iNoFacesOld = m_iNoFaces;

	/* paranoia */
	if (m_iNoFacesOld > NO_FACES_MAX / 4) {
		refinementLevelNew = refinementLevel;
		return;
	}

	/* transverse all faces, turn each one into 4 new ones */
	m_iNoFaces *= 4;

	/* Idee:
	fl�chen-array kreieren, das 6 (3*2) vertices pro existierender fl�che bereitstellt
	dar�ber iterieren, und unbehandelte vertices ('== -1') hinzuf�gen. dabei:
		nochmals �ber alle fl�chen iterieren, und die, die an die zu behandelnden vertices grenzen
		ebenfalls auf dieselbe neue vertex-# setzen.
		Neu hinzugef�gte ("behandelte") vertices werden einfach ans [bestehende] vertex-array angef�gt,
	�ber das nun vollst�ndig behandelte fl�chen-array iterieren, und ein neues fl�chen-array
	aus allen vertices erzeugen. */

	int bigFace_vertices[(NO_FACES_MAX / 4) * 6]; //m_iNoFacesOld*3*2, aber ist nicht constant..

	/* init bigFace with the current non-refined faces,
	mark 'in-between' vertices that still have to be generated as such */

	/* bekannte (bisherige) vertices eintragen */
	for (i = 0; i < m_iNoFacesOld; i++) {
		bigFace_vertices[i * 6] = auiIndices[i * 3];
		bigFace_vertices[i * 6 + 1] = -1;
		bigFace_vertices[i * 6 + 2] = auiIndices[i * 3 + 1];
		bigFace_vertices[i * 6 + 3] = -1;
		bigFace_vertices[i * 6 + 4] = auiIndices[i * 3 + 2];
		bigFace_vertices[i * 6 + 5] = -1;
	}
	for (i = 0; i < m_iNoFacesOld; i++) {
		/* neue vertices einf�gen (jede kante erh�lt einen vertex in der mitte, wird also halbiert) */
		/* jeden vertex in der kantenmitte berechnen und auf radius normalisieren */

		/* struktur:
				+0
				/\
			  +5  +1
			  /_+3_\
			+4      +2
		*/

		/* f�ge ein falls noch nicht vorhanden */
		if (bigFace_vertices[i * 6 + 1] == -1) {
			bigFace_vertices[i * 6 + 1] = ++vertexInd;
			/* berechne coords */
			vInd = bigFace_vertices[i * 6];
			vx = afVertices[vInd];
			vy = afVertices[vInd + 1];
			vz = afVertices[vInd + 2];
			vInd = bigFace_vertices[i * 6 + 2];
			vx = (vx + afVertices[vInd]) / 2;
			vy = (vy + afVertices[vInd + 1]) / 2;
			vz = (vz + afVertices[vInd + 2]) / 2;
			/* normalize */
			//..
			/* neuen vertex speichern */
			afVertices[vertexInd * 3] = vx;
			afVertices[vertexInd * 3 + 1] = vy;
			afVertices[vertexInd * 3 + 2] = vz;
		}

		/* f�ge ein falls noch nicht vorhanden */
		if (bigFace_vertices[i * 6 + 3] == -1) {
			bigFace_vertices[i * 6 + 3] = ++vertexInd;
			/* berechne coords */
			vInd = bigFace_vertices[i * 6 + 2];
			vx = afVertices[vInd];
			vy = afVertices[vInd + 1];
			vz = afVertices[vInd + 2];
			vInd = bigFace_vertices[i * 6 + 4];
			vx = (vx + afVertices[vInd]) / 2;
			vy = (vy + afVertices[vInd + 1]) / 2;
			vz = (vz + afVertices[vInd + 2]) / 2;
			/* normalize */
			//..
			/* neuen vertex speichern */
			afVertices[vertexInd * 3] = vx;
			afVertices[vertexInd * 3 + 1] = vy;
			afVertices[vertexInd * 3 + 2] = vz;
		}

		/* f�ge ein falls noch nicht vorhanden */
		if (bigFace_vertices[i * 6 + 5] == -1) {
			bigFace_vertices[i * 6 + 5] = ++vertexInd;
			/* berechne coords */
			vInd = bigFace_vertices[i * 6 + 4];
			vx = afVertices[vInd];
			vy = afVertices[vInd + 1];
			vz = afVertices[vInd + 2];
			vInd = bigFace_vertices[i * 6];
			vx = (vx + afVertices[vInd]) / 2;
			vy = (vy + afVertices[vInd + 1]) / 2;
			vz = (vz + afVertices[vInd + 2]) / 2;
			/* normalize */
			//..
			/* neuen vertex speichern */
			afVertices[vertexInd * 3] = vx;
			afVertices[vertexInd * 3 + 1] = vy;
			afVertices[vertexInd * 3 + 2] = vz;
		}

		/* �ber bisher unbekannte fl�chen iterieren und dort die vertices auch gleich eintragen,
		falls angrenzend an dieselbe betroffene Kante */
		for (j = i + 1; j < m_iNoFacesOld; j++) {
			/* check edge 1 of this face */
			if (bigFace_vertices[j * 6 + 1] == -1 &&
				auiIndices[j * 3] == auiIndices[i * 3] &&
				auiIndices[j * 3 + 1] == auiIndices[i * 3 + 1]) {
					bigFace_vertices[j * 6 + 1] = bigFace_vertices[i * 6 + 1];
			}
			/* check edge 2 of this face */
			if (bigFace_vertices[j * 6 + 3] == -1 &&
				auiIndices[j * 3 + 1] == auiIndices[i * 3 + 1] &&
				auiIndices[j * 3 + 2] == auiIndices[i * 3 + 2]) {
					bigFace_vertices[j * 6 + 3] = bigFace_vertices[i * 6 + 3];
			}
			/* check edge 3 of this face */
			if (bigFace_vertices[j * 6 + 5] == -1 &&
				auiIndices[j * 3 + 2] == auiIndices[i * 3 + 2] &&
				auiIndices[j * 3] == auiIndices[i * 3]) {
					bigFace_vertices[j * 6 + 5] = bigFace_vertices[i * 6 + 5];
			}
		}
	}

	/* update # of vertices we got now */
	m_iNoVertices = vertexInd + 1;

	/* generate new faces array from our temporary bigFaces array:
				+0			/\
				/\		   /\/\
			  +5  +1	   ````
			  /_+3_\
			+4      +2
	*/
	for (i = 0; i < m_iNoFacesOld; i++) {
		/* generate 4 faces from each big face */
		auiIndices[i * 3 * 4] = bigFace_vertices[i * 6];
		auiIndices[i * 3 * 4 + 1] = bigFace_vertices[i * 6 + 1];
		auiIndices[i * 3 * 4 + 2] = bigFace_vertices[i * 6 + 5];

		auiIndices[i * 3 * 4 + 3] = bigFace_vertices[i * 6 + 1];
		auiIndices[i * 3 * 4 + 4] = bigFace_vertices[i * 6 + 2];
		auiIndices[i * 3 * 4 + 5] = bigFace_vertices[i * 6 + 3];

		auiIndices[i * 3 * 4 + 6] = bigFace_vertices[i * 6 + 1];
		auiIndices[i * 3 * 4 + 7] = bigFace_vertices[i * 6 + 3];
		auiIndices[i * 3 * 4 + 8] = bigFace_vertices[i * 6 + 5];

		auiIndices[i * 3 * 4 + 9] = bigFace_vertices[i * 6 + 5];
		auiIndices[i * 3 * 4 + 10] = bigFace_vertices[i * 6 + 3];
		auiIndices[i * 3 * 4 + 11] = bigFace_vertices[i * 6 + 4];
	}

#endif

	/* we're now 1 refinement level better than when we started */
	refinementLevel++;
}
