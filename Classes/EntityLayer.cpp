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

void EntityLayer::Update(float x, float y, float scale)
{

	for (auto draw : m_drawNodes) {
		draw->clear();
		m_tree.getAllRect();
		for (int i = 0; i < m_tree.m_rects.size(); i++) {

			GameToolV_1::Rect r = m_tree.m_rects[i];
			draw->drawRect(cocos2d::Vec2(x + r.x * scale * 45, y + r.y * scale * 45),
				cocos2d::Vec2(x + (r.x + r.width) * scale * 45, y + (r.y + r.height) * scale * 45), cocos2d::Color4F(0, 0, 1, 0.45));
		}
	}
	for (auto sp : m_entity)
	{
		cocos2d::Rect rect = sp->m_rect;
		int nw = rect.size.width / 45;
		int nh = rect.size.height / 45;
		cocos2d::Size size = cocos2d::Size(rect.size.width * scale, rect.size.height * scale);
		sp->setContentSize(size);

		GameToolV_1::Rect objRect(sp->m_nextRect.origin.x, sp->m_nextRect.origin.y,
			sp->m_nextRect.size.width / 45, sp->m_nextRect.size.height / 45);
		std::array<GameToolV_1::Point, 4> rectPoint{
				GameToolV_1::Point(objRect.x, objRect.y),
				GameToolV_1::Point(objRect.x + objRect.width, objRect.y),
				GameToolV_1::Point(objRect.x, objRect.y + objRect.height),
				GameToolV_1::Point(objRect.x + objRect.width, objRect.y + objRect.height)
		};
		if (sp->x == 0) {
			if (m_tree.isEmpty(rectPoint[2]) && m_tree.isEmpty(rectPoint[3]) &&
				m_tree.isEmpty(GameToolV_1::Point((rectPoint[2].x + rectPoint[3].x) / 2, (rectPoint[2].y + rectPoint[3].y) / 2)))
			{
				sp->go();
				m_tree.thrownNode(sp);
				GameToolV_1::Rect objRect1(sp->m_rect.origin.x, sp->m_rect.origin.y,
					sp->m_rect.size.width / 45, sp->m_rect.size.height / 45);
				m_tree.addNode(sp, objRect1);
			}
			else {
				sp->k = 0;
			}
		}
		else if (sp->x == 1) {
			if (m_tree.isEmpty(rectPoint[1]) && m_tree.isEmpty(rectPoint[3]) &&
				m_tree.isEmpty(GameToolV_1::Point((rectPoint[1].x + rectPoint[3].x) / 2, (rectPoint[1].y + rectPoint[3].y) / 2)))
			{
				sp->go();
				m_tree.thrownNode(sp);
				GameToolV_1::Rect objRect1(sp->m_rect.origin.x, sp->m_rect.origin.y,
					sp->m_rect.size.width / 45, sp->m_rect.size.height / 45);
				m_tree.addNode(sp, objRect1);
			}
			else {
				sp->k = 0;
			}
		}
		else if (sp->x == 2) {
			if (m_tree.isEmpty(rectPoint[0]) && m_tree.isEmpty(rectPoint[1]) &&
				m_tree.isEmpty(GameToolV_1::Point((rectPoint[0].x + rectPoint[1].x) / 2, (rectPoint[0].y + rectPoint[1].y) / 2)))
			{
				sp->go();
				m_tree.thrownNode(sp);
				GameToolV_1::Rect objRect1(sp->m_rect.origin.x, sp->m_rect.origin.y,
					sp->m_rect.size.width / 45, sp->m_rect.size.height / 45);
				m_tree.addNode(sp, objRect1);
			}
			else {
				sp->k = 0;
			}
		}
		else if (sp->x == 3) {
			if (m_tree.isEmpty(rectPoint[0]) && m_tree.isEmpty(rectPoint[2]) &&
				m_tree.isEmpty(GameToolV_1::Point((rectPoint[0].x + rectPoint[2].x) / 2, (rectPoint[0].y + rectPoint[2].y) / 2)))
			{
				sp->go();
				m_tree.thrownNode(sp);
				GameToolV_1::Rect objRect1(sp->m_rect.origin.x, sp->m_rect.origin.y,
					sp->m_rect.size.width / 45, sp->m_rect.size.height / 45);
				m_tree.addNode(sp, objRect1);
			}
			else {
				sp->k = 0;
			}
		}

		//sp->go();
		sp->setPosition(cocos2d::Point(x + rect.origin.x * size.width / nw + size.width / 2,
			y + rect.origin.y * size.height / nh + size.height / 2));
	}

	m_tree.clearup();
	//cocos2d::
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
