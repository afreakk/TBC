#pragma once
#include "HandlerState.h"
#include "MutantHandlerEnums.h"
class BehaviourObject;
class BehaviourState;
#include "ENUMTumbleDirection.h"
#include "ENUMNormalDirection.h"
enum class SUICIDE_STATE
{
    NORMAL,
    TUMBLE
};
class MutantHandlerStateSuicideBomb : public HandlerState <MUTANT_HANDLER_STATE>
{
public:
	MutantHandlerStateSuicideBomb(BehaviourObject* mutant, BehaviourObject* playerObject);
	~MutantHandlerStateSuicideBomb();
	void update() override;
	TUMBLE_DIRECTION getDirection()
	{
		return m_tumbleDirection;
	}
private:
	NormalDirection m_direction;
	Ogre::Real m_speed;
	BehaviourObject* m_mutant;
	unique_ptr<BehaviourState> m_mutState;
	Ogre::Real m_detonationTimer;
	bool m_activated;
	BehaviourObject* m_player;
	TUMBLE_DIRECTION m_tumbleDirection;
	SUICIDE_STATE m_mutantState;

	void handleDetonationTimer();
	void steerTowardsPlayer();
	void horizontalSteer();
	void verticalSteer();
	void handleTumble();
	void setState(SUICIDE_STATE state);
	void clickClicker();

};
