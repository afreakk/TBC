#include "stdafx.h"
#include "DetonateWeaponHitTest.h"
#include "PlayerContainer.h"
#include "Player.h"
#include "MutantContainer.h"
#include "PlayerGlobalStats.h"
#include "ModelHandlerPlayer.h"


bool DetonateWeaponHitTest::detonate(Ogre::Node* m_node, const Ogre::Real& radius, bool isBall)
{
    //player
	bool didHit = false;
	Player * player = PlayerContainer::getSingleton().getPlayer();
	const Vector3& nodePos = isBall ? m_node->_getDerivedPosition() : m_node->getPosition();
	if (!static_cast<ModelHandlerPlayer&>(player->getModelHandler()).isTeleporting())
	{
		Real dist = player->getNode()->getPosition().distance(nodePos);
		cout << dist << endl;
		if (dist < radius)
		{
			didHit = true;
			if ( isBall)
                player->getModelHandler().freeze();
			else
                PlayerGlobalStats::getSingleton().modifyHealth(-50);
		}
          
	}
    //mutants
	for (auto itt : MutantContainer::getSingleton().getMutantIt())
	{
        Node* iMutantNode = itt->getNode();
        if (iMutantNode == (m_node->getParent()))
            continue;
		if (iMutantNode->getPosition().distance(nodePos) < radius)
		{
			didHit = true;
			if (isBall)
				itt->getModelHandler().freeze();
			else
			    MutantContainer::getSingleton().killMutant(itt->getNode()->getName());
		}
    }
	return didHit;
}
