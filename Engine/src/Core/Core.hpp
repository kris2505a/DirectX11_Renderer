#pragma once

#ifdef BUILD_DLL
    #define MIRA_API __declspec(dllexport)
#else 
    #define MIRA_API __declspec(dllimport)    
#endif