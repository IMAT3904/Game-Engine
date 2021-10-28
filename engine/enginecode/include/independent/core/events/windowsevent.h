#pragma once
#include "event.h"
#include <glm/glm.hpp>

namespace Engine {
	class WindowCloseEvent : public Event {
		static EventType getstatictype() { return EventType::WindowClose; }
		virtual inline EventType gettype() const override { return EventType::WindowClose; }
		virtual int32_t getcategoryflags() const override { return EventCategoryWindow; }
	};

	class WindowResizeEvent : public Event {
		public:
			WindowResizeEvent(int32_t width, int32_t height) : m_width(width), m_height(height) {}
			static EventType getstatictype() { return EventType::WindowResize; }
			virtual inline EventType gettype() const override { return EventType::WindowResize; }
			virtual int32_t getcategoryflags() const override { return EventCategoryWindow; }
			inline glm::vec2 getsize() const {return glm::vec2{m_width,m_height}; }
		private:
			int32_t m_width;
			int32_t m_height;
	};

	class WindowFocusEvent : public Event {
	public:
		WindowFocusEvent() {};
		static EventType getstatictype() { return EventType::WindowFocus; }
		virtual inline EventType gettype() const override {return EventType::WindowFocus; }
		virtual inline int32_t getcategoryflags() const override { return EventCategoryWindow; }
	};

	class WindowLostFocusEvent : public Event {
	public:
		WindowLostFocusEvent() {};
		static EventType getstatictype() { return EventType::WindowLostFocus; }
		virtual inline EventType gettype() const override { return EventType::WindowLostFocus; }
		virtual inline int32_t getcategoryflags() const override { return EventCategoryWindow; }
	};

	class WindowMovedEvent : public Event {
	public:
		WindowMovedEvent(int32_t x, int32_t y) : xpos(x),ypos(y) {};
		static EventType getstatictype() { return EventType::WindowMoved; }
		virtual inline EventType gettype() const override { return EventType::WindowMoved; }
		virtual inline int32_t getcategoryflags() const override { return EventCategoryWindow; }
		inline int32_t getx() const { return xpos; }
		inline int32_t gety() const { return ypos; }
		inline glm::vec2 getpos() const { return glm::vec2{ xpos,ypos }; }
	private:
		int32_t xpos;
		int32_t ypos;
	};
}