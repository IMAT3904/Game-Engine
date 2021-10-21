#pragma once
#include "event.h"
#include <glm/glm.hpp>

namespace Engine {
	class KeyboardEvent : public Event {
		virtual inline int32_t getcategoryflags() const override { return EventCategoryKeyboard | EventCategoryInput; }
	};

	class KeyPressed : public Event {
	public:
		KeyPressed(int key) : keycode(key){};
		static EventType getstatictype() { return EventType::KeyPressed; }
		virtual inline EventType gettype() const override { return EventType::KeyPressed; }
		virtual inline int32_t getcategoryflags() const override { return EventCategoryKeyboard; }
		inline int getkeycode() const { return keycode; }
	private:
		int keycode;
	};

	class KeyReleased : public Event {
	public:
		KeyReleased(int key) : keycode(key) {};
		static EventType getstatictype() { return EventType::KeyReleased; }
		virtual inline EventType gettype() const override { return EventType::KeyReleased; }
		virtual inline int32_t getcategoryflags() const override { return EventCategoryKeyboard; }
		inline int getkeycode() const { return keycode; }
	private:
		int keycode;
	};
}