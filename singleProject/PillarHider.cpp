#include "stdafx.h"
#include "PillarHider.h"
#include "PlayerContainer.h"
#include "UnitCircleMovement.h"
#include "Player.h"
PillarHider::PillarHider(Ogre::SceneNode* envnode)
: m_environmentNode(envnode)
{
}


PillarHider::~PillarHider()
{
}

void PillarHider::update()
{
	std::vector<string> meshNames = {"mid_Pillar", "endPillar"};
	auto rootItterator = m_environmentNode->getChildIterator();
	while (rootItterator.hasMoreElements())
	{
		auto n = rootItterator.getNext();
		auto childNodeItt = n->getChildIterator();
		while (childNodeItt.hasMoreElements())
		{
            auto node = childNodeItt.getNext();
			for (auto meshName : meshNames)
			{
                if (node->getName().compare(0,meshName.length(),meshName) == 0)
                {
                    auto envObjs = static_cast<SceneNode*>(node)->getAttachedObjectIterator();
                    if (envObjs.hasMoreElements())
                    {

                        auto roofPipeEnt = envObjs.getNext();
                        PolarCoordinates polarPos = UnitCircleMovement::PolarFromVector(node->_getDerivedPosition());
						if (float_compare(polarPos.theta, PlayerContainer::getSingleton().getPlayer()->getPolarCoordinates().theta, 0.2f))
							static_cast<Entity*>(roofPipeEnt)->setVisible(false);
						else
							static_cast<Entity*>(roofPipeEnt)->setVisible(true);
                    }
                }
			}

		}
	}
}