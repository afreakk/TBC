#include "stdafx.h"
#include "LoadingScreen.h"
#include "OgreCore.h"

BaseLoadingBar::BaseLoadingBar()
: m_animatedDots("")
{

}
void BaseLoadingBar::start(RenderWindow* window)
{
	m_background = unique_ptr<LoadingScreenDisplayer>(new LoadingScreenDisplayer());
	auto smgr = OgreCore::getSingleton().getSceneMgr();
	smgr->clearSpecialCaseRenderQueues();
	smgr->addSpecialCaseRenderQueue(RENDER_QUEUE_OVERLAY);
	smgr->setSpecialCaseRenderQueueMode(SceneManager::SCRQM_INCLUDE);

}

const std::string& BaseLoadingBar::animatedDots()
{
    if (m_animatedDots.length() < 3)
        m_animatedDots += ".";
    else
        m_animatedDots = "";
	return m_animatedDots;
}
void BaseLoadingBar::finish(void)
{
	auto smgr = OgreCore::getSingleton().getSceneMgr();
	smgr->clearSpecialCaseRenderQueues();
	smgr->setSpecialCaseRenderQueueMode(SceneManager::SCRQM_EXCLUDE);
	m_background.reset();
}
void BaseLoadingBar::animate()
{
	assert(m_background);
	m_background->animate();
}
//----------#######################################################|||||||||||||||||||||||||||||||||||
void LevelLoaderBar::start(RenderWindow* window)
{
	BaseLoadingBar::start(window);
    //----------
    mWindow = window;
    ResourceGroupManager::getSingleton().initialiseResourceGroup("Bootstrap");

    OverlayManager& omgr = OverlayManager::getSingleton();
    mLoadOverlay = (Overlay*)omgr.getByName("Core/LoadOverlay");
    mLoadOverlay->show();

    mLoadingBarElement = omgr.getOverlayElement("Core/LoadPanel/Bar/Progress");
    mLoadingCommentElement = omgr.getOverlayElement("Core/LoadPanel/Comment");
    mLoadingDescriptionElement = omgr.getOverlayElement("Core/LoadPanel/Description");

    OverlayElement* barContainer = omgr.getOverlayElement("Core/LoadPanel/Bar");
    mLoadingBarElement->setWidth(0);
	mProgressBarInc = 6.5f;
	write1337Text();
	animate();
	mWindow->update();
    //----------#######################################################
	LogManager::getSingleton().getDefaultLog()->addListener(this);
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void LevelLoaderBar::finish(void)
{
	BaseLoadingBar::finish();
    //----------
    mLoadOverlay->hide();
	LogManager::getSingleton().getDefaultLog()->removeListener(this);
}

static unsigned detailDropper = 0;
void LevelLoaderBar::messageLogged(const String& message, LogMessageLevel lml, bool maskDebug, const String &logName, bool& skipThisMessage)
{
	if (detailDropper < 20)
		detailDropper++;
	else
		write1337Text();
}

void LevelLoaderBar::write1337Text()
{
    mLoadingBarElement->setWidth(mLoadingBarElement->getWidth() + mProgressBarInc);
	const std::string& dots = animatedDots();
	mLoadingCommentElement->setCaption("--==[##UR G4M3");
	mLoadingDescriptionElement->setCaption( "--==[##L04D1N6"+dots );
    animate();
    mWindow->update();
    detailDropper = 0;
}
void LoadingBar::start(RenderWindow* window, unsigned short numGroupsInit , unsigned short numGroupsLoad , Real initProportion )
{
	BaseLoadingBar::start(window);
    //----------
    mWindow = window;
    mNumGroupsInit = numGroupsInit;
    mNumGroupsLoad = numGroupsLoad;
    mInitProportion = initProportion;
    ResourceGroupManager::getSingleton().initialiseResourceGroup("Bootstrap");

    OverlayManager& omgr = OverlayManager::getSingleton();
    mLoadOverlay = (Overlay*)omgr.getByName("Core/LoadOverlay");
    mLoadOverlay->show();

    mLoadingBarElement = omgr.getOverlayElement("Core/LoadPanel/Bar/Progress");
    mLoadingCommentElement = omgr.getOverlayElement("Core/LoadPanel/Comment");
    mLoadingDescriptionElement = omgr.getOverlayElement("Core/LoadPanel/Description");

    OverlayElement* barContainer = omgr.getOverlayElement("Core/LoadPanel/Bar");
    mProgressBarMaxSize = barContainer->getWidth();
    mLoadingBarElement->setWidth(0);

    ResourceGroupManager::getSingleton().addResourceGroupListener(this);
	animate();
	mWindow->update();
}

void LoadingBar::finish(void)
{
	BaseLoadingBar::finish();
    //----------
    mLoadOverlay->hide();
    ResourceGroupManager::getSingleton().removeResourceGroupListener(this);
}


    //----------#######################################################
void LoadingBar::resourceGroupScriptingStarted(const String& groupName, size_t scriptCount)
{
    assert(mNumGroupsInit > 0 && "You stated you were not going to init "
        "any groups, but you did! Divide by zero would follow...");

    mProgressBarInc = mProgressBarMaxSize * mInitProportion / (Real)scriptCount;
    mProgressBarInc /= mNumGroupsInit;
	const std::string& dots = animatedDots();
    mLoadingDescriptionElement->setCaption("Parsing scripts"+dots);
	animate();
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
	animate();
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
	const std::string& dots = animatedDots();
    mLoadingDescriptionElement->setCaption("Loading resources"+dots);
	animate();
    mWindow->update();
}
void LoadingBar::resourceLoadStarted(const ResourcePtr& resource)
{
    mLoadingCommentElement->setCaption(resource->getName());
	animate();
    mWindow->update();
}
void LoadingBar::resourceLoadEnded(void)
{
}
void LoadingBar::worldGeometryStageStarted(const String& description)
{
    mLoadingCommentElement->setCaption(description);
	animate();
    mWindow->update();
}
void LoadingBar::worldGeometryStageEnded(void)
{
    mLoadingBarElement->setWidth(
        mLoadingBarElement->getWidth() + mProgressBarInc);
	animate();
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

    //----------#######################################################

