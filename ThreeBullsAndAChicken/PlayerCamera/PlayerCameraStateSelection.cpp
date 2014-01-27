#include "stdafx.h"
#include "PlayerCameraStateSelection.h"
#include "../Enemy/EnemyHandler.h"

PlayerCameraStateSelection::PlayerCameraStateSelection() : m_mutants(EnemyHandler::getSingleton().getMutantHandlers()), m_camera(OgreCore::getSingleton().getCamera())
{
}


PlayerCameraStateSelection::~PlayerCameraStateSelection()
{
}

void PlayerCameraStateSelection::update()
{
	for (const auto& mutant : m_mutants)
	{
		if (mutant->getMutant().getModelHandler().isSelected())
		{
			m_camera->lookAt(mutant->getMutant().getModelHandler().getNode()->getPosition());
		}
	}

}
