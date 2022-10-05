#include "ComponentMouseDemo.h"
#include "EntityStruct.h"

ComponentMouseDemo::ComponentMouseDemo(EntityStruct* sprite, cocos2d::EventListenerMouse* mouseListener)
{
	mouseListener->onMouseDown = [sprite](cocos2d::Event* event)
	{
		cocos2d::EventMouse* e = (cocos2d::EventMouse*)event;
		cocos2d::Point p = e->getLocationInView();
		if (sprite->getBoundingBox().containsPoint(p))
		{
			//This considers the sprite as a simple square. For a more precise collision detection you need to implement your own method.
			cocos2d::Point st = sprite->getPosition() - p;
			if (st.y > fabs(st.x))
			{
				sprite->m_rect.origin.y--;
			}
			else if (-st.y > fabs(st.x))
			{
				sprite->m_rect.origin.y++;
			}
			else if (st.x > fabs(st.y))
			{
				sprite->m_rect.origin.x--;
			}
			else if (-st.x > fabs(st.y))
			{
				sprite->m_rect.origin.x++;
			}
		}
	};
}
