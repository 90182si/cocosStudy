#ifndef __ENTITY_STRUCT_H__
#define __ENTITY_STRUCT_H__

#include "EsComponent.h"
#include "ComponentMouseDemo.h"
#include "cocos2d.h"

class EntityStruct : public cocos2d::Sprite, public ESComponent
{
public:
	cocos2d::Rect m_rect;
public:
	static EntityStruct* create(const char* name)
	{
		EntityStruct* sprite = new EntityStruct();
		if (sprite && sprite->initWithFile(name))
		{
			sprite->autorelease();

			auto mouseListener = cocos2d::EventListenerMouse::create();
			sprite->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, sprite);
			sprite->AddComomponent(new ComponentMouseDemo(sprite,mouseListener));

			sprite->schedule(CC_SCHEDULE_SELECTOR(EntityStruct::walk), 0);
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	EntityStruct() {};
	~EntityStruct(){}

	int k = 0;
	int x = 0;
	void walk(float dt)
	{
		if (k == 10)
		{
			int y = rand() % 8;
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
			m_rect.origin.y += 0.1;
		}
		else if (x == 1)
		{
			m_rect.origin.x+= 0.1;
		}
		else if (x == 2)
		{
			m_rect.origin.y-= 0.1;
		}
		else if (x == 3)
		{
			m_rect.origin.x-= 0.1;
		}
		k++;
	}
	void setMyRect(cocos2d::Rect rect)
	{
		m_rect = rect;
	}
};

#endif // __ENTITY_STRUCT_H__
