#pragma once
#include <string>

#ifdef UTILS_DLL
    #define UTILS_API __declspec(dllexport)
#else
    #define UTILS_API __declspec(dllimport)
#endif

UTILS_API void print_message(const std::string& message);
