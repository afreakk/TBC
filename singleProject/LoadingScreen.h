#pragma once
#include "LoadingScreenDisplayer.h"
class BaseLoadingBar
{
public:
	BaseLoadingBar();
	virtual void start(RenderWindow* window);
	virtual void finish(void);
protected:
	virtual void animate();
	const std::string& animatedDots();
private:
	std::unique_ptr<LoadingScreenDisplayer> m_background;
	std::string m_animatedDots;
};
class LevelLoaderBar : public BaseLoadingBar, LogListener
{
public:
	LevelLoaderBar() {}
	virtual ~LevelLoaderBar();
	virtual void start(RenderWindow* window ) override;
	virtual void finish(void) override;
    virtual void messageLogged( const String& message, LogMessageLevel lml, bool maskDebug, const String &logName, bool& skipThisMessage ) override;
protected:
	Real mProgressBarInc;
	RenderWindow* mWindow;
	Overlay* mLoadOverlay;
	OverlayElement* mLoadingBarElement;
	OverlayElement* mLoadingDescriptionElement;
	OverlayElement* mLoadingCommentElement;
	void write1337Text();
};

class LoadingBar : public ResourceGroupListener, BaseLoadingBar
{
public:
	LoadingBar() {}
	virtual ~LoadingBar(){}
	virtual void start(RenderWindow* window, unsigned short numGroupsInit = 1, unsigned short numGroupsLoad = 1, Real initProportion = 0.70f);
	virtual void finish(void) override;
	// ResourceGroupListener callbacks
	void resourceGroupScriptingStarted(const String& groupName, size_t scriptCount);
	void scriptParseStarted(const String& scriptName, bool &skipThisScript);
	void scriptParseEnded(const String& scriptName, bool skipped);
	void resourceGroupScriptingEnded(const String& groupName);
	void resourceGroupLoadStarted(const String& groupName, size_t resourceCount);
	void resourceLoadStarted(const ResourcePtr& resource);
	void resourceLoadEnded(void);
	void worldGeometryStageStarted(const String& description);
	void worldGeometryStageEnded(void);
	void resourceGroupLoadEnded(const String& groupName);
	Ogre::DataStreamPtr resourceLoading(const String &name, const String &group, Resource *resource);
	bool resourceCollision(ResourcePtr &resource, ResourceManager *resourceManager);

protected:
	RenderWindow* mWindow;
	Overlay* mLoadOverlay;
	Real mInitProportion;
	unsigned short mNumGroupsInit;
	unsigned short mNumGroupsLoad;
	Real mProgressBarMaxSize;
	Real mProgressBarScriptSize;
	Real mProgressBarInc;
	OverlayElement* mLoadingBarElement;
	OverlayElement* mLoadingDescriptionElement;
	OverlayElement* mLoadingCommentElement;

};
