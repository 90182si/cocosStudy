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
	void Update(float x, float y, float scale) override
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
				if (m_tree.isEmpty(rectPoint[2])&& m_tree.isEmpty(rectPoint[3]) && 
					m_tree.isEmpty(GameToolV_1::Point((rectPoint[2].x+ rectPoint[3].x)/2, (rectPoint[2].y + rectPoint[3].y) / 2)))
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
			sp->setPosition(cocos2d::Point(x + rect.origin.x * size.width/nw + size.width / 2,
				y + rect.origin.y * size.height/nh + size.height / 2));
		}

		m_tree.clearup();
		//cocos2d::
	}
	

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
