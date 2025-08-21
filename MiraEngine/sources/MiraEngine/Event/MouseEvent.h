#pragma once
#include "Event.h"

namespace Mira {

class MIRA_API MouseMovedEvent : public Event {
public:
	inline int getXPos() const { return m_xPos; }
	inline int getYPos() const { return m_yPos; }

	MouseMovedEvent(int _x, int _y)
		: m_xPos(_x), m_yPos(_y) { }

	virtual EventType getType() const override {
		return EventType::mouseMoved;
	}
	virtual int getCategory() const override {
		return EventCategory::eventMouse | EventCategory::eventInput;
	}
	virtual std::string getName() const override final {
		return "MouseMoved";
	}
	std::string toString() const override {
		return std::format("MouseMoved: {}, {}", getXPos(), getYPos());
	}
	static EventType getStaticType() { 
		return EventType::mouseMoved; 
	}


private:
	int m_xPos, m_yPos;
};

class MIRA_API MouseButtonEvent : public Event {
public:
	inline int getButton() const {
		return m_key;
	}

protected:
	MouseButtonEvent(int _key)
		: m_key(_key) { }

private:
	int m_key;
};

class MIRA_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
	MouseButtonPressedEvent(int _key) 
		:MouseButtonEvent(_key) {}
	virtual EventType getType() const override {
		return EventType::mouseButtonPressed;
	}
	virtual int getCategory() const override {
		return EventCategory::eventMouseButton | EventCategory::eventInput;
	}
	virtual std::string getName() const override final {
		return "MouseButtonPressed";
	}
	std::string toString() const override {
		return std::format("MouseButtonPressed: {}", getButton());
	}
	static EventType getStaticType() {
		return EventType::mouseButtonPressed;
	}
};

class MIRA_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
	MouseButtonReleasedEvent(int _key)
		:MouseButtonEvent(_key) {}
	virtual EventType getType() const override {
		return EventType::mouseButtonReleased;
	}
	virtual int getCategory() const override {
		return EventCategory::eventMouseButton | EventCategory::eventInput;
	}
	virtual std::string getName() const override final {
		return "MouseButtonReleased";
	}
	std::string toString() const override {
		return std::format("MouseButtonReleased: {}", getButton());
	}
	static EventType getStaticType() {
		return EventType::mouseButtonReleased;
	}
};

class MIRA_API MouseScrolledEvent : public Event {
public:
	inline int getXOffset() const { return m_xOffset; }
	inline int getYOffset() const { return m_yOffset; }

	MouseScrolledEvent(int _xOffset, int _yOffset)
		: m_xOffset(_xOffset), m_yOffset(_yOffset) {
	}
	virtual EventType getType() const override {
		return EventType::mouseScrolled;
	}
	virtual int getCategory() const override {
		return EventCategory::eventMouse | EventCategory::eventInput;
	}
	virtual std::string getName() const override final {
		return "MouseScrolled";
	}
	std::string toString() const override {
		return std::format("MouseScrolled: {}, {}", getXOffset(), getYOffset());
	}
	static EventType getStaticType() {
		return EventType::mouseScrolled;
	}
private:
	int m_xOffset, m_yOffset;
};

} //namespace ends