#include "stdafx.h"
#include "Tutorial.h"
#include "Player.h"
#include "GlobalVariables.h"
#include "PlayerContainer.h"
#include "ModelHandler.h"
#include "CoreCompositor.h"
#include "OISCore.h"
#include "MainUpdate.h"
#include "OISHelp.h"
#include "MutantContainer.h"
TutorialScript Tutorial::m_tooltipIdx = TutorialScript::even_one;
Tutorial::Tutorial()
: m_player(PlayerContainer::getSingleton().getPlayer())
, m_enterReleased(true)
, m_compositorOn(false)
, m_pauseTimer(0.0f)
, m_mutantSize(0)
, m_canSpawn(false)
, m_changeLevel(false)
, m_music("music/tutorial", "_intro", "_loop", "_loop")
, m_keyToClick(OIS::KeyCode::KC_0)
{
	m_tooltipIdx = TutorialScript::even_one;
	fillJustPassedKilledCheckpoints();
	m_music.begin();
}


Tutorial::~Tutorial()
{
}

void Tutorial::fillJustPassedKilledCheckpoints()
{
	m_justPassedKilledCheckpoints.push_back(TutorialScript::pauseKillMutant);
	m_justPassedKilledCheckpoints.push_back(TutorialScript::even_fireball_end);
	m_justPassedKilledCheckpoints.push_back(TutorialScript::even_frostbolt_wait_two);
    m_justPassedKilledCheckpoints.push_back(TutorialScript::suicide_five);
    //int cast value order
}
TutorialScript Tutorial::getTooltipIdx()
{
	return m_tooltipIdx;
}

