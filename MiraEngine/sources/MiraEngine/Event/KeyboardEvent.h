#pragma once
#include "Event.h"

namespace Mira {

class MIRA_API KeyboardEvent : public Event {
public:
	int getKey() const { return m_key; }

protected:
	KeyboardEvent(int _key)
		: m_key(_key) { }

private:
	int m_key;
};


class MIRA_API KeyPressedEvent : public KeyboardEvent {
public:
	KeyPressedEvent(int _key, bool _repeat)
		:KeyboardEvent(_key), m_repeat(_repeat) {
	}

	virtual EventType getType() const override {
		return EventType::keyPressed;
	}
	virtual int getCategory() const override {
		return EventCategory::eventKeyboard | EventCategory::eventInput;
	}
	virtual std::string getName() const override {
		return "KeyPressed";
	}
	bool isRepeat() const {
		return m_repeat;
	}
	std::string toString() const override {
		return std::format("KeyPressed: {}", getKey());
	}
	static EventType getStaticType() {
		return EventType::keyPressed;
	}
private:
	bool m_repeat;
};


class MIRA_API KeyReleasedEvent : public KeyboardEvent {
public:
	KeyReleasedEvent(int _key)
		:KeyboardEvent(_key) {
	}

	virtual EventType getType() const override {
		return EventType::keyReleased;
	}
	virtual int getCategory() const override {
		return EventCategory::eventKeyboard | EventCategory::eventInput;
	}
	virtual std::string getName() const override final {
		return "KeyReleased";
	}
	std::string toString() const override {
		return std::format("KeyReleased: {}", getKey());
	}
	static EventType getStaticType() {
		return EventType::keyReleased;
	}
};

} //namespace ends