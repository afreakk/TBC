#include "stdafx.h"
#include "Tutorial.h"
#include "Player.h"
#include "GlobalVariables.h"
#include "PlayerContainer.h"
#include "ModelHandler.h"
#include "CoreCompositor.h"
#include "OISCore.h"
#include "MainUpdate.h"
#include "MutantContainer.h"

Tutorial::Tutorial()
: m_player(PlayerContainer::getSingleton().getPlayer())
, m_tooltipIdx(TutorialScript::even_one/*TutorialScript::debug*/)
, m_enterReleased(true)
, m_compositorOn(false)
, m_pauseTimer(0.0f)
, m_mutantSize(0)
, m_canSpawn(false)
, m_changeLevel(false)
, m_music("music/tutorial")
{
}


Tutorial::~Tutorial()
{
}

void Tutorial::update()
{
	m_music.update();
	m_canSpawn = false;
	if (m_enterReleased)
	{
        switch (m_tooltipIdx)
        {
		case TutorialScript::debug:
            showTooltipSlowMotion(m_player->getModelHandler(), "debug..");
			genericPress(TutorialScript::slowmo_allKilled_four);
            break;
        case TutorialScript::even_one:
            showTooltipSlowMotion(m_player->getModelHandler(), "It looks like the mission rests on my shoulders.");
			genericPress(TutorialScript::even_two);
            break;
        case TutorialScript::even_two:
            showTooltipSlowMotion(m_player->getModelHandler(), "I could never forgive myself if I were to fail my\ncountry and not least my teammates now!");
			genericPress(TutorialScript::even_three);
            break;
        case TutorialScript::even_three:
            showTooltipSlowMotion(m_player->getModelHandler(), "So I better get\nused to fighting\nin this suit again. \nIt’s been a long time since I\nused it on a mission.");
			genericPress(TutorialScript::mov_even_one);
            break;
		case TutorialScript::mov_even_one:
            showTooltipSlowMotion(m_player->getModelHandler(), "I can walk forwards and backwards\nusing the D and A keys.");
			genericPress(TutorialScript::tutorial_pause_one,OIS::KC_A);
			genericPress(TutorialScript::tutorial_pause_one,OIS::KC_D);
            break;
		case TutorialScript::tutorial_pause_one:
			if (pauseTimer())
				m_tooltipIdx = TutorialScript::tumble_even;
			hideTooltip(m_player->getModelHandler());
			break;
		case TutorialScript::tumble_even:
            showTooltipSlowMotion(m_player->getModelHandler(), "By pressing W or S\nI can jump either left or right\nin the hallway here.");
			genericPress(TutorialScript::tutorial_pause_two,OIS::KC_S);
			genericPress(TutorialScript::tutorial_pause_two,OIS::KC_W);
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
            showTooltipSlowMotion(m_player->getModelHandler(), "Slicing up these mutants won’t be hard with my sword!");
			genericPress(TutorialScript::even_attack_two);
			break;
		case TutorialScript::even_attack_two:
            showTooltipSlowMotion(m_player->getModelHandler(), "I’ll just press space_bar!");
			genericPress(TutorialScript::even_attack_four);
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
            showTooltipSlowMotion(m_player->getModelHandler(), "I can feel the energy flowing into me after defeating that monster.");
			genericPress(TutorialScript::even_feels_two);
			break;
		case TutorialScript::even_feels_two:
            showTooltipSlowMotion(m_player->getModelHandler(), "The more monsters I beat, the more energy I can harvest into my powersuit.");
			genericPress(TutorialScript::even_teleport);
			break;
		case TutorialScript::even_teleport:
            showTooltipSlowMotion(m_player->getModelHandler(), "By spending a small amount of energy I can teleport short distances.");
			genericPress(TutorialScript::even_teleport_two);
			break;
		case TutorialScript::even_teleport_two:
            showTooltipSlowMotion(m_player->getModelHandler(), "Press e to teleport");
			genericPress(TutorialScript::even_teleportBreak, OIS::KeyCode::KC_E);
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
			showTooltipSlowMotion(m_player->getModelHandler(), "Looks like this guy isn’t a pushover like that last one.");
			genericPress(TutorialScript::even_fireball_two);
			break;
		case TutorialScript::even_fireball_two:
			showTooltipSlowMotion(m_player->getModelHandler(), "According to the mission briefing it should be one of those Firebreathers.");
			genericPress(TutorialScript::even_fireball_three);
			break;
		case TutorialScript::even_fireball_three:
			showTooltipSlowMotion(m_player->getModelHandler(), "I should dodge his fireballs while moving towards him and go for the kill!");
			genericPress(TutorialScript::even_fireball_four);
			break;
		case TutorialScript::even_fireball_four:
			showTooltipSlowMotion(m_player->getModelHandler(), "When fighting multiple monsters, \ntricking them into hitting each other is the key to an easy win!");
			genericPress(TutorialScript::even_fireball_waitForKill);
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
			showTooltipSlowMotion(m_player->getModelHandler(), "That wasn’t too hard! These guys will be extinct before you can say brown cheese!");
			genericPress(TutorialScript::even_fireball_end_pt_three);
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
			showTooltipSlowMotion(m_player->getModelHandler(), "If memory serves me right, this is a Freezer.");
			genericPress(TutorialScript::even_frostbolt_two);
			break;
		case TutorialScript::even_frostbolt_two:
			showTooltipSlowMotion(m_player->getModelHandler(), "Their frostbolts will slow down my movements.");
			genericPress(TutorialScript::even_frostbolt_killListen);
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
			showTooltipSlowMotion(m_player->getModelHandler(), "See ya!");
			genericPress(TutorialScript::suicide_listen);
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
			showTooltipSlowMotion(m_player->getModelHandler(), "This guy doesn’t look too good. That’s an Exploder!");
			genericPress(TutorialScript::suicide_two);
			break;
		case TutorialScript::suicide_two:
			showTooltipSlowMotion(m_player->getModelHandler(), "The radiation have been wreaking havoc on \ntheir minds and their bodies for too long.");
			genericPress(TutorialScript::suicide_three);
			break;
		case TutorialScript::suicide_three:
			showTooltipSlowMotion(m_player->getModelHandler(), "Their so unstable they could explode any minute!");
			genericPress(TutorialScript::suicide_four);
			break;
		case TutorialScript::suicide_four:
			showTooltipSlowMotion(m_player->getModelHandler(), "Better stay away from it until it’s out of its misery.");
			genericPress(TutorialScript::suicide_listen_two);
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
			showTooltipSlowMotion(m_player->getModelHandler(), "Phew. Hope I don’t have to meet too many of those bastards.");
			genericPress(TutorialScript::slowmo_one);
			break;
		case TutorialScript::slowmo_one:
			if (mutantSpawned())
				m_tooltipIdx = TutorialScript::slowmo_two;
			hideTooltip(m_player->getModelHandler());
			break;
		case TutorialScript::slowmo_two:
			showTooltipSlowMotion(m_player->getModelHandler(), "My powersuit is overflowing with power!");
			genericPress(TutorialScript::slowmo_three);
			break;
		case TutorialScript::slowmo_three:
			showTooltipSlowMotion(m_player->getModelHandler(), "With this much energy I can enter a state of superhuman senses by pressing shift+space.");
			if(OISCore::getSingleton().getKeyboard()->isModifierDown(OIS::Keyboard::Modifier::Shift))
			    genericPress(TutorialScript::slowmo_four,OIS::KC_SPACE);
			break;
		case TutorialScript::slowmo_four:
			if (pauseTimer())
				m_tooltipIdx = TutorialScript::slowmo_five;
			hideTooltip(m_player->getModelHandler());
			break;
		case TutorialScript::slowmo_five:
			showTooltipSlowMotion(m_player->getModelHandler(), "I can then focus on picking my next targets and easily take them out with super speed!");
			genericPress(TutorialScript::slowmo_six);
			break;
		case TutorialScript::slowmo_six:
			showTooltipSlowMotion(m_player->getModelHandler(), "I’ll test it out on those mutants over there!");
			genericPress(TutorialScript::slowmo_seven);
			break;
		case TutorialScript::slowmo_seven:
			hideTooltip(m_player->getModelHandler());
			if (allKilled())
				m_tooltipIdx = TutorialScript::slowmo_allKilled;
			break;
		case TutorialScript::slowmo_allKilled:
			showTooltipSlowMotion(m_player->getModelHandler(), "Easy peasy, lemon squeezy!");
			genericPress(TutorialScript::slowmo_allKilled_two);
			break;
		case TutorialScript::slowmo_allKilled_two:
			showTooltipSlowMotion(m_player->getModelHandler(), "I should get out of this lab and follow the mutants trail into the forest.");
			genericPress(TutorialScript::slowmo_allKilled_three);
			break;
		case TutorialScript::slowmo_allKilled_three:
			showTooltipSlowMotion(m_player->getModelHandler(), "Guys! I won’t let your deaths be in vain!");
			genericPress(TutorialScript::slowmo_allKilled_four);
			break;
		case TutorialScript::slowmo_allKilled_four:
			hideTooltip(m_player->getModelHandler());
			if (pauseTimer())
				m_tooltipIdx = TutorialScript::change_level;
			break;
		case TutorialScript::change_level:
			m_changeLevel = true;
			break;
        default:
            break;
        }
	}
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
bool Tutorial::canSpawn()
{
	return m_canSpawn;
}
bool Tutorial::mutantIsClose()
{
	return float_compare(MutantContainer::getSingleton().getMutantIt().back()->getPolarCoordinates().theta, m_player->getPolarCoordinates().theta, 0.1f);
}
bool Tutorial::mutantSpawned()
{
	m_canSpawn = true;
	if (m_mutantSize < MutantContainer::getSingleton().getMutantIt().size())
	{
	    m_mutantSize = MutantContainer::getSingleton().getMutantIt().size();
		return true;
	}
	return false;
}
bool Tutorial::mutantDied()
{
	cout << m_mutantSize << " " << MutantContainer::getSingleton().getMutantIt().size();
	if (m_mutantSize > MutantContainer::getSingleton().getMutantIt().size())
	{
	    m_mutantSize = MutantContainer::getSingleton().getMutantIt().size();
		return true;
	}
	return false;
}
void Tutorial::genericPress(TutorialScript changeTo, OIS::KeyCode keyCode)
{
    if (OISCore::getSingleton().getKeyboard()->isKeyDown(keyCode))
    {
        m_tooltipIdx = changeTo;
        enterPressed();
    }
}
bool Tutorial::pauseTimer()
{
	m_pauseTimer += MainUpdate::getSingleton().getDeltaTime();
	if (m_pauseTimer > 2.0f)
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
        model.tooltip(m_currentMsg);
	}
}
void Tutorial::showTooltipSlowMotion(ModelHandler& model, const std::string& msg)
{
	if (m_currentMsg != msg || !float_compare(GlobalVariables::getSingleton().getSpeed(), 0.0f,0.1f))
	{
        m_currentMsg = msg;
		setCompositor(true);
		setSlowmotion(true);
        model.tooltip(m_currentMsg);
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
        GlobalVariables::getSingleton().setSpeed(0.001f);
	else
        GlobalVariables::getSingleton().setSpeed(1.0f);
}