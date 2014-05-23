#include "stdafx.h"
#include "Tooltip.h"
#include "OgreCore.h"
#include "MainUpdate.h"

std::vector<TooltipBase*> TooltipUpdates::m_tooltips;
//--------------------------------------------------------------TooltipBase-----------------
TooltipBase::TooltipBase()
:m_addedToUpdate(false)
{

}
void TooltipBase::addToUpdate()
{
	if (!m_addedToUpdate)
	{
        TooltipUpdates::addTooltip(this);
		m_addedToUpdate = true;
	}
}
void TooltipBase::removeFromUpdate()
{
	if (m_addedToUpdate)
	{
        TooltipUpdates::removeTooltip(this);
		m_addedToUpdate = false;
	}
}

//--------------------------------------------------------------2DTooltip-----------------

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
, m_captionString("fucku")
{
	
}
TwoDTooltip::~TwoDTooltip()
{
    Gorilla::Silverback::getSingleton().destroyScreen(m_screen);
	removeFromUpdate();
}
void TwoDTooltip::show(const std::string& markup, const std::string& caption)
{
	if (m_markupString == markup && caption == m_captionString)
		return;
	m_markupString = markup;
	m_captionString = caption;
	if (!m_created)
		create();
	updateText(m_markupString);
	updateCaption(m_captionString);
    makeBubble();
	addToUpdate();
}
void TwoDTooltip::hide()
{
    m_layer->destroyLineList(m_lineList);
    m_layer->destroyMarkupText(m_mainTextMarkup);
	m_layer->destroyCaption(m_keyToPressCaption);
	m_lineList = nullptr;
	m_mainTextMarkup = nullptr;
	m_keyToPressCaption = nullptr;
	removeFromUpdate();
}
void TwoDTooltip::update()
{
	if (m_timeSinceLastUpdate<1.0f)
	    m_timeSinceLastUpdate += MainUpdate::getSingleton().getDeltaTime();
	else
        updateCaption(m_captionString + m_stringDotter.getDot() );
}
//---------------------------------------------privates-----------------------------------------------------------
void TwoDTooltip::updateCaption(const std::string& caption)
{
    m_timeSinceLastUpdate = 0.0f;
	auto vpH = OgreCore::getSingleton().getViewport()->getActualHeight();
	auto vpW = OgreCore::getSingleton().getViewport()->getActualWidth();
	if (m_keyToPressCaption)
		m_layer->destroyCaption(m_keyToPressCaption);
	m_keyToPressCaption = m_layer->createCaption(14, m_offset.x+m_rectSize.x+vpW/60.0f, vpH-(m_offset.y+vpH/30.0f), caption);
}
void TwoDTooltip::updateText(const std::string& msg)
{
	m_rectSize = getDimensions(msg, 24);
	if (m_mainTextMarkup)
	    m_layer->destroyMarkupText(m_mainTextMarkup);
	m_rectSize.y += m_offset.y;
	auto vpH = OgreCore::getSingleton().getViewport()->getActualHeight();
	auto vpW = OgreCore::getSingleton().getViewport()->getActualWidth();
    m_mainTextMarkup = m_layer->createMarkupText(24, m_offset.x, vpH-m_rectSize.y, msg);
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

//-----------------------------------------------3DTooltip-------------------------------------------------------

ThreeDTooltip::ThreeDTooltip(Ogre::SceneNode* parentNode)
: m_tooltipSize(600.0f, 200.0f)
, m_rectSize(m_tooltipSize.x*65.0f, m_tooltipSize.y*100.0f)
, m_screen ( Gorilla::Silverback::getSingleton().createScreenRenderable(m_tooltipSize, "dejavu") )
, m_layer(nullptr)
, m_markup(nullptr)
, m_lineList(nullptr)
, m_node ( parentNode->createChildSceneNode(Vector3(0.0f, 450.0f, 0.0f)) ) 
, m_created(false)
, m_shown(false)
{
}
ThreeDTooltip::~ThreeDTooltip()
{
	removeFromUpdate();
	destroyScreenRenderable();
}
void ThreeDTooltip::hide()
{
	removeFromUpdate();
	if (m_shown)
	{
		m_node->detachObject(m_screen);
        m_shown = false;
	}
}

void ThreeDTooltip::destroyScreenRenderable()
{
    Gorilla::Silverback::getSingleton().destroyScreenRenderable(m_screen);
}
Ogre::Vector2 ThreeDTooltip::updateText(std::string& msg)
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
Ogre::Vector2 ThreeDTooltip::getDimensions(std::string& msg, unsigned fontSize)
{
	auto temp = m_layer->createMarkupText(fontSize, 0, 0, msg);
	Ogre::Vector2 dimensions;
	dimensions.x = temp->maxTextWidth();
	dimensions.y = temp->maxTextHeight(false);
	m_layer->destroyMarkupText(temp);
	return dimensions;
}
void ThreeDTooltip::show(std::string& msg)
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
void ThreeDTooltip::makeBubble(Ogre::Vector2& compensation)
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
void ThreeDTooltip::update()
{
	m_node->lookAt(Vector3(0,100,0),Node::TransformSpace::TS_WORLD);
}

//------------------------------------TooltipUpdates--------------------------------------------------------------

void TooltipUpdates::update()
{
    for (auto& tooltip : m_tooltips)
        tooltip->update();
}
void TooltipUpdates::addTooltip(TooltipBase* tooltip)
{
    m_tooltips.push_back(tooltip);
}
void TooltipUpdates::removeTooltip(TooltipBase* tooltip)
{
    auto it = std::find(m_tooltips.begin(), m_tooltips.end(), tooltip);
    if (it != m_tooltips.end())
        m_tooltips.erase(it);
}
