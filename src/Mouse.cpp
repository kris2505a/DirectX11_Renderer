#include "Mouse.h"
#include <Windows.h>

bool Mouse::m_left       = false;
bool Mouse::m_right      = false;
bool Mouse::m_middle     = false;
bool Mouse::m_inWindow   = false;
bool Mouse::m_firstMove  = true;
int  Mouse::m_xPos       = 0;
int  Mouse::m_yPos       = 0;
int  Mouse::m_wheel      = 0;
float Mouse::m_deltaX	 = 0.0f;
float Mouse::m_deltaY    = 0.0f;

void Mouse::buttonDown(WPARAM button) {
	switch (button) {
	case VK_LBUTTON:
		m_left     = true;
		break;

	case VK_RBUTTON:
		m_right    = true;
		break;

	case VK_MBUTTON:
		m_middle   = true;
		break;
	}
}

void Mouse::buttonUp(WPARAM button) {
	switch (button) {
	case VK_LBUTTON:
		m_left     = false;
		break;

	case VK_RBUTTON:
		m_right    = false;
		break;

	case VK_MBUTTON:
		m_middle   = false;
		break;
	}
}

void Mouse::move(int x, int y) {
	
	float prevX = static_cast <float>(m_xPos);
	float prevY = static_cast <float>(m_yPos);

	m_xPos = x;
	m_yPos = y;

	m_deltaX = static_cast <float> (m_xPos) - prevX;
	m_deltaY = static_cast <float> (m_yPos) - prevY;
	
	if (m_firstMove) {
		m_deltaX = 0.0f;
		m_deltaY = 0.0f;
		m_firstMove = false;
	}
}

void Mouse::scroll(int delta) {
	m_wheel += delta;
	while (m_wheel >= WHEEL_DELTA) {
		m_wheel -= WHEEL_DELTA;
	}
	while (m_wheel <= WHEEL_DELTA) {
		m_wheel += WHEEL_DELTA;
	}
}

bool Mouse::isInWindow() {
	return m_inWindow;
}

void Mouse::inWindow() {
	m_inWindow = true;
}

void Mouse::offWindow() {
	m_inWindow = false;
}