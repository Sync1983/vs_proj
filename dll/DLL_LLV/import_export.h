#pragma once

#ifdef DLL_LLV_EXPORTS
#define DLL_LLV_API __declspec(dllexport)
#else
#define DLL_LLV_API __declspec(dllimport)
#endif