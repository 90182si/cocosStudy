#ifndef __ESCOMPONENT_H__
#define __ESCOMPONENT_H__

#include "ComponentCom.h"
#include <list>
class ESComponent
{
private:
	std::list<ComponentCom*> m_listComponent;
public:
	ESComponent() {}
	virtual ~ESComponent() {
		m_listComponent.clear();
	}

	void AddComomponent(ComponentCom* child)
	{
		m_listComponent.push_back(child);
	}
	void RemoveComomponent(ComponentCom* child)
	{
		auto it = std::find(m_listComponent.begin(), m_listComponent.end(), child);
		if (it != m_listComponent.end())
		{
			m_listComponent.erase(it);
		}
	}
};

#endif // __ESCOMPONENT_H__
