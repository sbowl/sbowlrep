/* extra stuff from doodb */
#include "RenderSceneB.h"
#include "Settings.h"

RenderSceneB::RenderSceneB()
{
}

void RenderSceneB::Refinement()
{
	if (refinementLevelNew < 0) refinementLevelNew = 0;
	if (refinementLevelNew > 10) refinementLevelNew = 10;

	while (refinementLevelNew > refinementLevel)
		RefinementStep();
}

void RenderSceneB::RefinementStep()
{
	int i;
	
#if 0 /* we're gonna rebuild the arrays from scratch? */
	
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
	
	int m_iNoFacesOld = m_iNoFaces;

	/* transverse all faces, turn each one into 4 new ones */
	for (i = 0; i < m_iNoFacesOld*3; i++) {
		/* paranoia */
		if (m_iNoFaces + 3 > NO_FACES_MAX) break;

		/* insert 3 new faces (ie split up 1 old face into 4 faces) */
		m_iNoFaces += 3;

		//auiIndices[i]
	}

#endif

	/* we're now 1 refinement level better than when we started */
	refinementLevel++;
}