void Tutorial::setTooltipIdx(TutorialScript newIdx) 
{
	m_tooltipIdx = newIdx;
}
void Tutorial::update()
{
	m_music.loop();
	m_canSpawn = false;
	TutorialScript oldTooltipIdx = m_tooltipIdx;
	if (m_enterReleased)
	{
        switch (m_tooltipIdx)
        {
		case TutorialScript::debug:
			genericPress(TutorialScript::slowmo_allKilled_four);
            showTooltipSlowMotion(m_player->getModelHandler(), "debug..");
            break;
        case TutorialScript::even_one:
			genericPress(TutorialScript::even_two);
            showTooltipSlowMotion(m_player->getModelHandler(), "It looks like the mission rests on my shoulders.");
            break;
        case TutorialScript::even_two:
			genericPress(TutorialScript::even_three);
            showTooltipSlowMotion(m_player->getModelHandler(), "I could never forgive myself if I were to fail my\ncountry and not least my teammates now!");
            break;
        case TutorialScript::even_three:
			genericPress(TutorialScript::mov_even_one);
            showTooltipSlowMotion(m_player->getModelHandler(), "So I better get\nused to fighting\nin this suit again. \nIt’s been a long time since I\nused it on a mission.");
            break;
		case TutorialScript::mov_even_one:
			genericPress(TutorialScript::tutorial_pause_one,OIS::KC_A);
			genericPress(TutorialScript::tutorial_pause_one,OIS::KC_D);
            showTooltipSlowMotion(m_player->getModelHandler(), "I can walk forwards and backwards\nusing the D and A keys.");
            break;
		case TutorialScript::tutorial_pause_one:
			if (pauseTimer())
				m_tooltipIdx = TutorialScript::tumble_even;
			hideTooltip(m_player->getModelHandler());
			break;
		case TutorialScript::tumble_even:
			genericPress(TutorialScript::tutorial_pause_two,OIS::KC_S);
			genericPress(TutorialScript::tutorial_pause_two,OIS::KC_W);
            showTooltipSlowMotion(m_player->getModelHandler(), "By pressing W or S\nI can jump either left or right\nin the hallway here.");
			break;
		case TutorialScript::tutorial_pause_two:
			if (mutantSpawned())
				m_tooltipIdx = TutorialScript::tutorial_pause_two_pt_two;
			hideTooltip(m_player->getModelHandler());
			break;
		case TutorialScript::tutorial_pause_two_pt_two:
			if (mutantIsClose())
				m_tooltipIdx = TutorialScript::even_attack_one;
			break;
		case TutorialScript::even_attack_one:
			genericPress(TutorialScript::even_attack_two);
            showTooltipSlowMotion(m_player->getModelHandler(), "Slicing up these mutants won’t be hard with my sword!");
			break;
		case TutorialScript::even_attack_two:
			genericPress(TutorialScript::even_attack_four,OIS::KC_SPACE);
            showTooltipSlowMotion(m_player->getModelHandler(), "I’ll just press space_bar!");
            break;
            //skip One enum
		case TutorialScript::even_attack_four:
			hideTooltip(m_player->getModelHandler());
			if (mutantDied())
				m_tooltipIdx = TutorialScript::pauseKillMutant;
			break;
		case TutorialScript::pauseKillMutant:
			if (pauseTimer())
				m_tooltipIdx = TutorialScript::even_feels_energy;
			break;
		case TutorialScript::even_feels_energy:
			genericPress(TutorialScript::even_feels_two);
            showTooltipSlowMotion(m_player->getModelHandler(), "I can feel the energy flowing into me after defeating that monster.");
			break;
		case TutorialScript::even_feels_two:
			genericPress(TutorialScript::even_teleport);
            showTooltipSlowMotion(m_player->getModelHandler(), "The more monsters I beat, the more energy I can \nharvest into my powersuit.");
			break;
		case TutorialScript::even_teleport:
			genericPress(TutorialScript::even_teleport_two);
            showTooltipSlowMotion(m_player->getModelHandler(), "By spending a small amount of energy I \ncan teleport short distances.");
			break;
		case TutorialScript::even_teleport_two:
			genericPress(TutorialScript::even_teleportBreak, OIS::KeyCode::KC_E);
            showTooltipSlowMotion(m_player->getModelHandler(), "Press e to teleport");
			break;
		case TutorialScript::even_teleportBreak:
			hideTooltip(m_player->getModelHandler());
			if (mutantSpawned())
				m_tooltipIdx = TutorialScript::even_fireballWait;
			break;
		case TutorialScript::even_fireballWait:
			if (mutantIsClose())
				m_tooltipIdx = TutorialScript::even_fireball_one;
			break;
		case TutorialScript::even_fireball_one:
			genericPress(TutorialScript::even_fireball_two);
			showTooltipSlowMotion(m_player->getModelHandler(), "Looks like this guy isn’t a pushover like that last one.");
			break;
		case TutorialScript::even_fireball_two:
			genericPress(TutorialScript::even_fireball_three);
			showTooltipSlowMotion(m_player->getModelHandler(), "According to the mission briefing it \nshould be one of those Firebreathers.");
			break;
		case TutorialScript::even_fireball_three:
			genericPress(TutorialScript::even_fireball_four);
			showTooltipSlowMotion(m_player->getModelHandler(), "I should dodge his fireballs while moving \ntowards him and go for the kill!");
			break;
		case TutorialScript::even_fireball_four:
			genericPress(TutorialScript::even_fireball_waitForKill);
			showTooltipSlowMotion(m_player->getModelHandler(), "When fighting multiple monsters, \ntricking them into hitting each other is the key to an easy win!");
			break;
		case TutorialScript::even_fireball_waitForKill:
			hideTooltip(m_player->getModelHandler());
			if (mutantDied())
				m_tooltipIdx = TutorialScript::even_fireball_end;
			break;
		case TutorialScript::even_fireball_end:
			if (pauseTimer())
				m_tooltipIdx = TutorialScript::even_fireball_end_pt_two;
			break;
		case TutorialScript::even_fireball_end_pt_two:
			genericPress(TutorialScript::even_fireball_end_pt_three);
			showTooltipSlowMotion(m_player->getModelHandler(), "That wasn’t too hard! These guys will be extinct \nbefore you can say brown cheese!");
			break;
		case TutorialScript::even_fireball_end_pt_three:
			hideTooltip(m_player->getModelHandler());
			if (mutantSpawned())
				m_tooltipIdx = TutorialScript::even_frostbolt_wait_root;
			break;
		case TutorialScript::even_frostbolt_wait_root:
			if (mutantIsClose())
				m_tooltipIdx = TutorialScript::even_frostbolt_one;
			break;
		case TutorialScript::even_frostbolt_one:
			genericPress(TutorialScript::even_frostbolt_two);
			showTooltipSlowMotion(m_player->getModelHandler(), "If memory serves me right, this is a Freezer.");
			break;
		case TutorialScript::even_frostbolt_two:
			genericPress(TutorialScript::even_frostbolt_killListen);
			showTooltipSlowMotion(m_player->getModelHandler(), "Their frostbolts will slow down my movements.");
			break;
		case TutorialScript::even_frostbolt_killListen:
			hideTooltip(m_player->getModelHandler());
			if (mutantDied())
				m_tooltipIdx = TutorialScript::even_frostbolt_wait_two;
			break;
		case TutorialScript::even_frostbolt_wait_two:
			if (pauseTimer())
				m_tooltipIdx = TutorialScript::even_frostbolt_end;
			break;
		case TutorialScript::even_frostbolt_end:
			genericPress(TutorialScript::suicide_listen);
			showTooltipSlowMotion(m_player->getModelHandler(), "See ya!");
			break;
		case TutorialScript::suicide_listen:
			hideTooltip(m_player->getModelHandler());
			if (mutantSpawned())
				m_tooltipIdx = TutorialScript::suicide_wait;
			break;
		case TutorialScript::suicide_wait:
			if (mutantIsClose())
				m_tooltipIdx = TutorialScript::suicide_one;
			break;
		case TutorialScript::suicide_one:
			genericPress(TutorialScript::suicide_two);
			showTooltipSlowMotion(m_player->getModelHandler(), "This guy doesn’t look too good. That’s an Exploder!");
			break;
		case TutorialScript::suicide_two:
			genericPress(TutorialScript::suicide_three);
			showTooltipSlowMotion(m_player->getModelHandler(), "The radiation have been wreaking havoc on \ntheir minds and their bodies for too long.");
			break;
		case TutorialScript::suicide_three:
			genericPress(TutorialScript::suicide_four);
			showTooltipSlowMotion(m_player->getModelHandler(), "Their so unstable they could explode any minute!");
			break;
		case TutorialScript::suicide_four:
			genericPress(TutorialScript::suicide_listen_two);
			showTooltipSlowMotion(m_player->getModelHandler(), "Better stay away from it until it’s out of its misery.");
			break;
		case TutorialScript::suicide_listen_two:
			hideTooltip(m_player->getModelHandler());
			if (mutantDied())
				m_tooltipIdx = TutorialScript::suicide_five;
			break;
		case TutorialScript::suicide_five:
			if (pauseTimer())
				m_tooltipIdx = TutorialScript::suicide_six;
			break;
		case TutorialScript::suicide_six:
			genericPress(TutorialScript::slowmo_one);
			showTooltipSlowMotion(m_player->getModelHandler(), "Phew. Hope I don’t have to meet \ntoo many of those bastards.");
			break;
		case TutorialScript::slowmo_one:
			if (mutantSpawned())
				m_tooltipIdx = TutorialScript::slowmo_two;
			hideTooltip(m_player->getModelHandler());
			break;
		case TutorialScript::slowmo_two:
			genericPress(TutorialScript::slowmo_three);
			showTooltipSlowMotion(m_player->getModelHandler(), "My powersuit is overflowing with power!");
			break;
		case TutorialScript::slowmo_three:
			if(OISCore::getSingleton().getKeyboard()->isModifierDown(OIS::Keyboard::Modifier::Shift))
			    genericPress(TutorialScript::slowmo_four,OIS::KC_SPACE);
			showTooltipSlowMotion(m_player->getModelHandler(), "With this much energy I can enter a state of \nsuperhuman senses by pressing shift+space.");
			break;
		case TutorialScript::slowmo_four:
			if (pauseTimer())
				m_tooltipIdx = TutorialScript::slowmo_five;
			hideTooltip(m_player->getModelHandler());
			break;
		case TutorialScript::slowmo_five:
			genericPress(TutorialScript::slowmo_six);
			showTooltipSlowMotion(m_player->getModelHandler(), "I can then focus on picking my next targets and \neasily take them out with super speed!");
			break;
		case TutorialScript::slowmo_six:
			genericPress(TutorialScript::slowmo_seven);
			showTooltipSlowMotion(m_player->getModelHandler(), "I’ll test it out on those mutants over there!");
			break;
		case TutorialScript::slowmo_seven:
			hideTooltip(m_player->getModelHandler());
			if (allKilled())
				m_tooltipIdx = TutorialScript::slowmo_allKilled;
			break;
		case TutorialScript::slowmo_allKilled:
			genericPress(TutorialScript::slowmo_allKilled_two);
			showTooltipSlowMotion(m_player->getModelHandler(), "Easy peasy, lemon squeezy!");
			break;
		case TutorialScript::slowmo_allKilled_two:
			genericPress(TutorialScript::slowmo_allKilled_three);
			showTooltipSlowMotion(m_player->getModelHandler(), "I should get out of this lab and follow the \nmutants trail into the forest.");
			break;
		case TutorialScript::slowmo_allKilled_three:
			genericPress(TutorialScript::slowmo_allKilled_four);
			showTooltipSlowMotion(m_player->getModelHandler(), "Guys! I won’t let your deaths be in vain!");
			break;
		case TutorialScript::slowmo_allKilled_four:
			hideTooltip(m_player->getModelHandler());
			if (pauseTimer(5.0f))
				m_tooltipIdx = TutorialScript::change_level;
			break;
		case TutorialScript::change_level:
			m_changeLevel = true;
			break;
        default:
            break;
        }
	}
	if (m_tooltipIdx == oldTooltipIdx && mutantDied() && m_tooltipIdx < m_justPassedKilledCheckpoints.back())
		m_tooltipIdx = getNearestKilledCheckpointIdx();

	if (!OISCore::getSingleton().getKeyboard()->isKeyDown(OIS::KeyCode::KC_RETURN))
		m_enterReleased = true;
}
bool Tutorial::plzChangeLevel()
{
	return m_changeLevel;
}
bool Tutorial::allKilled()
{
	return MutantContainer::getSingleton().getMutantIt().size() == 0;
}
TutorialScript Tutorial::getNearestKilledCheckpointIdx()
{
	int currentIdx = static_cast<int>(m_tooltipIdx);
	int i = 0;
	while (currentIdx > static_cast<int>(m_justPassedKilledCheckpoints[i]))
		i++;
	return m_justPassedKilledCheckpoints[i];
}
bool Tutorial::canSpawn()
{
	return m_canSpawn;
}
bool Tutorial::mutantIsClose()
{
	return float_compare(MutantContainer::getSingleton().getMutantIt().back()->getPolarCoordinates().theta, m_player->getPolarCoordinates().theta, 0.3f);
}
bool Tutorial::mutantSpawned()
{
	auto totalMutants = MutantContainer::getSingleton().getMutantIt().size();
	m_canSpawn = true;
	if (m_mutantSize < totalMutants)
	{
	    m_mutantSize = totalMutants;
		return true;
	}
    m_mutantSize = totalMutants;
	return false;
}
bool Tutorial::mutantDied()
{
	auto totalMutants = MutantContainer::getSingleton().getMutantIt().size();
	if (m_mutantSize > totalMutants)
	{
	    m_mutantSize = totalMutants;
		return true;
	}
    m_mutantSize = totalMutants;
	return false;
}
void Tutorial::genericPress(TutorialScript changeTo, OIS::KeyCode keyCode)
{
	m_keyToClick = keyCode;
    if (OISCore::getSingleton().getKeyboard()->isKeyDown(keyCode))
    {
        m_tooltipIdx = changeTo;
        enterPressed();
    }
}
bool Tutorial::pauseTimer(Ogre::Real time)
{
	m_pauseTimer += MainUpdate::getSingleton().getDeltaTime();
	if (m_pauseTimer > time)
	{
		m_pauseTimer = 0.0f;
		return true;
	}
	else
		return false;
}
void Tutorial::enterPressed()
{
	m_enterReleased = false;
}

