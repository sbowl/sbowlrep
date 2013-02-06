/* extra stuff from dooda */
#include "RenderSceneA.h"

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
	int auiIndices[1000];
	m_iNoVerticesOld = m_iNoVertices;
}
