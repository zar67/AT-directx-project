#include <comdef.h>

#include "ErrorLogger.h"
#include "StringConversion.h"

void ErrorLogger::Log(std::string message)
{
	std::string errorMessage = "Error:" + message;
	MessageBoxA(NULL, errorMessage.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hResult, std::string message)
{
	_com_error error(hResult);
	std::wstring errorMessage = L"Error:" + StringConversion::StringToWide(message) + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hResult, std::wstring message)
{
	_com_error error(hResult);
	std::wstring errorMessage = L"Error:" + message + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_ICONERROR);
}