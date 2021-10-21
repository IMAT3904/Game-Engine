#pragma once
#include "event.h"
#include <glm/glm.hpp>

namespace Engine {
	class MouseEvent : public Event {
		virtual inline int32_t getcategoryflags() const override { return EventCategoryMouse | EventCategoryInput; }
	};

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : mousex(x),mousey(y) {};
		static EventType getstatictype() { return EventType::MouseMoved; }
		virtual inline EventType gettype() const override { return EventType::MouseMoved; }
		virtual inline int32_t getcategoryflags() const override { return EventCategoryMouse; }
		inline glm::vec2 getpos() const { return glm::vec2(mousex, mousey); }
	private:
		float mousex;
		float mousey;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xoff, float yoff) : mousexoffset(xoff), mouseyoffset(yoff) {};
		static EventType getstatictype() { return EventType::MouseScrolled; }
		virtual inline EventType gettype() const override { return EventType::MouseScrolled; }
		virtual inline int32_t getcategoryflags() const override { return EventCategoryMouse; }
		inline float getxoffset() const { return mousexoffset; }
		inline float getyoffset() const { return mouseyoffset; }
	private:
		float mousexoffset;
		float mouseyoffset;
	};

	class MouseButtonPressedEvent : public Event {
	public:
		MouseButtonPressedEvent(int button) : mousebutton(button) {};
		static EventType getstatictype() { return EventType::MouseButtonPressed; }
		virtual inline EventType gettype() const override { return EventType::MouseButtonPressed; }
		virtual inline int32_t getcategoryflags() const override { return EventCategoryMouse; }
		inline int getbutton() const { return mousebutton; }
	private:
		int mousebutton;
	};

	class MouseButtonReleasedEvent : public Event {
	public:
		MouseButtonReleasedEvent(int button) : mousebutton(button) {};
		static EventType getstatictype() { return EventType::MouseButtonReleased; }
		virtual inline EventType gettype() const override { return EventType::MouseButtonReleased; }
		virtual inline int32_t getcategoryflags() const override { return EventCategoryMouse; }
		inline int getbutton() const { return mousebutton; }
	private:
		int mousebutton;
	};
}