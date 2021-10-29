#include "StringConversion.h"

std::wstring StringConversion::StringToWide(std::string str)
{
	std::wstring wideString(str.begin(), str.end());
	return wideString;
}