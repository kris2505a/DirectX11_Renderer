#pragma once
#include "Event.h"
#include <MiraEngine/Core/MiraCore.h>

namespace Mira {

class MIRA_API WindowCloseEvent : public Event {
public:

	WindowCloseEvent() = default;
	~WindowCloseEvent() = default;

	virtual EventType getType() const override {
		return EventType::windowClose;
	}
	virtual int getCategory() const override {
		return EventCategory::eventApp;
	}
	virtual std::string getName() const override {
		return "EngineClosed";
	}

	std::string toString() const override {
		return std::format("Engine Closed");
	}
	static EventType getStaticType() {
		return EventType::windowClose;
	}
};

}