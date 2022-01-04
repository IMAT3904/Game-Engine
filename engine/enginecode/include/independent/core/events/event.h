#pragma once
#include <inttypes.h>
#include "include/platform/codes.h"

/** \file event.h
*/

namespace Engine {
	/** \class Event
** \brief A class to determine an events type and if it's handled


**/

/** \class EventType
** \brief A class to get the type of event


**/

/** \class EventCategory
** \brief A class to specify the events catagory


**/
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, MouseButtonPressed, MouseButtonReleased,
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
		virtual EventType gettype() const = 0; //!< get the type of event
		virtual int32_t getcategoryflags() const = 0; //!< get the flags for the catagory
		inline bool handled() const { return m_handled; } //!< is the event handled
		inline void handle(bool ishandled) { m_handled = ishandled; } //!< handle the event
		inline bool isincategory(EventCategory category) const { return getcategoryflags() & category; } //!< the catagory of the event
	protected:
		bool m_handled = false; //!< bool to determine if the event is handled
	};
}