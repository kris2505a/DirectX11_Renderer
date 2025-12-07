#pragma once
#include <bitset>
#include <Windows.h>

#define kW 0x57 
#define kA 0x41
#define kS 0x53
#define kD 0x44
#define kQ 0x51
#define kE 0x45
#define TILDE 0x60

class Keyboard {
	friend class Input;
	friend class Window;



public:
	Keyboard() = delete;
	~Keyboard() = delete;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	Keyboard(Keyboard&&) = delete;
	Keyboard& operator=(Keyboard&&) = delete;
	
	static void clearState();
	static bool repeatStatus();

	static bool isKeyDown(int key) {
		return m_keys[key];
	}
	
private:
	static void keyPressed(WPARAM key);
	static void keyReleased(WPARAM key);
	

private:
	static std::bitset <256> m_keys;
	static bool m_repeat;
};