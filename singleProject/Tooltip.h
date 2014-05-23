#pragma once
#include "GUIUtils.h"
class TooltipBase
{
public:
	TooltipBase();
	virtual ~TooltipBase(){}
	virtual void update() = 0;
protected:
	void addToUpdate();
	void removeFromUpdate();
private:
	bool m_addedToUpdate;
};

class TwoDTooltip : public TooltipBase
{
public:
	TwoDTooltip(Ogre::Node* parentNode);
	~TwoDTooltip();
	void show(const std::string& markup, const std::string& caption);
	void hide();
	void update() override;
private:
	Ogre::Node*m_node;
	Gorilla::Screen* m_screen;
	Gorilla::Layer* m_layer;
	Gorilla::MarkupText* m_mainTextMarkup;
	Gorilla::Caption* m_keyToPressCaption;
	Gorilla::LineList* m_lineList;
	bool m_created;
	Ogre::Vector2 m_rectSize;
	Ogre::Vector2 m_offset;
	Ogre::Vector2 m_bubbleTextOffset;
	std::string m_captionString;
	std::string m_markupString;
	StringDotter m_stringDotter;
	Ogre::Real m_timeSinceLastUpdate;
    

	void create();
	void updateText(const std::string& msg);
	void updateCaption(const std::string& caption);
	void makeBubble();
	Ogre::Vector2 getDimensions(const std::string& msg, unsigned fontSize);
};

class ThreeDTooltip : public TooltipBase
{
public:
	ThreeDTooltip(Ogre::SceneNode* parentNode);
	~ThreeDTooltip();
	void update() override;
	void show(std::string& msg);
	void hide();
private:
	const Ogre::Vector2 m_tooltipSize;
	Ogre::Vector2 m_rectSize;

	Gorilla::ScreenRenderable* m_screen;
	Gorilla::Layer* m_layer;
	Gorilla::MarkupText* m_markup;
	Gorilla::LineList* m_lineList;
	Ogre::SceneNode*m_node;
	bool m_created;
	bool m_shown;


	void destroyScreenRenderable();
	Ogre::Vector2 updateText(std::string& msg);
	void makeBubble(Ogre::Vector2& compensation);
	Ogre::Vector2 getDimensions(std::string& msg, unsigned fontSize);

};


class TooltipUpdates
{
public:
	static void update();
	static void addTooltip(TooltipBase* tooltip);
	static void removeTooltip(TooltipBase* tooltip);
private:
	static std::vector< TooltipBase*> m_tooltips;
};