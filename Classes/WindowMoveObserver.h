#ifndef __WINDOW_MOVE_OBSERVER_H__
#define __WINDOW_MOVE_OBSERVER_H__

class WindowMoveObserver
{
public:
	virtual ~WindowMoveObserver() {};
	virtual void Update(float x,float y, float scale) = 0;
};
class ObserverSubject
{
public:
	virtual ~ObserverSubject() {};
	virtual void Attach(WindowMoveObserver*) = 0;
	virtual void Detach(WindowMoveObserver*) = 0;
	virtual void Notify() = 0;
};

#endif // __WINDOW_MOVE_OBSERVER_H__
