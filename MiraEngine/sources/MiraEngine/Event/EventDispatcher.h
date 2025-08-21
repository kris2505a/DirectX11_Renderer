#pragma once
#include "Event.h"

namespace Mira {
class EventDispatcher {
public:
	EventDispatcher(Event& ev)
		:m_event(ev) {}

	template <typename T, typename F>
	bool dispatch(const F& func) {
		if (m_event.getType() == T::getStaticType()) {
			m_event.m_handled = func(static_cast<T&>(m_event));
			return true;
		}
		return false;
	}
private:
	Event& m_event;
};

} // namespace ends