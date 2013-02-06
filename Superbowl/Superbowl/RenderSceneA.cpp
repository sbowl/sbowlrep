/* extra stuff from dooda */
#include "RenderSceneA.h"
#include "Settings.h"

RenderSceneA::RenderSceneA()
  : m_iWidth( 800 )
  , m_iHeight( 600 )
  , m_fHeightAngle( 0.4f )
  , m_dNearDistance( 5.0f )
  , m_dFarDistance( 15.0f )
  , m_fRot( 0.0f )
  , m_fTurnX ( 0.0f)
  , m_fTurnY (0.0f)
  , m_bRendered (false)
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
