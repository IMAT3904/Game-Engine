#pragma once
#include <inttypes.h>
#include "include/platform/codes.h"


namespace Engine {
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, WindowMoved, MouseButtonPressed, MouseButtonReleased,
		MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryWindow = 1 << 0, //00000001
		EventCategoryInput = 1 << 1, //00000010
		EventCategoryKeyboard = 1 << 2, //00000100
		EventCategoryMouse = 1 << 3, //00001000
		EventCategoryMouseButton = 1 << 4 //00010000
	};

	class Event {
	public:
		virtual EventType gettype() const = 0;
		virtual int32_t getcategoryflags() const = 0;
		inline bool handled() const { return m_handled; }
		inline void handle(bool ishandled) { m_handled = ishandled; }
		inline bool isincategory(EventCategory category) const { return getcategoryflags() & category; }
	protected:
		bool m_handled = false;
	};
}