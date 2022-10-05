#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "TransText.h"
#include "EntityLayer.h"
USING_NS_CC;

Scene* GameScene::createScene(Scene* mainScene)
{
    auto scene = GameScene::create();
    scene->m_mainScene = mainScene;
    return scene;
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // creating a keyboard event listener
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //m_layerMulti = LayerMultiplex::create();
    m_backLayer = BackGroundLayer::create();
   // m_layerMulti->addLayer(m_backLayer);
    //m_layerMulti->addLayer(EntityLayer::create());


    EntityLayer* layer = EntityLayer::create();
    addChild(m_backLayer,9);
    addChild(layer,10);
    m_backLayer->Attach(layer);
    //m_layerMulti->switchTo(0);
    return true;

}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
        CCLOG(TC("pressed up"));
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
        CCLOG(TC("pressed left"));
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
        CCLOG(TC("pressed right"));
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
        CCLOG(TC("pressed down"));
    }
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
}