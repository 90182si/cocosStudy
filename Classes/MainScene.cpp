#include "MainScene.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("HelloWorld.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backgroundSprite);

    auto playGameButton = ui::Button::create("PlayGame.png");
    playGameButton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - playGameButton->getContentSize().height));
    playGameButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        auto gameScene = GameScene::create();
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            log("--------ShopScene 1----------");      
            Director::getInstance()->pushScene(gameScene);
            //Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene));
            break;
        default:
            break;
        }
    });

    this->addChild(playGameButton);

    return true;
}