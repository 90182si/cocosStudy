#ifndef __COMPONENT_MOUSE_DEMO_H__
#define __COMPONENT_MOUSE_DEMO_H__

#include "cocos2d.h"
#include "ESComponent.h"
#include "ComponentCom.h"

class EntityStruct;
class ComponentMouseDemo : public ComponentCom
{
public:
	ComponentMouseDemo(EntityStruct* sprite, cocos2d::EventListenerMouse* mouseListener);
	~ComponentMouseDemo(){}
};

#endif // __COMPONENT_MOUSE_DEMO_H__
