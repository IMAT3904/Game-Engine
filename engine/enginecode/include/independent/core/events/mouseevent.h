#pragma once
#include "event.h"
#include <glm/glm.hpp>

/** \file mouseevent.h
*/

namespace Engine {
	/** \class MouseEvent
** \brief A class that controls the Mouse Events


**/
	class MouseEvent : public Event {
		virtual inline int32_t getcategoryflags() const override { return EventCategoryMouse | EventCategoryInput; } //!< gets a list of the flags
	};

	/** \class MouseMovedEvent
** \brief A class that holds the information for the Mouse Moved Event


**/
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : mousex(x),mousey(y) {}; //!< a constructor to get the Mouse Moved Event info
		static EventType getstatictype() { return EventType::MouseMoved; } //!< get the static type of event
		virtual inline EventType gettype() const override { return EventType::MouseMoved; } //!< get the type
		virtual inline int32_t getcategoryflags() const override { return EventCategoryMouse; } //!< get the catagory flags
		inline glm::vec2 getpos() const { return glm::vec2(mousex, mousey); } //!< gets the position for the moved mouse
	private:
		float mousex; //!< mouse x position
		float mousey; //!< mouse y position
	};

	/** \class MouseScrolledEvent
** \brief A class that holds the information for the Mouse Scrolled Event


**/
	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xoff, float yoff) : mousexoffset(xoff), mouseyoffset(yoff) {}; //!< a constructor to get the Mouse Scrolled Event info
		static EventType getstatictype() { return EventType::MouseScrolled; } //!< get the static type of event
		virtual inline EventType gettype() const override { return EventType::MouseScrolled; } //!< get the type
		virtual inline int32_t getcategoryflags() const override { return EventCategoryMouse; } //!< get the catagory flags
		inline float getxoffset() const { return mousexoffset; } //!< gets the offset for the x axis
		inline float getyoffset() const { return mouseyoffset; } //!< gets the offset for the y axis
	private:
		float mousexoffset; //!< mouse x offset
		float mouseyoffset; //!< mouse y offset
	};

	/** \class MouseButtonPressedEvent
** \brief A class that holds the information for the Mouse Button Pressed Event


**/

	class MouseButtonPressedEvent : public Event {
	public:
		MouseButtonPressedEvent(int button) : mousebutton(button) {}; //!< a constructor to get the Mouse Button Pressed Event info
		static EventType getstatictype() { return EventType::MouseButtonPressed; } //!< get the static type of event
		virtual inline EventType gettype() const override { return EventType::MouseButtonPressed; } //!< get the type
		virtual inline int32_t getcategoryflags() const override { return EventCategoryMouse; } //!< get the catagory flags
		inline int getbutton() const { return mousebutton; } //!< gets the button pressed
	private:
		int mousebutton; //!< the mouse button pressed
	};

	/** \class MouseButtonReleasedEvent
** \brief A class that holds the information for the Mouse Button Released Event


**/

	class MouseButtonReleasedEvent : public Event {
	public:
		MouseButtonReleasedEvent(int button) : mousebutton(button) {}; //!< a constructor to get the Mouse Button Released Event info
		static EventType getstatictype() { return EventType::MouseButtonReleased; } //!< get the static type of event
		virtual inline EventType gettype() const override { return EventType::MouseButtonReleased; } //!< get the type
		virtual inline int32_t getcategoryflags() const override { return EventCategoryMouse; } //!< get the catagory flags
		inline int getbutton() const { return mousebutton; } //!< gets the button released
	private:
		int mousebutton; //!< the mouse button released
	};
}