#include "Keyboard.h"
#include <iostream>

std::bitset <256> Keyboard::m_keys;
bool Keyboard::m_repeat = false;

void Keyboard::keyPressed(WPARAM key) {
	if (key < 256) {
		m_keys.set(static_cast<size_t>(key), true);
	}
}

bool Keyboard::repeatStatus() {
	return m_repeat;
}

void Keyboard::clearState() {
	m_keys.reset();
}

void Keyboard::keyReleased(WPARAM key) {
	if (key < 256) {
		m_keys.set(static_cast<size_t>(key), false);
	}
}
