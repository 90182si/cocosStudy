#include "TransText.h"
USING_NS_CC;

TransText TransText::instance;
TransText::TransText()
{
	auto txt_vec = FileUtils::getInstance()->getValueVectorFromFile("string.xml");
	txt_map = txt_vec.at(0).asValueMap();
}
std::string TransText::ChineseWord(const char* wordId)
{
	std::string ret = txt_map.at(wordId).asString();

	return ret;
}