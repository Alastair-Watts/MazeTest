#include "StringUtil.h"

StringUtil::StringUtil()
{
}


string StringUtil::toString(float number) {
	stringstream strs;
	strs << number;
	return strs.str();
}

StringUtil::~StringUtil()
{
}
