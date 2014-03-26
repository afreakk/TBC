#pragma once
#include "ModelHandlerPlayer.h"
#include "MainUpdate.h"
#include "Player.h"
enum class TeleportState
{
    TELEPORT_IN,
    TELEPORT_WAIT,
    TELEPORT_OUT,
    COOLDOWN,
    NOTHING
};
class Teleporter
{
private:
	TeleportState m_teleportState;
	Player* m_player;
	Ogre::Real m_teleportTimer;
	Ogre::Vector3 m_toLoc;

public:
	Teleporter(Player* player)
		: m_player(player)
		, m_teleportState(TeleportState::NOTHING)
		, m_teleportTimer(0.0f)
		, m_toLoc(Vector3::ZERO)
	{}
    void teleport(const Vector3& to = Vector3::ZERO)
    {
		if (m_teleportState == TeleportState::NOTHING)
		{
            m_teleportState = TeleportState::TELEPORT_IN;
			m_toLoc = to;
		}
    }
    bool handleTeleport()
    {
        switch (m_teleportState)
        {
        case TeleportState::TELEPORT_IN:
            static_cast<ModelHandlerPlayer&>(m_player->getModelHandler()).teleportIn();
            m_teleportState = TeleportState::TELEPORT_WAIT;
            break;
        case TeleportState::TELEPORT_WAIT:
            m_teleportTimer += MainUpdate::getSingleton().getDeltaTime();
            if (m_teleportTimer > 0.5f)
            {
				if (m_toLoc != Vector3::ZERO)
                    static_cast<ModelHandlerPlayer&>(m_player->getModelHandler()).teleportMove(m_toLoc);
				else
                    static_cast<ModelHandlerPlayer&>(m_player->getModelHandler()).teleportMove();
                m_teleportState = TeleportState::TELEPORT_OUT;
                m_teleportTimer = 0.0f;
            }
            break;
        case TeleportState::TELEPORT_OUT:
            static_cast<ModelHandlerPlayer&>(m_player->getModelHandler()).teleportOut();
            m_teleportState = TeleportState::COOLDOWN;
            break;
        case TeleportState::COOLDOWN:
            m_teleportTimer += MainUpdate::getSingleton().getDeltaTime();
            if (m_teleportTimer > 0.2f)
            {
                m_teleportState = TeleportState::NOTHING;
                m_teleportTimer = 0.0;
            }
            break;
        case TeleportState::NOTHING:
            //nuthin dood
			return false;
            break;
        default:
            assert(0);
            break;
        }
        return true;
    }
};