#pragma once // Only want pre-compiled headers to compile once

#include <Windows.h>

#include "../resource.h"

#define MAX_NAME_STRING 256

#define HInstance() GetModuleHandle(NULL) // Macro to access the program instance.