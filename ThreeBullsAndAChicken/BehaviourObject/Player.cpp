#include "stdafx.h"
#include "Player.h"
#include "../ModelBehaviour/ModelHandlerPlayer.h"

Player::Player() 
: BehaviourObject(new ModelHandlerPlayer( PolarCoordinates( 0.0, NORMAL_LANES[1], 0.2 )  ) )
{
	m_model->init();
}

Player::~Player()
{

}

