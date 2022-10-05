#ifndef __ENTITY_STRUCT_H__
#define __ENTITY_STRUCT_H__

#include "EsComponent.h"
#include "ComponentMouseDemo.h"
#include "cocos2d.h"

class EntityStruct : public cocos2d::Sprite, public ESComponent
{
public:
	cocos2d::Rect m_rect;
	cocos2d::Rect m_nextRect;
public:
	static EntityStruct* create(const char* name)
	{
		EntityStruct* sprite = new EntityStruct();
		if (sprite && sprite->initWithFile(name))
		{
			sprite->autorelease();

			auto mouseListener = cocos2d::EventListenerMouse::create();
			sprite->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, sprite);
			//sprite->AddComomponent(new ComponentMouseDemo(sprite,mouseListener));

			sprite->schedule(CC_SCHEDULE_SELECTOR(EntityStruct::walk), 0);
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	static EntityStruct* createWithTexture(cocos2d::Texture2D* texture)
	{
		EntityStruct* sprite = new EntityStruct();
		if (sprite && sprite->initWithTexture(texture))
		{
			sprite->autorelease();

			auto mouseListener = cocos2d::EventListenerMouse::create();
			sprite->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, sprite);
			//sprite->AddComomponent(new ComponentMouseDemo(sprite,mouseListener));

			sprite->schedule(CC_SCHEDULE_SELECTOR(EntityStruct::walk), 0);
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	EntityStruct() {};
	~EntityStruct(){}

	int k = 0;
	int x = -1;
	float w = 0.25;
	void walk(float dt)
	{
		
		if (k == 20)
		{
			int y = rand() % 4;
			if (y > 3)
			{
				x = -1;
			}
			else
			{
				x = y;
				
			}
			k = 0;
		}
		else if (k == 0) {
			int y = rand() % 4;
			if (y > 3)
			{
				x = -1;
			}
			else
			{
				x = y;

			}
			k = 0;
		}
		if (x == 0)
		{
			m_nextRect.origin.y = m_rect.origin.y + w;
			m_nextRect.origin.x = m_rect.origin.x;
		}
		else if (x == 1)
		{
			m_nextRect.origin.y = m_rect.origin.y;
			m_nextRect.origin.x = m_rect.origin.x + w;
		}
		else if (x == 2)
		{
			m_nextRect.origin.y = m_rect.origin.y - w;
			m_nextRect.origin.x = m_rect.origin.x;
		}
		else if (x == 3)
		{
			m_nextRect.origin.y = m_rect.origin.y;
			m_nextRect.origin.x = m_rect.origin.x - w;
		}
		
		//go();
	}
	void go()
	{
		/*if (m_nextRect.origin.x < -100-w/2 || m_nextRect.origin.x>200+w/2 || 
			m_nextRect.origin.y < -100-w/2 || m_nextRect.origin.y>200+w/2) {
			k = 0;
			return;
		}*/
		if (x == 0)
		{
			m_rect.origin.y += w;
			k++;
		}
		else if (x == 1)
		{
			m_rect.origin.x += w;
			k++;
		}
		else if (x == 2)
		{
			m_rect.origin.y -= w;
			k++;
		}
		else if (x == 3)
		{
			m_rect.origin.x -= w; 
			k++;
		}
		
	}
	void setMyRect(cocos2d::Rect rect)
	{
		m_nextRect = m_rect = rect;
	}
};

#endif // __ENTITY_STRUCT_H__
