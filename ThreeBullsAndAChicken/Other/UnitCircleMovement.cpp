#include "stdafx.h"
#include "UnitCircleMovement.h"
using namespace Ogre;
Ogre::Vector3 UnitCircleMovement::posFromR(NormalPosition p)
{
	return Ogre::Vector3(Ogre::Math::Sin(p.r)*p.d,p.h,Ogre::Math::Cos(p.r)*p.d);
}
void UnitCircleMovement::normalSetPosition(Ogre::SceneNode* node, NormalPosition p)
{
	node->setPosition(posFromR(p));
}
void UnitCircleMovement::normalSetDirection(Ogre::SceneNode* node, NormalPosition p, NormalDirection direction)
{
	switch (direction)
	{
	case NormalDirection::Left:
		p.r += Ogre::Math::PI/12.0;
		break;
	case NormalDirection::Right:
		p.r -= Ogre::Math::PI/12.0;
		break;
	default:
		return;
		break;
	}
	node->lookAt(posFromR(p),Ogre::Node::TransformSpace::TS_WORLD);
}

void keepWithinMax(Real* d)
{
	while (*d > Math::PI*2.0)
		*d -= Math::PI*2.0;
	while (*d < 0.0)
		*d += Math::PI*2.0;
}
#include <math.h>
unsigned energyCostOf(NormalPosition a, NormalPosition b)
{
	return static_cast<unsigned>(round( Ogre::Math::Abs(a.r - b.r)*100.0 ));
}