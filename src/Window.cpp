#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <imgui_impl_win32.h>

#include <windowsx.h>
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);                // Use ImGui::GetCurrentContext()


LRESULT CALLBACK Window::messageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	Window* p_window = nullptr;

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
		return true;

	if (msg == WM_NCCREATE) {
		// get "this" from lpCreateParams
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		p_window = static_cast<Window*>(cs->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p_window));
	}
	else {
		// retrieve stored "this"
		p_window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	switch (msg) {
	case WM_DESTROY:
	{
		p_window->m_open = false;
		PostQuitMessage(0);
		break;
	}

	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		if(!(lParam & 0x40000000) || Keyboard::repeatStatus())
			Keyboard::keyPressed(wParam);
		break;
	}

	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		Keyboard::keyReleased(wParam);
		break;
	}

	case WM_XBUTTONDOWN:
	{
		Mouse::buttonDown(VK_MBUTTON);
		break;
	}

	case WM_XBUTTONUP:
	{
		Mouse::buttonUp(VK_MBUTTON);
		break;
	}

	case WM_MOUSEMOVE:
	{
		POINTS pts = MAKEPOINTS(lParam);
		
		if (pts.x >= 0 && pts.x <= p_window->m_width && pts.y >= 0 && pts.y <= p_window->m_height) {
			Mouse::move(pts.x, pts.y);
			if (!Mouse::isInWindow()) {
				SetCapture(p_window->m_handle);
				Mouse::inWindow();
			}
		} else {
			if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
				Mouse::move(pts.x, pts.y);
			} else {
				ReleaseCapture();
				Mouse::offWindow();
			}
		}
		break;
	}

	case WM_MOUSEWHEEL:
	{
		Mouse::scroll(GET_WHEEL_DELTA_WPARAM(wParam));
		break;
	}

	case WM_KILLFOCUS:
	{
		Keyboard::clearState();
		break;
	}

	} //switch ends

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


Window::Window(HINSTANCE instance)
	: m_instance(instance) {

	m_open = true;
	m_width = 1600;
	m_height = 900;
	this->initWndClassEx();
	this->initWindowHandle();
	ShowWindow(m_handle, SW_SHOW);


}

void Window::initWndClassEx() {
	m_className = const_cast<LPWSTR>(L"WinClass");
	m_windowName = const_cast <LPWSTR> (L"Dx-3D");

	m_wc.cbSize = sizeof(WNDCLASSEX);
	m_wc.style = CS_OWNDC;
	m_wc.lpfnWndProc = Window::messageProc;
	m_wc.cbClsExtra = 0;
	m_wc.cbWndExtra = 0;
	m_wc.hInstance = m_instance;
	m_wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	m_wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_wc.lpszMenuName = nullptr;
	m_wc.lpszClassName = m_className;
	m_wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClassEx(&m_wc);
}

void Window::initWindowHandle() {

	unsigned int xPos = (1920 - m_width) / 2;
	unsigned int yPos = (1080 - m_height) / 2;

	m_handle = CreateWindowEx(
		0,
		m_className,
		m_windowName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		xPos, yPos,
		m_width, m_height,
		nullptr,
		nullptr,
		m_instance,
		this
	);
}

bool Window::isOpen() const {
	return m_open;
}

HWND& Window::getHandle() {
	return m_handle;
}

void Window::setWindowTitle(const std::wstring& str) {
	SetWindowText(m_handle, str.c_str());
}

void Window::handleMessages() {
	while (PeekMessage(&m_message, m_handle, 0, 0, PM_REMOVE)) {
		TranslateMessage(&m_message);
		DispatchMessage(&m_message);
	}
}

Window::~Window() {
	DestroyWindow(m_handle);
	ImGui_ImplWin32_Shutdown();
}