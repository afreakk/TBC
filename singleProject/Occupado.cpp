#include "stdafx.h"
#include "Occupado.h"
#include "PolarCoordinates.h"
#include "MutantContainer.h"
#include "PlayerContainer.h"
#include "Player.h"
#include "LaneSettings.h"
const Ogre::Real NormalModeModelSpacing = Math::PI/1024.0;
const Ogre::Real LerpModeSpacing = 200.0;

bool Occupado::isOccupiedVelocity(const PolarCoordinates& e , const Ogre::Real& velocity)
{
	for (auto& it : MutantContainer::getSingleton().getMutantIt())
	{
		if (hitTestVelocity(it, e, velocity))
			return true;
	}
	return (hitTestVelocity(PlayerContainer::getSingleton().getPlayer(), e, velocity));
}
bool Occupado::hitTestVelocity(const BehaviourObject* object, const PolarCoordinates& e, const Ogre::Real& velocity)
{
	if (!float_compare(object->getPolarCoordinates().radius, e.radius, LaneSettings::getSingleton().getIncrement()/Real(2.0)) 
		|| &e == &(object->getPolarCoordinates()))
		return false;
	if (float_compare(object->getPolarCoordinates().theta, e.theta + velocity, NormalModeModelSpacing))
	{
		if (e.theta > object->getPolarCoordinates().theta) {
			if (velocity > 0)
				return false;
		}
		else if (velocity < 0)
            return false;
        return true;
	}
	return false;
}
bool Occupado::isOccupiedWidth(const PolarCoordinates& e , const Ogre::Real& width)
{
	if (MutantContainer::isInstantiated())
	{
        for (auto& it : MutantContainer::getSingleton().getMutantIt())
        {
            if (hitTestWidth(it, e, width))
                return true;
        }
	}
	return (hitTestWidth(PlayerContainer::getSingleton().getPlayer(), e,width));
}
bool Occupado::hitTestWidth(const BehaviourObject* object, const PolarCoordinates& e, const Ogre::Real& width)
{
	if (!float_compare(object->getPolarCoordinates().radius, e.radius, LaneSettings::getSingleton().getIncrement()/Real(2.0)) 
		|| &e == &(object->getPolarCoordinates()))
		return false;
	if (float_compare(object->getPolarCoordinates().theta, e.theta, width))
		return true;
	return false;
}
// not implemented dno if needed
/*
Ogre::Vector3 Occupado::safeTranslate(Ogre::Node* node, const Ogre::Real& velocity)
{
	node->translate(Vector3(0.0, 0.0, -velocity), Ogre::Node::TS_LOCAL);
	Vector3 unModifiedTranslate = node->getPosition();
	BehaviourObject* target = nullptr;
	Real closestTarget = numeric_limits<Real>::max();
	for (auto& it : MutantContainer::getSingleton().getMutantIt())
	{
		auto result = hitTest(it, node);
		if (result.first && result.second<closestTarget)
		{
			target = it;
			closestTarget = result.second;
		}
	}
	auto result = hitTest(PlayerContainer::getSingleton().getPlayer(), node);
	if (result.first&& result.second < closestTarget)
	{
        target = PlayerContainer::getSingleton().getPlayer();
        closestTarget = result.second;
	}
	if (target != nullptr)
	{
        Ogre::Real hitTargetLocalX = node->convertWorldToLocalPosition(target->getNode()->getPosition()).x;
        node->translate(Vector3(-hitTargetLocalX, 0.0, 0.0), Ogre::Node::TS_LOCAL);
	}
	Vector3 modifiedAmmount = node->getPosition() - unModifiedTranslate;
	return modifiedAmmount;
}

std::pair<bool,Ogre::Real> Occupado::hitTest(BehaviourObject* it, const Ogre::Node* node)
{
	if (it->getNode() == node)
		return{ false, 0.0 };
    Real distance = it->getNode()->getPosition().distance(node->getPosition());
    if (distance < LerpModeSpacing)
        return{ true , distance};
	return{ false, 0.0 };
}

Ogre::AxisAlignedBox getTranslatedAAB(Ogre::AxisAlignedBox boundingBox, Ogre::Node* node, Ogre::Entity* entity)
{
	Matrix4 mat;
    Node* entityNode = entity->getParentNode();
	if (node != entityNode)
        mat.makeTransform(node->getPosition(), entityNode->getScale(), entityNode->getOrientation());
	else
        mat.makeTransform(node->getPosition(), node->getScale(), node->getOrientation());
    // this is hax because robot is being "innerscaled"  
	boundingBox.transform(mat);
	return boundingBox;
}
*/