#pragma once
class LevelLoaderBar
{
public:
	LevelLoaderBar() {}
	virtual ~LevelLoaderBar(){}
	virtual void start(RenderWindow* window );
	virtual void finish(void);
	void increment();
protected:
	RenderWindow* mWindow;
	Overlay* mLoadOverlay;
	OverlayElement* mLoadingBarElement;
	OverlayElement* mLoadingDescriptionElement;
	OverlayElement* mLoadingCommentElement;
};

class LoadingBar : public ResourceGroupListener
{
public:
	LoadingBar() {}
	virtual ~LoadingBar(){}
	virtual void start(RenderWindow* window, unsigned short numGroupsInit = 1, unsigned short numGroupsLoad = 1, Real initProportion = 0.70f);
	virtual void finish(void);
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