void Tutorial::hideTooltip(ModelHandler& model)
{
	if (m_currentMsg != "")
	{
        m_currentMsg = "";
        model.hideTooltip();
        setCompositor(false);
        setSlowmotion(false);
	}
}
void Tutorial::showTooltipNormie(ModelHandler& model, const  std::string& msg)
{
	if (m_currentMsg != msg || !float_compare(GlobalVariables::getSingleton().getSpeed(), 1.0f,0.1f))
	{
        m_currentMsg = msg;
		setCompositor(true);
		setSlowmotion(false);
        model.tooltip(m_currentMsg, OISHelp::keyCodeToString( m_keyToClick ));
	}
}
void Tutorial::showTooltipSlowMotion(ModelHandler& model, const std::string& msg)
{
	if (m_currentMsg != msg || !float_compare(GlobalVariables::getSingleton().getSpeed(), 0.0f,0.1f))
	{
        m_currentMsg = msg;
		setCompositor(true);
		setSlowmotion(true);
        model.tooltip(m_currentMsg, OISHelp::keyCodeToString( m_keyToClick ) );
	}
}
///
void Tutorial::setCompositor(bool enabled)
{
/*	if (m_compositorOn != enabled)
	{
        CoreCompositor::getSingleton().getSingleton().tooltipComp(enabled);
		m_compositorOn = enabled;
	}
    
    */
}
void Tutorial::setSlowmotion(bool slowMotion)
{
	if (slowMotion)
        GlobalVariables::getSingleton().setSpeed(0.1f);
	else
        GlobalVariables::getSingleton().setSpeed(1.0f);
}
