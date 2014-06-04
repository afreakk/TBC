#include "stdafx.h"
#include "MutantDeadState.h"
#include "MainUpdate.h"
#include "SoundFactory.h"
MutantDeadState::MutantDeadState(Vector3 killedDirection, ModelHandlerMutant& mutantModelHandler)
: BehaviourStateDead()
{
	std::string deadSound = "sfx/mons_dead" +boost::lexical_cast<std::string>( rand() % 3) + ".ogg";
	SoundFactory::getSingleton().playSound3D(deadSound, deadSound,mutantModelHandler.getNode());
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	mutantModelHandler.damage(killedDirection.normalisedCopy());
}

MutantDeadState::~MutantDeadState()
{
}
void MutantDeadState::update(ModelHandler& m)
{
	m.getNode()->translate(Vector3(0, -MainUpdate::getSingleton().getDeltaTime() * 10.0f, 0));
	BehaviourStateDead::update(m);
}