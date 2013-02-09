/* extra stuff from doodb */
#include "stdafx.h"

#define CRUNCHY ((110.0f - ((float)(rand() % 21))) / 100.0f)

RenderSceneB::RenderSceneB()
{
}

void RenderSceneB::Refinement()
{
	
	if (refinementLevelNew < 0) refinementLevelNew = 0;
	if (refinementLevelNew > NO_MAX_REFINEMENTS) refinementLevelNew = NO_MAX_REFINEMENTS;

	while (refinementLevelNew > refinementLevel)
		RefinementStep();
	while (refinementLevelNew < refinementLevel)
		DefinementStep();
}

void RenderSceneB::RefinementStep()
{
	/* rebuild current iss from backed up iss, while refining 1 step */	

	/* für optimierungen */
	int oi3, oi6, oj6;
	bool cv1, cv3, cv5;

	float vlen; //für vektor-normalisierung
	int i, j;

	/* temporäre vars für coords */
	int vInd;
	float vx, vy, vz;

	int m_iNoVerticesOld = m_iNoVertices;
	int vertexInd = m_iNoVertices;
	int m_iNoFacesOld = m_iNoFaces;

	/* paranoia */
	if (m_iNoFacesOld > NO_FACES_MAX / 4) {
		refinementLevelNew = refinementLevel;
		return;
	}

	/* transverse all faces, turn each one into 4 new ones */
	m_iNoFaces *= 4;

	/* Idee:
	flächen-array kreieren, das 6 (3*2) vertices pro existierender fläche bereitstellt
	darüber iterieren, und unbehandelte vertices ('== -1') hinzufügen. dabei:
		nochmals über alle flächen iterieren, und die, die an die zu behandelnden vertices grenzen
		ebenfalls auf dieselbe neue vertex-# setzen.
		Neu hinzugefügte ("behandelte") vertices werden einfach ans [bestehende] vertex-array angefügt,
	über das nun vollständig behandelte flächen-array iterieren, und ein neues flächen-array
	aus allen vertices erzeugen. */

	//int bigFace_vertices[(NO_FACES_MAX / 4) * 6]; //m_iNoFacesOld*3*2, aber ist nicht constant..
	int *bigFace_vertices = new int[(NO_FACES_MAX / 4) * 6];

	/* init bigFace with the current non-refined faces,
	mark 'in-between' vertices that still have to be generated as such */

	/* bekannte (bisherige) vertices eintragen */
	for (i = 0; i < m_iNoFacesOld; i++) {
		oi3 = i * 3;
		oi6 = i * 6;
		bigFace_vertices[oi6 + 0] = auiIndices[oi3 + 0];
		bigFace_vertices[oi6 + 1] = -1;
		bigFace_vertices[oi6 + 2] = auiIndices[oi3 + 1];
		bigFace_vertices[oi6 + 3] = -1;
		bigFace_vertices[oi6 + 4] = auiIndices[oi3 + 2];
		bigFace_vertices[oi6 + 5] = -1;
	}

	/* neue vertices einfügen (jede kante erhält einen vertex in der mitte, wird also halbiert) */
	for (i = 0; i < m_iNoFacesOld; i++) {
		/* jeden vertex in der kantenmitte berechnen und auf radius normalisieren */

		/* struktur:
				+0
				/\
			  +5  +1
			  /_+3_\
			+4      +2
		*/

		oi6 = i * 6;
		cv1 = cv3 = cv5 = true;

		/* füge ein falls noch nicht vorhanden */
		if (bigFace_vertices[oi6 + 1] == -1) {
			cv1 = false;
			bigFace_vertices[oi6 + 1] = vertexInd;
			/* berechne coords */
			vInd = bigFace_vertices[oi6 + 0];
			oi3 = vInd * 3;
			vx = afVertices[oi3 + 0];
			vy = afVertices[oi3 + 1];
			vz = afVertices[oi3 + 2];
			vInd = bigFace_vertices[oi6 + 2];
			oi3 = vInd * 3;
			vx = (vx + afVertices[oi3 + 0]) / 2;
			vy = (vy + afVertices[oi3 + 1]) / 2;
			vz = (vz + afVertices[oi3 + 2]) / 2;
			/* normalize */
			vlen = sqrtf(vx*vx + vy*vy + vz*vz);
			vx = vx / vlen;
			vy = vy / vlen;
			vz = vz / vlen;
			/* neuen vertex speichern */
			oi3 = vertexInd * 3;
			switch (BallMod) {
			case 0:
				afVertices[oi3 + 0] = vx;
				afVertices[oi3 + 1] = vy;
				afVertices[oi3 + 2] = vz;
				break;
			case 1:
				afVertices[oi3 + 0] = vx * CRUNCHY;
				afVertices[oi3 + 1] = vy * CRUNCHY;
				afVertices[oi3 + 2] = vz * CRUNCHY;
				break;
			}

			vertexInd++;
		}

		/* füge ein falls noch nicht vorhanden */
		if (bigFace_vertices[oi6 + 3] == -1) {
			cv3 = false;
			bigFace_vertices[oi6 + 3] = vertexInd;
			/* berechne coords */
			vInd = bigFace_vertices[oi6 + 2];
			oi3 = vInd * 3;
			vx = afVertices[oi3 + 0];
			vy = afVertices[oi3 + 1];
			vz = afVertices[oi3 + 2];
			vInd = bigFace_vertices[oi6 + 4];
			oi3 = vInd * 3;
			vx = (vx + afVertices[oi3 + 0]) / 2;
			vy = (vy + afVertices[oi3 + 1]) / 2;
			vz = (vz + afVertices[oi3 + 2]) / 2;
			/* normalize */
			vlen = sqrtf(vx*vx + vy*vy + vz*vz);
			vx = vx / vlen;
			vy = vy / vlen;
			vz = vz / vlen;
			/* neuen vertex speichern */
			oi3 = vertexInd * 3;
			switch (BallMod) {
			case 0:
				afVertices[oi3 + 0] = vx;
				afVertices[oi3 + 1] = vy;
				afVertices[oi3 + 2] = vz;
				break;
			case 1:
				afVertices[oi3 + 0] = vx * CRUNCHY;
				afVertices[oi3 + 1] = vy * CRUNCHY;
				afVertices[oi3 + 2] = vz * CRUNCHY;
				break;
			}

			vertexInd++;
		}

		/* füge ein falls noch nicht vorhanden */
		if (bigFace_vertices[oi6 + 5] == -1) {
			cv5 = false;
			bigFace_vertices[oi6 + 5] = vertexInd;
			/* berechne coords */
			vInd = bigFace_vertices[oi6 + 4];
			oi3 = vInd * 3;
			vx = afVertices[oi3 + 0];
			vy = afVertices[oi3 + 1];
			vz = afVertices[oi3 + 2];
			vInd = bigFace_vertices[oi6 + 0];
			oi3 = vInd * 3;
			vx = (vx + afVertices[oi3 + 0]) / 2;
			vy = (vy + afVertices[oi3 + 1]) / 2;
			vz = (vz + afVertices[oi3 + 2]) / 2;
			/* normalize */
			vlen = sqrtf(vx*vx + vy*vy + vz*vz);
			vx = vx / vlen;
			vy = vy / vlen;
			vz = vz / vlen;
			/* neuen vertex speichern */
			oi3 = vertexInd * 3;
			switch (BallMod) {
			case 0:
				afVertices[oi3 + 0] = vx;
				afVertices[oi3 + 1] = vy;
				afVertices[oi3 + 2] = vz;
				break;
			case 1:
				afVertices[oi3 + 0] = vx * CRUNCHY;
				afVertices[oi3 + 1] = vy * CRUNCHY;
				afVertices[oi3 + 2] = vz * CRUNCHY;
				break;
			}

			vertexInd++;
		}

		if (cv1 && cv3 && cv5) continue;

		/* sollte optimieren: können hier continue; falls kein neuer knoten definiert wurde,
		   und können teile folgender checks aussparen falls nicht alle 3 knoten neu definiert wurden */

		/* über bisher unbekannte flächen iterieren und dort die vertices auch gleich eintragen,
		falls angrenzend an dieselbe betroffene Kante */
		for (j = i + 1; j < m_iNoFacesOld; j++) {
			oj6 = j * 6;
			/* check edge 1 of this face */
			if (bigFace_vertices[oj6 + 1] == -1) {
				/* check for all 3 vertices we inserted */
				if (bigFace_vertices[oj6 + 0] == bigFace_vertices[oi6 + 0]) {
					/* check both directions: edges aren't directional! */
					if (bigFace_vertices[oj6 + 2] == bigFace_vertices[oi6 + 2])
						bigFace_vertices[oj6 + 1] = bigFace_vertices[oi6 + 1];
					else if (bigFace_vertices[oj6 + 2] == bigFace_vertices[oi6 + 4])
						bigFace_vertices[oj6 + 1] = bigFace_vertices[oi6 + 5];
				} else if (bigFace_vertices[oj6 + 0] == bigFace_vertices[oi6 + 2]) {
					/* check both directions: edges aren't directional! */
					if (bigFace_vertices[oj6 + 2] == bigFace_vertices[oi6 + 0])
						bigFace_vertices[oj6 + 1] = bigFace_vertices[oi6 + 1];
					else if (bigFace_vertices[oj6 + 2] == bigFace_vertices[oi6 + 4])
						bigFace_vertices[oj6 + 1] = bigFace_vertices[oi6 + 3];
				} else if (bigFace_vertices[oj6 + 0] == bigFace_vertices[oi6 + 4]) {
					/* check both directions: edges aren't directional! */
					if (bigFace_vertices[oj6 + 2] == bigFace_vertices[oi6 + 0])
						bigFace_vertices[oj6 + 1] = bigFace_vertices[oi6 + 5];
					else if (bigFace_vertices[oj6 + 2] == bigFace_vertices[oi6 + 2])
						bigFace_vertices[oj6 + 1] = bigFace_vertices[oi6 + 3];
				}
			}
			/* check edge 2 of this face */
			if (bigFace_vertices[oj6 + 3] == -1) {
				/* check for all 3 vertices we inserted */
				if (bigFace_vertices[oj6 + 2] == bigFace_vertices[oi6 + 2]) {
					/* check both directions: edges aren't directional! */
					if (bigFace_vertices[oj6 + 4] == bigFace_vertices[oi6 + 4])
						bigFace_vertices[oj6 + 3] = bigFace_vertices[oi6 + 3];
					else if (bigFace_vertices[oj6 + 4] == bigFace_vertices[oi6 + 0])
						bigFace_vertices[oj6 + 3] = bigFace_vertices[oi6 + 1];
				} else if (bigFace_vertices[oj6 + 2] == bigFace_vertices[oi6 + 0]) {
					/* check both directions: edges aren't directional! */
					if (bigFace_vertices[oj6 + 4] == bigFace_vertices[oi6 + 2])
						bigFace_vertices[oj6 + 3] = bigFace_vertices[oi6 + 1];
					else if (bigFace_vertices[oj6 + 4] == bigFace_vertices[oi6 + 4])
						bigFace_vertices[oj6 + 3] = bigFace_vertices[oi6 + 5];
				} else if (bigFace_vertices[oj6 + 2] == bigFace_vertices[oi6 + 4]) {
					/* check both directions: edges aren't directional! */
					if (bigFace_vertices[oj6 + 4] == bigFace_vertices[oi6 + 0])
						bigFace_vertices[oj6 + 3] = bigFace_vertices[oi6 + 5];
					else if (bigFace_vertices[oj6 + 4] == bigFace_vertices[oi6 + 2])
						bigFace_vertices[oj6 + 3] = bigFace_vertices[oi6 + 3];
				}
			}
			/* check edge 3 of this face */
			if (bigFace_vertices[oj6 + 5] == -1) {
				/* check for all 3 vertices we inserted */
				if (bigFace_vertices[oj6 + 4] == bigFace_vertices[oi6 + 4]) {
					/* check both directions: edges aren't directional! */
					if (bigFace_vertices[oj6 + 0] == bigFace_vertices[oi6 + 0])
						bigFace_vertices[oj6 + 5] = bigFace_vertices[oi6 + 5];
					else if (bigFace_vertices[oj6 + 0] == bigFace_vertices[oi6 + 2])
						bigFace_vertices[oj6 + 5] = bigFace_vertices[oi6 + 3];
				} else if (bigFace_vertices[oj6 + 4] == bigFace_vertices[oi6 + 0]) {
					/* check both directions: edges aren't directional! */
					if (bigFace_vertices[oj6 + 0] == bigFace_vertices[oi6 + 2])
						bigFace_vertices[oj6 + 5] = bigFace_vertices[oi6 + 1];
					else if (bigFace_vertices[oj6 + 0] == bigFace_vertices[oi6 + 4])
						bigFace_vertices[oj6 + 5] = bigFace_vertices[oi6 + 5];
				} else if (bigFace_vertices[oj6 + 4] == bigFace_vertices[oi6 + 2]) {
					/* check both directions: edges aren't directional! */
					if (bigFace_vertices[oj6 + 0] == bigFace_vertices[oi6 + 4])
						bigFace_vertices[oj6 + 5] = bigFace_vertices[oi6 + 3];
					else if (bigFace_vertices[oj6 + 0] == bigFace_vertices[oi6 + 0])
						bigFace_vertices[oj6 + 5] = bigFace_vertices[oi6 + 1];
				}
			}
		}
	}

	/* update # of vertices we got now */
	m_iNoVertices = vertexInd;

	/* generate new faces array from our temporary bigFaces array:
				+0			/\
				/\		   /\/\
			  +5  +1	   ````
			  /_+3_\
			+4      +2
	*/
	for (i = 0; i < m_iNoFacesOld; i++) {
		oi3 = i * 3 * 4;
		oi6 = i * 6;

		/* generate 4 faces from each big face */
		auiIndices[oi3 + 0] = bigFace_vertices[oi6 + 0];
		auiIndices[oi3 + 1] = bigFace_vertices[oi6 + 1];
		auiIndices[oi3 + 2] = bigFace_vertices[oi6 + 5];

		auiIndices[oi3 + 3] = bigFace_vertices[oi6 + 1];
		auiIndices[oi3 + 4] = bigFace_vertices[oi6 + 2];
		auiIndices[oi3 + 5] = bigFace_vertices[oi6 + 3];

		auiIndices[oi3 + 6] = bigFace_vertices[oi6 + 1];
		auiIndices[oi3 + 7] = bigFace_vertices[oi6 + 3];
		auiIndices[oi3 + 8] = bigFace_vertices[oi6 + 5];

		auiIndices[oi3 + 9] = bigFace_vertices[oi6 + 5];
		auiIndices[oi3 + 10] = bigFace_vertices[oi6 + 3];
		auiIndices[oi3 + 11] = bigFace_vertices[oi6 + 4];
	}

	/* we're now 1 refinement level better than when we started */
	refinementLevel++;
}

void RenderSceneB::DefinementStep()
{
#if 0 /* tatsächlich runterrechnen */

	/* rebuild current iss from backed up iss, while defining 1 step */	
	//int i, j;

	/* paranoia */
	if (m_iNoFaces < 4 * 4) {
		refinementLevelNew = refinementLevel;
		return;
	}

	/* transverse all faces, collapse each 4 into one */
	m_iNoFaces /= 4;



	/* we're now 1 refinement level worse than when we started */
	refinementLevel--;

#else /* neu aufbauen */

	int tmp = refinementLevelNew;
	initSettings();
	refinementLevelNew = tmp;

	/* abuse refinementStep() to just build bottom-up */
	while (refinementLevelNew > refinementLevel)
		RefinementStep();

#endif
}
