#ifndef __ENTITY_LAYER_H__
#define __ENTITY_LAYER_H__

#include "cocos2d.h"
#include "EntityStruct.h"
#include "WindowMoveObserver.h"
#include <vector>
#include "QuadTree.h"
//#include "Quadtree.h"

class BackGroundLayer;
class EntityLayer : public cocos2d::Layer,public WindowMoveObserver
{
private:
	cocos2d::TextureCache* m_textureCache;
	cocos2d::Texture2D* m_texture;
public:
	void Update(float x, float y, float scale) override;

	static cocos2d::Layer* createScene(Layer* mainScene);
	CREATE_FUNC(EntityLayer);
	virtual bool init();
	void update(float delta);

private:
	std::vector<EntityStruct*> m_entity;
	std::vector<cocos2d::DrawNode*> m_drawNodes;
	GameToolV_1::QuadTree<EntityStruct*> m_tree;
private:
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
};

#endif // __ENTITY_LAYER_H__
