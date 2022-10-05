#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include "WindowMoveObserver.h"
#include <list>

class BackGroundLayer : public cocos2d::Layer,public ObserverSubject
{
private:
	int m_pixStepMapX;//图片X方向/64 的大小  64x64->1,1
	int m_pixStepMapY;//图片Y方向/64 的大小  64x128->1,2
	float m_scale;
	float m_lastScale;
	float m_shitf;
	bool dir[4] = { false,false,false,false };

	std::list<WindowMoveObserver*> _pObserverList;
public:
	void Attach(WindowMoveObserver* pObserver) override
	{
		_pObserverList.push_back(pObserver);
	}

	void Detach(WindowMoveObserver* pObserver) override
	{
		_pObserverList.remove(pObserver);
	}

	void Notify() override
	{
		auto begin = _pObserverList.begin();
		auto end = _pObserverList.end();
		while (begin != end)
		{
			(*begin)->Update(m_centerPoint.x, m_centerPoint.y, m_scale);
			begin++;
		}
	}

	static cocos2d::Layer* createScene(Layer* mainScene);
	CREATE_FUNC(BackGroundLayer);
	virtual bool init();
	void update(float delta);
	void InitMap();
	void UpdataBack();

private:
	cocos2d::Point m_centerPoint;
	cocos2d::Point m_mousePoint;
	cocos2d::TextureCache* m_textureCache;
	cocos2d::Texture2D* m_texture;
	cocos2d::Sprite* backTileModel;
	cocos2d::Size spSize;
	cocos2d::Point m_stPoint;
	cocos2d::Point m_visCenterPoint;
	cocos2d::Size m_blockSize; //地图图片大小
	cocos2d::Size m_visSize; //窗口的大小
	cocos2d::Vector<Node*> m_children;
private:
	cocos2d::Point CalSpPoint(int x, int y);
private:
	void onMouseScroll(cocos2d::Event* event);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif // __BACKGROUND_LAYER_H__
