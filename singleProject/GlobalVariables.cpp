#include "stdafx.h"
#include "GlobalVariables.h"
#include "MainUpdate.h"
#include "ConfigScriptLoader.h"
template<> GlobalVariables* Ogre::Singleton<GlobalVariables>::msSingleton = 0;
GlobalVariables::GlobalVariables()
: m_speed(Real(1.0))
, m_lerpToNormal(0.0f)
{
    parseScript();
}
GlobalVariables::~GlobalVariables()
{}
const Real& GlobalVariables::getSpeed() 
{
    m_finalSpeed = m_speed - m_lerpToNormal;
    return m_finalSpeed;
}
void GlobalVariables::updateLerp()
{
    if (m_lerpToNormal > 0.0f)
        m_lerpToNormal -= MainUpdate::getSingleton().getDeltaTime()/1.5f;
    else if (m_lerpToNormal != 0.0f)
        m_lerpToNormal = 0.0f;
}
void GlobalVariables::setSpeed(const Real& newSpeed)
{
    if (m_speed != newSpeed)
    {
        m_speed = newSpeed;
        if (m_speed > 0.75f)
            m_lerpToNormal = 0.9f;
        m_soundOfSpeed.updateValue(m_speed);
    }
}
const Real& GlobalVariables::getLERPAnimWalkRatio() const
{
    return m_lerpAnimWalkRatio;
}
const Real& GlobalVariables::getLERPAnimAttackRatio() const
{
    return m_lerpAnimAttackRatio;
}
const Real& GlobalVariables::getLERPAnimTumblekRatio() const
{
    return m_lerpAnimTumbleRatio;
}
const Real& GlobalVariables::getNormalAnimWalkSpeed() const
{
    return m_normalAnimWalkSpeed;
}
const Real& GlobalVariables::getAnimDieSpeed() const
{
    return m_animDieSpeed;
}
//---------------privatez--------------------
void GlobalVariables::parseScript()
{
    ConfigNode* rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "GlobalStats");
    m_lerpAnimWalkRatio = rootNode->findChild("LERPAnimWalkRatio")->getValueR(0);
    m_lerpAnimAttackRatio = rootNode->findChild("LERPAnimAttackRatio")->getValueR(0);
    m_lerpAnimTumbleRatio = rootNode->findChild("LERPAnimTumbleRatio")->getValueR(0);

    m_normalAnimWalkSpeed = rootNode->findChild("normalAnimWalkSpeed")->getValueR(0);
    m_animDieSpeed = rootNode->findChild("animDieSpeed")->getValueR(0);
}