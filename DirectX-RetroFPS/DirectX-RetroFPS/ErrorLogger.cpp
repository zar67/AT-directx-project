/* ------------------------------------------------- */
/* Filename: ErrorLogger.cpp                         */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the ErrorLogger class.                            */
/* ------------------------------------------------- */

#include "ErrorLogger.h"
#include <comdef.h>

void ErrorLogger::Log(std::string message)
{
	std::string errorMessage = "Error:" + message;
	MessageBoxA(NULL, errorMessage.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hResult, std::string message)
{
	_com_error error(hResult);
	std::wstring errorMessage = L"Error:" + StringToWide(message) + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hResult, std::wstring message)
{
	_com_error error(hResult);
	std::wstring errorMessage = L"Error:" + message + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_ICONERROR);
}

std::wstring ErrorLogger::StringToWide(std::string str)
{
	std::wstring wideString(str.begin(), str.end());
	return wideString;
}
