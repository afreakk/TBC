#include "stdafx.h"
#include "Tooltip.h"
#include "OgreCore.h"

std::vector<Tooltip*> TooltipUpdates::m_tooltips;

TwoDTooltip::TwoDTooltip(Node* node)
: m_node(node)
, m_screen ( nullptr )
, m_layer(nullptr)
, m_mainTextMarkup(nullptr)
, m_keyToPressCaption(nullptr)
, m_lineList(nullptr)
, m_created(false)
, m_offset(100,100)
, m_bubbleTextOffset(10,10)
{
	
}
TwoDTooltip::~TwoDTooltip()
{
    Gorilla::Silverback::getSingleton().destroyScreen(m_screen);
}
void TwoDTooltip::show(const std::string& msg, const std::string& caption)
{
	if (!m_created)
		create();
	updateText(msg, caption);
    makeBubble();
}
void TwoDTooltip::updateText(const std::string& msg, const std::string& caption)
{
	m_rectSize = getDimensions(msg, 24);
	if (m_keyToPressCaption)
		m_layer->destroyCaption(m_keyToPressCaption);
	if (m_mainTextMarkup)
	    m_layer->destroyMarkupText(m_mainTextMarkup);
	m_rectSize.y += m_offset.y;
	auto vpH = OgreCore::getSingleton().getViewport()->getActualHeight();
	auto vpW = OgreCore::getSingleton().getViewport()->getActualWidth();
    m_mainTextMarkup = m_layer->createMarkupText(24, m_offset.x, vpH-m_rectSize.y, msg);
	m_keyToPressCaption = m_layer->createCaption(14, m_offset.x+m_rectSize.x+vpW/60.0f, vpH-(m_offset.y+vpH/30.0f), caption);
}
void TwoDTooltip::makeBubble()
{
	Vector2 comp(m_mainTextMarkup->left()-m_bubbleTextOffset.x, m_mainTextMarkup->top()- m_bubbleTextOffset.y);
	if (m_lineList)
	    m_layer->destroyLineList(m_lineList);
	m_lineList = m_layer->createLineList();
	m_lineList->begin(1.0f, Gorilla::Colours::Aquamarine);
	Vector2 topLeft(    0.0f                                     , 0.0f);
	Vector2 topRight(   m_rectSize.x + m_bubbleTextOffset.x*2.0f , 0.0f);
	Vector2 bottomLeft( 0.0f                                     , m_rectSize.y - m_offset.y + m_bubbleTextOffset.y*2.0f);
	Vector2 bottomRight(m_rectSize.x + m_bubbleTextOffset.x*2.0f, m_rectSize.y - m_offset.y + m_bubbleTextOffset.y*2.0f);
	m_lineList->position( comp+topLeft);
	m_lineList->position( comp+bottomLeft);
	m_lineList->position( comp+bottomRight);
	auto boxSize = 100.0f;
	m_lineList->position(comp + bottomRight + Vector2(boxSize, 0.0f));
	m_lineList->position(comp + bottomRight + Vector2(boxSize, -boxSize/2.0f));
	m_lineList->position(comp + bottomRight + Vector2(0.0f, -boxSize/2.0f));
	m_lineList->position( comp+bottomRight);
	m_lineList->position( comp+topRight);
	m_lineList->position( comp+topLeft);
	m_lineList->end();
}
Ogre::Vector2 TwoDTooltip::getDimensions(const std::string& msg, unsigned fontSize)
{
	auto temp = m_layer->createMarkupText(fontSize, 0, 0, msg);
	Ogre::Vector2 dimensions;
	dimensions.x = temp->maxTextWidth();
	dimensions.y = temp->maxTextHeight(false);
	m_layer->destroyMarkupText(temp);
	return dimensions;
}
void TwoDTooltip::create()
{
	m_screen = Gorilla::Silverback::getSingleton().createScreen(OgreCore::getSingleton().getViewport(), "dejavu");
    m_layer = m_screen->createLayer(0);
	m_created = true;
}
void TwoDTooltip::hide()
{
    m_layer->destroyLineList(m_lineList);
    m_layer->destroyMarkupText(m_mainTextMarkup);
	m_layer->destroyCaption(m_keyToPressCaption);
	m_lineList = nullptr;
	m_mainTextMarkup = nullptr;
	m_keyToPressCaption = nullptr;
}
//------------------------------------------------------------------------------------------------------------------------------------
Tooltip::Tooltip(Ogre::SceneNode* parentNode)
: m_tooltipSize(600.0f, 200.0f)
, m_rectSize(m_tooltipSize.x*65.0f, m_tooltipSize.y*100.0f)
, m_screen ( Gorilla::Silverback::getSingleton().createScreenRenderable(m_tooltipSize, "dejavu") )
, m_layer(nullptr)
, m_markup(nullptr)
, m_lineList(nullptr)
, m_node ( parentNode->createChildSceneNode(Vector3(0.0f, 450.0f, 0.0f)) ) 
, m_addedToUpdate(false)
, m_created(false)
, m_shown(false)
{
}
Tooltip::~Tooltip()
{
	removeFromUpdate();
	destroyScreenRenderable();
}
void Tooltip::hide()
{
	removeFromUpdate();
	if (m_shown)
	{
		m_node->detachObject(m_screen);
        m_shown = false;
	}
}

