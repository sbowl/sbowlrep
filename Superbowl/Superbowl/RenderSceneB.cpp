/* extra stuff from doodb */
#include "RenderSceneB.h"

RenderSceneB::RenderSceneB()
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

void RenderSceneB::Refinement()
{

	//std::vector<int> v;
 //   int i;
 //
 //   for (i=0; i<100; ++i) {
 //       v.push_back(i); // F�gt i ans Ende von v an.
 //       ++v[i]; // v[i] muss bereits existieren.
	//}
	//printf("%d", v[2]);
}
