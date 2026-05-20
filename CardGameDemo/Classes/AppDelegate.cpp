#include "AppDelegate.h"
#include "Config/GameConfig.h"
#include "Scenes/CardGameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    Director* director = Director::getInstance();
    GLView* glview = director->getOpenGLView();
    if (!glview)
    {
        glview = GLViewImpl::createWithRect(
            "CardGameDemo",
            Rect(0, 0, GameConfig::DESIGN_WIDTH, GameConfig::DESIGN_HEIGHT),
            0.5f);
        director->setOpenGLView(glview);
    }

    glview->setDesignResolutionSize(
        GameConfig::DESIGN_WIDTH,
        GameConfig::DESIGN_HEIGHT,
        ResolutionPolicy::FIXED_WIDTH);

    director->setAnimationInterval(1.0f / 60.0f);
    director->runWithScene(CardGameScene::createScene());

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