void Tooltip::destroyScreenRenderable()
{
    Gorilla::Silverback::getSingleton().destroyScreenRenderable(m_screen);
}
void Tooltip::addToUpdate()
{
	if (!m_addedToUpdate)
        TooltipUpdates::addTooltip(this);
}
void Tooltip::removeFromUpdate()
{
	if (m_addedToUpdate)
        TooltipUpdates::removeTooltip(this);
}
Ogre::Vector2 Tooltip::updateText(std::string& msg)
{
	Gorilla::MarkupText::TEXTSIZEHACK = 200.0f;
	const Ogre::Vector2 dimensions = getDimensions(msg,24);
	if (m_markup)
	    m_layer->destroyMarkupText(m_markup);
	Ogre::Vector2 compensation(Ogre::Vector2::ZERO);
	if (dimensions.y > 30000.0f)
		compensation.y = -(dimensions.y - 30000.0f) ;
	m_markup = m_layer->createMarkupText(24, 0, 0, msg);
	m_rectSize = dimensions;
	return compensation;
}
Ogre::Vector2 Tooltip::getDimensions(std::string& msg, unsigned fontSize)
{
	auto temp = m_layer->createMarkupText(fontSize, 0, 0, msg);
	Ogre::Vector2 dimensions;
	dimensions.x = temp->maxTextWidth();
	dimensions.y = temp->maxTextHeight(false);
	m_layer->destroyMarkupText(temp);
	return dimensions;
}
void Tooltip::show(std::string& msg)
{
	if (!m_created)
	{
        m_layer = m_screen->createLayer(0);
        m_created = true;
	}
	auto compensation = updateText(msg);
    makeBubble(compensation);
	addToUpdate();
	if (!m_shown)
	{
        m_node->attachObject(m_screen);
		m_shown = true;
	}
}
void Tooltip::makeBubble(Ogre::Vector2& compensation)
{
	if (m_lineList)
	    m_layer->destroyLineList(m_lineList);
	m_lineList = m_layer->createLineList();
	m_lineList->begin(500.0f, Gorilla::Colours::Aquamarine);
	Ogre::Real down_dup = 30000.0f;
	Ogre::Real arrowLength = 38000.0f;
	m_lineList->position( Vector2(0.0f           , 0.0f));
	m_lineList->position( Vector2(0.0f           , m_rectSize.y));
	m_lineList->position( Vector2(down_dup-4000.0f, m_rectSize.y));
	m_lineList->position( Vector2(down_dup, arrowLength));
	m_lineList->position( Vector2(down_dup, m_rectSize.y));
	m_lineList->position( Vector2(m_rectSize.x, m_rectSize.y));
	m_lineList->position( Vector2(m_rectSize.x, 0.0f));
	m_lineList->position( Vector2(0.0f, 0.0f));
	m_lineList->end();
}
void Tooltip::update()
{
	m_node->lookAt(Vector3(0,100,0),Node::TransformSpace::TS_WORLD);
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