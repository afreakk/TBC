#include "stdafx.h"
#include "LoadingScreen.h"

void LevelLoaderBar::start(RenderWindow* window)
{
    mWindow = window;
    ResourceGroupManager::getSingleton().initialiseResourceGroup("Bootstrap");

    OverlayManager& omgr = OverlayManager::getSingleton();
    mLoadOverlay = (Overlay*)omgr.getByName("Core/LoadOverlay");
    mLoadOverlay->show();

    mLoadingCommentElement = omgr.getOverlayElement("Core/LoadPanel/Comment");
	mLoadingCommentElement->setCaption("Loading new level..");
    mLoadingDescriptionElement = omgr.getOverlayElement("Core/LoadPanel/Description");
	mLoadingDescriptionElement->setCaption("--Please==wait--");

	mWindow->update();
}

void LevelLoaderBar::finish(void)
{
    mLoadOverlay->hide();
}


void LoadingBar::start(RenderWindow* window, unsigned short numGroupsInit , unsigned short numGroupsLoad , Real initProportion )
{
    mWindow = window;
    mNumGroupsInit = numGroupsInit;
    mNumGroupsLoad = numGroupsLoad;
    mInitProportion = initProportion;
    ResourceGroupManager::getSingleton().initialiseResourceGroup("Bootstrap");

    OverlayManager& omgr = OverlayManager::getSingleton();
    mLoadOverlay = (Overlay*)omgr.getByName("Core/LoadOverlay");
    mLoadOverlay->show();

    // Save links to the bar and to the loading text, for updates as we go
    mLoadingBarElement = omgr.getOverlayElement("Core/LoadPanel/Bar/Progress");
    mLoadingCommentElement = omgr.getOverlayElement("Core/LoadPanel/Comment");
    mLoadingDescriptionElement = omgr.getOverlayElement("Core/LoadPanel/Description");

    OverlayElement* barContainer = omgr.getOverlayElement("Core/LoadPanel/Bar");
    mProgressBarMaxSize = barContainer->getWidth();
    mLoadingBarElement->setWidth(0);

    ResourceGroupManager::getSingleton().addResourceGroupListener(this);

	mWindow->update();
}

void LoadingBar::finish(void)
{
    mLoadOverlay->hide();
    ResourceGroupManager::getSingleton().removeResourceGroupListener(this);
}


void LoadingBar::resourceGroupScriptingStarted(const String& groupName, size_t scriptCount)
{
    assert(mNumGroupsInit > 0 && "You stated you were not going to init "
        "any groups, but you did! Divide by zero would follow...");

    mProgressBarInc = mProgressBarMaxSize * mInitProportion / (Real)scriptCount;
    mProgressBarInc /= mNumGroupsInit;
    mLoadingDescriptionElement->setCaption("Parsing scripts...");
    mWindow->update();
}
void LoadingBar::scriptParseStarted(const String& scriptName, bool &skipThisScript)
{
    mLoadingCommentElement->setCaption(scriptName);
    mWindow->update();
}
void LoadingBar::scriptParseEnded(const String& scriptName, bool skipped)
{
    mLoadingBarElement->setWidth(
        mLoadingBarElement->getWidth() + mProgressBarInc);
    mWindow->update();
}
void LoadingBar::resourceGroupScriptingEnded(const String& groupName)
{
}
void LoadingBar::resourceGroupLoadStarted(const String& groupName, size_t resourceCount)
{
    assert(mNumGroupsLoad > 0 && "You stated you were not going to load "
        "any groups, but you did! Divide by zero would follow...");
    mProgressBarInc = mProgressBarMaxSize * (1 - mInitProportion) /
        (Real)resourceCount;
    mProgressBarInc /= mNumGroupsLoad;
    mLoadingDescriptionElement->setCaption("Loading resources...");
    mWindow->update();
}
void LoadingBar::resourceLoadStarted(const ResourcePtr& resource)
{
    mLoadingCommentElement->setCaption(resource->getName());
    mWindow->update();
}
void LoadingBar::resourceLoadEnded(void)
{
}
void LoadingBar::worldGeometryStageStarted(const String& description)
{
    mLoadingCommentElement->setCaption(description);
    mWindow->update();
}
void LoadingBar::worldGeometryStageEnded(void)
{
    mLoadingBarElement->setWidth(
        mLoadingBarElement->getWidth() + mProgressBarInc);
    mWindow->update();
}
void LoadingBar::resourceGroupLoadEnded(const String& groupName)
{
}

Ogre::DataStreamPtr LoadingBar::resourceLoading(const String &name, const String &group, Resource *resource)
{
    return Ogre::DataStreamPtr();
}

bool LoadingBar::resourceCollision(ResourcePtr &resource, ResourceManager *resourceManager)
{
    return false;
}