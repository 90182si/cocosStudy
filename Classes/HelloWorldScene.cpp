#include "HelloWorldScene.h"
#include "MainScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::GoToMainScene), 0.5);
    auto backgroundSprite = Sprite::create("CloseNormal.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backgroundSprite);
    
    return true;
}

void HelloWorld::GoToMainScene(float dt)
{
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}
