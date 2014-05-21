#pragma once
class TwoDTooltip
{
public:
	TwoDTooltip(Ogre::Node* parentNode);
	~TwoDTooltip();
	void show(const std::string& msg, const std::string& caption);
	void hide();
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

	void create();
	void updateText(const std::string& msg, const std::string& caption);
	void makeBubble();
	Ogre::Vector2 getDimensions(const std::string& msg, unsigned fontSize);
};

class Tooltip
{
public:
	Tooltip(Ogre::SceneNode* parentNode);
	~Tooltip();
	void update();
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
	bool m_addedToUpdate;
	bool m_created;
	bool m_shown;


	void addToUpdate();
	void removeFromUpdate();
	void destroyScreenRenderable();
	Ogre::Vector2 updateText(std::string& msg);
	void makeBubble(Ogre::Vector2& compensation);
	Ogre::Vector2 getDimensions(std::string& msg, unsigned fontSize);

};


class TooltipUpdates
{
public:
	static void update();
	static void addTooltip(Tooltip* tooltip);
	static void removeTooltip(Tooltip* tooltip);
private:
	static std::vector< Tooltip*> m_tooltips;
};