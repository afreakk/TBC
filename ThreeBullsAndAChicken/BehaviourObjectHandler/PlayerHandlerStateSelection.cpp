#include "stdafx.h"
#include "PlayerHandlerStateSelection.h"
#include "../ModelBehaviour/ModelHandlerMutant.h"
#include "../Containers/MutantContainer.h"
#include "../Stats/GlobalVariables.h"
PlayerHandlerStateSelection::PlayerHandlerStateSelection(Player* player) 
: m_selectionHandler(player->getNode()->getPosition())
, HandlerState(PLAYER_HANDLER_STATE::SELECTION)
, m_player(player)
, m_selectionState{ new PlayerSelectionState() }
{
	m_player->setState(m_selectionState.get());
	GlobalVariables::getSingleton().setSpeed(1.0 / 20.0);
}


PlayerHandlerStateSelection::~PlayerHandlerStateSelection()
{
	GlobalVariables::getSingleton().setSpeed(1.0);
	for (auto idx:m_attackList)
		static_cast<ModelHandlerMutant&>(MutantContainer::getSingleton().getMutants()[idx]->getModelHandler()).getNumer().unMarkNumber();
}

void PlayerHandlerStateSelection::update()
{
	m_selectionHandler.updateSelected();
}
void PlayerHandlerStateSelection::keyPressed(const OIS::KeyEvent& e)
{
	m_selectionHandler.handleIndex(e);
	handleSelection(e);
}
void PlayerHandlerStateSelection::keyReleased(const OIS::KeyEvent& e)
{

}
void PlayerHandlerStateSelection::handleSelection(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KC_SPACE)
		pushBackSelected();
	if (e.key == OIS::KC_RETURN && m_attackList.size()>0)
		goLerp();
}
std::vector<unsigned> PlayerHandlerStateSelection::getAttackList() const
{
	return m_attackList;
}
void PlayerHandlerStateSelection::goLerp()
{
	m_state = PLAYER_HANDLER_STATE::LERP;
}
void PlayerHandlerStateSelection::pushBackSelected()
{
	for (const auto& atk : m_attackList)
	{
		if (m_selectionHandler.getSelected() == atk)
			return;
	}
	m_attackList.push_back(m_selectionHandler.getSelected());
	static_cast<ModelHandlerMutant&>(MutantContainer::getSingleton().getMutants()[m_attackList[m_attackList.size() - 1]]->getModelHandler()).getNumer().markAs(m_attackList.size());
	m_selectionHandler.addLine();
}
