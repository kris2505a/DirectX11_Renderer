#pragma once
#include <MiraPreCompHeader.h>
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Core/MiraMacros.h>

enum class EventType {
	none = 0,
	windowClose, windowResize,
	keyPressed, keyReleased,
	mouseMoved, mouseButtonPressed, mouseButtonReleased, mouseScrolled
};

enum EventCategory {
	none = 0,
	eventApp = BIT(1),
	eventInput = BIT(2),
	eventKeyboard = BIT(3),
	eventMouse = BIT(4),
	eventMouseButton = BIT(5)
};

namespace Mira {

class MIRA_API Event {
	friend class EventDispatcher;

public:
	inline bool isHandled() const { return m_handled; }
	virtual EventType getType() const = 0;
	virtual int getCategory() const = 0;
	bool isInCategory(EventCategory category) { return getCategory() & category; }
	virtual std::string getName() const = 0;
	virtual std::string toString() const = 0;

private:
	bool m_handled{ false };
};

} // namespace ends