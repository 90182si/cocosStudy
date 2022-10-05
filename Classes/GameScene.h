#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "TransText.h"
#include "BackGroundLayer.h"
#include "2d/CCLayer.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(Scene* mainScene);

    virtual bool init();

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

    
private:
    cocos2d::LayerMultiplex* m_layerMulti;
    BackGroundLayer* m_backLayer;
    Scene* m_mainScene;
};

#endif // __GAME_SCENE_H__
