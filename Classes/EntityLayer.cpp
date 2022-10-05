#include "EntityLayer.h"
#include "Definition.h"
#include "TransText.h"
#include "BackGroundLayer.h"
#include <iostream>

USING_NS_CC;

cocos2d::Layer* EntityLayer::createScene(Layer* mainScene)
{
    return EntityLayer::create();
}

bool EntityLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //初始化键盘鼠标控制
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(EntityLayer::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(EntityLayer::onKeyReleased, this);
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(EntityLayer::onMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(EntityLayer::onMouseUp, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(EntityLayer::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    //初始化图集
    Image* img = new Image();
    img->initWithImageFile(SPRITE_IMAGE);
    m_textureCache = new TextureCache();
    m_textureCache->addImage(img, "sprite");
    m_texture = m_textureCache->getTextureForKey("sprite");

    //int s[100] = { 0 };
    for (int i = 0; i < 2000; i++)
    {
        int x = rand() % 200-100;
        int y = rand() % 200-100;
        
        //log("%d",i);
        //std::cout << "创建中....." << i << std::endl;
        //clock_t a = clock();
        if (m_tree.isEmpty(GameToolV_1::Point(x, y)) == true)
        {   
            //s[x * 10 + y]++;
            //EntityStruct* sp = EntityStruct::create("spriteDemo2.png");
            EntityStruct* sp = EntityStruct::createWithTexture(m_texture);
            Size size = sp->getContentSize();
            sp->setMyRect(Rect(Vec2(x,y), size));
            m_entity.push_back(sp);
            addChild(sp);
            m_tree.addNode(sp, GameToolV_1::Rect(x, y,1,1));
        }
    }
    auto draw = DrawNode::create();
    this->addChild(draw, 10);
    m_drawNodes.push_back(draw);
    // 画圆
    //draw->drawSegment(Vec2(2,2), Vec2(4,4), 4, Color4F(0, 1, 0, 1));
    //draw->drawSegment(Vec2(10, s.height / 2), Vec2(s.width / 2, s.height / 2), 40, Color4F(1, 0, 1, 0.5));

    Point bg(0,0);
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            /////
        }
    }
    

    scheduleUpdate();

    return true;
}

void EntityLayer::update(float delta)
{
    
}

void EntityLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    
}

void EntityLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    
}

void EntityLayer::onMouseDown(cocos2d::Event* event)
{
}

void EntityLayer::onMouseUp(cocos2d::Event* event)
{
}

void EntityLayer::onMouseMove(cocos2d::Event* event)
{
}
