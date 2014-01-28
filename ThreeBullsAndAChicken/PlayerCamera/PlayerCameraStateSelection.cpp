#include "stdafx.h"
#include "PlayerCameraStateSelection.h"
#include "../Enemy/EnemyHandler.h"
#include "../Enemy/MutantModelHandler.h"
PlayerCameraStateSelection::PlayerCameraStateSelection() : m_mutants(EnemyHandler::getSingleton().getMutants()), m_camera(OgreCore::getSingleton().getCamera())
{
}


PlayerCameraStateSelection::~PlayerCameraStateSelection()
{
}

void PlayerCameraStateSelection::update()
{
	for (const auto& mutant : m_mutants)
	{
		MutantModelHandler& mutantModelHandler = static_cast<MutantModelHandler&>(mutant->getModelHandler());
		if (mutantModelHandler.isSelected())
		{
			m_camera->lookAt(mutant->getModelHandler().getNode()->getPosition());
		}
	}

}
