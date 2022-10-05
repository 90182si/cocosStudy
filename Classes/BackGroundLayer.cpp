#include "BackGroundLayer.h"
#include "Definition.h"
#include "TransText.h"

USING_NS_CC;

cocos2d::Layer* BackGroundLayer::createScene(Layer* mainScene)
{
    return BackGroundLayer::create();
}

bool BackGroundLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    m_visSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    m_visCenterPoint = Point(m_visSize.width / 2, m_visSize.height / 2);
    m_centerPoint = Point(m_visSize.width / 2, m_visSize.height / 2);
    m_mousePoint = Point(m_visSize.width / 2, m_visSize.height / 2);
    m_lastScale = m_scale = SCALE_INIT_VALUE;
    m_shitf = SHIFT_INIT_VALUE;

    //初始化键盘鼠标控制
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(BackGroundLayer::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(BackGroundLayer::onKeyReleased, this);
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseScroll = CC_CALLBACK_1(BackGroundLayer::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    //初始化图集
    Image* img = new Image();
    img->initWithImageFile(BACKGROUND_IMAGE);
    m_textureCache = new TextureCache();
    m_textureCache->addImage(img, "background");
    m_texture = m_textureCache->getTextureForKey("background");

    //初始化地图模板
    backTileModel = Sprite::createWithTexture(m_texture);
    m_blockSize = backTileModel->getContentSize();
    m_pixStepMapX = ceil(m_visSize.width / (m_blockSize.width * MIN_VIEW_SCALE)) + 1;
    m_pixStepMapY = ceil(m_visSize.height / (m_blockSize.height * MIN_VIEW_SCALE)) + 1;
    spSize = Size(m_blockSize.width * m_scale, m_blockSize.height * m_scale);
    for (int x = 0; x < m_pixStepMapX * m_pixStepMapY; x++)
    {
        auto backTile = Sprite::createWithTexture(m_texture);
        addChild(backTile);
    }
    m_children = getChildren();

    m_stPoint = Point(0, 0);

    InitMap();
    scheduleUpdate();

    return true;
}

void BackGroundLayer::update(float delta)
{
    int step = MOVE_STEP_VALUE * m_shitf;
    if (dir[0] == true)
    {
        m_centerPoint.y += step;
    }
    if (dir[1] == true)
    {
        m_centerPoint.y -= step;
    }
    if (dir[2] == true)
    {
        m_centerPoint.x -= step;
    }
    if (dir[3] == true)
    {
        m_centerPoint.x += step;
    }
    UpdataBack();
}

float yu(float a, float b)
{
    if (a > 0)
    {
        a = a - ((int)(a / b)) * b;
    }
    else
    {
        a = ((int)(-a / b)+1) * b + a;
    }
    return a;
}

void BackGroundLayer::InitMap()
{
    spSize = Size(m_blockSize.width * m_scale, m_blockSize.height * m_scale);

    int spIndex = 0;
    float rate = m_scale / m_lastScale - 1.0;

    m_centerPoint.x += (m_centerPoint.x - m_mousePoint.x) * rate;
    m_centerPoint.y += (m_centerPoint.y - m_mousePoint.y) * rate;
    for (auto sp : m_children)
    {
        sp->setContentSize(spSize);
        Point pt = CalSpPoint(spIndex % m_pixStepMapX, spIndex / m_pixStepMapX);
        sp->setPosition(pt);
        spIndex++;
    }

    Notify();

    m_mousePoint = m_centerPoint;
}

void BackGroundLayer::UpdataBack()
{
    InitMap();
}

cocos2d::Point BackGroundLayer::CalSpPoint(int x, int y)
{
    Point ct = Point(m_centerPoint.x + x * spSize.width,m_centerPoint.y  + y * spSize.height);

    ct.x = yu(ct.x, m_pixStepMapX * spSize.width);
    ct.y = yu(ct.y, m_pixStepMapY * spSize.height);

    ct.x -= spSize.width / 2;
    ct.y -= spSize.height / 2;
    return ct;
}

void BackGroundLayer::onMouseScroll(Event* event)
{
    m_lastScale = m_scale;
    EventMouse* e = (EventMouse*)event;
    if (e->getScrollY() == -MOUSE_SCROLL_DIR && m_scale * SCALE_CHANGE_VALUE < MAX_VIEW_SCALE)
    {
        m_scale *= SCALE_CHANGE_VALUE;
    }
    else if (e->getScrollY() == MOUSE_SCROLL_DIR && m_scale / SCALE_CHANGE_VALUE > MIN_VIEW_SCALE)
    {
        m_scale /= SCALE_CHANGE_VALUE;
    }
    m_mousePoint = e->getLocationInView();
}

void BackGroundLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        dir[0] = true;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        dir[2] = true;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        dir[3] = true;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
        dir[1] = true;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_SHIFT) {
        m_shitf = SHIFT_PRESSED_VALUE;
    }
}

void BackGroundLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        dir[0] = false;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        dir[2] = false;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        dir[3] = false;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
        dir[1] = false;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_SHIFT) {
        m_shitf = SHIFT_INIT_VALUE;
    }
}
