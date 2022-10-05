#ifndef __TRANSTEXT_H__
#define __TRANSTEXT_H__

#include "cocos2d.h"
#include "string.h"
#define TC(worldid) TransText::getInstance()->ChineseWord(worldid).c_str()

class TransText
{
private:
	static TransText instance;

	cocos2d::ValueMap txt_map;
	TransText();
public:
	static TransText* getInstance() {
		return &instance;
	}
	std::string ChineseWord(const char* wordId);
};

#endif // __TRANSTEXT_H__
