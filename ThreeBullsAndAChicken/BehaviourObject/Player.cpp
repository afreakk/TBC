#include "stdafx.h"
#include "Player.h"
#include "../ModelBehaviour/ModelHandlerPlayer.h"

Player::Player(PolarCoordinates coordinate) 
: BehaviourObject(new ModelHandlerPlayer( coordinate ) ) 
{
	m_model->init();
}

Player::~Player()
{

}

