/* ------------------------------------------------- */
/* Filename: ErrorLogger.h                           */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the ErrorLogger class.     */
/* The ErrorLogger logs errors through MessageBoxes. */
/* ------------------------------------------------- */

#pragma once
#include <string>
#include <Windows.h>

class ErrorLogger
{
public:
	static void Log(std::string message);
	static void Log(HRESULT hResult, std::string message);
	static void Log(HRESULT hResult, std::wstring message);
private:
	static std::wstring StringToWide(std::string str);
};