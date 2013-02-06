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
	int auiIndicesOld[NO_VERTICES_MAX*3];

	/* backup current indexed shape set */
	for (i = 0; i < NO_VERTICES_MAX*3; i++) {
		afVerticesOld[i] = afVertices[i];
		auiIndicesOld[i = auiIndices[i];
	}
	
	/* reset current indexed shape set */
	m_iNoVertices = 0;
	m_iNoFaces = 0;

	/* rebuild current iss from backed up iss, while refining 1 step */

#else /* just append additional stuff to the arrays */
	


#endif

	/* we're now 1 refinement level better than when we started */
	refinementLevel++;
}
