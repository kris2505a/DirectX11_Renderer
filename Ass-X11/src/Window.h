#pragma once
#include <Windows.h>
#include <memory>
#include <string>

class Window {
public:
	Window(HINSTANCE instance);
	~Window();
	static LRESULT CALLBACK messageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool isOpen() const;
	HWND& getHandle();
	void setWindowTitle(const std::wstring& str);
	void handleMessages();

private:
	void initWndClassEx();
	void initWindowHandle();

private:
	unsigned int m_width;
	unsigned int m_height;
	LPWSTR m_windowName;
	bool m_open;

	
	//WIN32
	LPWSTR m_className;
	WNDCLASSEX m_wc;
	HWND m_handle;
	HINSTANCE m_instance;
	MSG m_message;

};