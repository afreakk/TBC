#include "stdafx.h"
#include "Tooltip.h"
#include "OgreCore.h"
std::vector<Tooltip*> TooltipUpdates::m_tooltips;

Tooltip::Tooltip(Ogre::SceneNode* parentNode)
: m_tooltipSize(600.0f, 200.0f)
, m_rectSize(m_tooltipSize.x*65.0f, m_tooltipSize.y*100.0f)
, m_screen ( Gorilla::Silverback::getSingleton().createScreenRenderable(m_tooltipSize, "dejavu") )
, m_node ( parentNode->createChildSceneNode(Vector3(0.0f, 450.0f, 0.0f)) ) 
{
}
void Tooltip::enable(bool v)
{
	m_layer = m_screen->createLayer(0);
	Gorilla::MarkupText::TEXTSIZEHACK = 200.0f;
	const Ogre::Vector2 padding = m_rectSize / 32.0f;
	m_markup = m_layer->createMarkupText(24, padding.x, padding.y, "This guy!!!!!\nover here..");
	m_node->attachObject(m_screen);
	m_lineList = m_layer->createLineList();
	m_lineList->begin(500.0f, Gorilla::Colours::Aquamarine);
	const Ogre::Vector2 chopSize = m_rectSize/7.0f;
	m_lineList->position(Vector2(0.0f           , 0.0f));
	m_lineList->position(Vector2(0.0f           , m_rectSize.y));
	m_lineList->position(Vector2(chopSize.x*3.0f, m_rectSize.y));
	m_lineList->position(Vector2(chopSize.x*5.0f, m_rectSize.y*1.5f));
	m_lineList->position(Vector2(chopSize.x*5.0f, m_rectSize.y));
	m_lineList->position(Vector2(chopSize.x*7.0f, m_rectSize.y));
	m_lineList->position(Vector2(chopSize.x*7.0f, 0.0f));
	m_lineList->position(Vector2(0.0f, 0.0f));
	m_lineList->end();
	TooltipUpdates::addTooltip(this);
}
void Tooltip::update()
{
	m_node->lookAt(Vector3::ZERO,Node::TransformSpace::TS_WORLD);
}
Tooltip::~Tooltip()
{
//	TooltipUpdates::removeTooltip(this);
    // fix this hobo
}


void TooltipUpdates::update()
{
    for (auto& tooltip : m_tooltips)
        tooltip->update();
}
void TooltipUpdates::addTooltip(Tooltip* tooltip)
{
    m_tooltips.push_back(tooltip);
}
void TooltipUpdates::removeTooltip(Tooltip* tooltip)
{
    auto it = std::find(m_tooltips.begin(), m_tooltips.end(), tooltip);
    if (it != m_tooltips.end())
        m_tooltips.erase(it);
    else
        assert(0);
}