/* extra stuff from dooda */
#include "RenderSceneA.h"
#include "Settings.h"

RenderSceneA::RenderSceneA()
  : m_iNoVerticesNew (0)
  , m_iNoFacesNew ( 0 )
{}

void RenderSceneA::Refinement()
{
	int m_iNoVerticesOld;
	float afVertices[NO_VERTICES_MAX*3];
	int auiIndices[NO_VERTICES_MAX];
	m_iNoVerticesOld = m_iNoVertices;
	//alte arrays kopieren
	//
}
