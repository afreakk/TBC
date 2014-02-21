#include "stdafx.h"
#include "Player.h"
#include "ModelHandlerPlayer.h"

Player::Player(PolarCoordinates coordinate) 
: BehaviourObject(new ModelHandlerPlayer( coordinate ) , BObjectType::Player) 
{
	m_model->init();
}

Player::~Player()
{

}

