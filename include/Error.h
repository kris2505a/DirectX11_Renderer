#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <dxgidebug.h>

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

#ifdef _DEBUG
#define RUN(dx_call, device_ptr) \
    do { \
        dx_call; \
        ID3D11InfoQueue* infoQueue = nullptr; \
        if (SUCCEEDED((device_ptr)->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&infoQueue)) && infoQueue) { \
            SIZE_T numMessages = infoQueue->GetNumStoredMessages(); \
            std::string out; \
            for (SIZE_T i = 0; i < numMessages; ++i) { \
                SIZE_T messageLength = 0; \
                infoQueue->GetMessage(i, nullptr, &messageLength); \
                std::vector<char> bytes(messageLength); \
                D3D11_MESSAGE* message = (D3D11_MESSAGE*)bytes.data(); \
                if (SUCCEEDED(infoQueue->GetMessage(i, message, &messageLength))) { \
                    out.append(message->pDescription); \
                    out.append("\n"); \
                } \
            } \
            if (!out.empty()) { \
                std::cout << "DirectX debug error(s)!\n\n"; \
                std::cout << "File: " << __FILE__ << "\n"; \
                std::cout << "Line: " << __LINE__ << "\n\n"; \
                std::cout << "Call: " << #dx_call << "\n\n"; \
                std::cout << out << std::endl; \
                std::exit(1); \
            } \
            infoQueue->ClearStoredMessages(); \
            infoQueue->Release(); \
        } \
    } while (0)
#else
#define RUN(dx_call, device_ptr) dx_call
#endif

#ifdef _DEBUG
#define HRUN(hr_call) \
    do { \
        HRESULT hr__ = hr_call; \
        if (FAILED(hr__)) { \
            std::cout << "DirectX call failed!\n\n"; \
            std::cout << "File: " << __FILE__ << "\n"; \
            std::cout << "Line: " << __LINE__ << "\n\n"; \
            std::cout << "Call: " << #hr_call << "\n"; \
            std::cout << "HRESULT: 0x" << std::hex << (unsigned int)hr__ << std::dec << "\n"; \
            std::cout << "Message: " << HResultToString(hr__) << std::endl; \
            std::exit(1); \
        } \
    } while (0)
#else
#define HRUN(hr_call) hr_call
#endif

inline std::string HResultToString(HRESULT hr)
{
    LPVOID msgBuffer = nullptr;

    DWORD result = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        hr,
        0,
        (LPSTR)&msgBuffer,
        0,
        nullptr
    );

    std::string errorStr;
    if (result && msgBuffer) {
        errorStr = static_cast<LPCSTR>(msgBuffer);
        LocalFree(msgBuffer);
    }
    else {
        char buf[64];
        snprintf(buf, sizeof(buf), "Unknown error 0x%08X", (unsigned int)hr);
        errorStr = buf;
    }

    return errorStr;
}
