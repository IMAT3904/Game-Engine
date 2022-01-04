#pragma once
#include "event.h"
#include <glm/glm.hpp>

/** \file windowsevent.h
*/

namespace Engine {
	/** \class WindowCloseEvent
** \brief An override class that contains the data for the Window Close Event


**/
	class WindowCloseEvent : public Event {
		static EventType getstatictype() { return EventType::WindowClose; } //!< get the static type of event
		virtual inline EventType gettype() const override { return EventType::WindowClose; } //!< get the type
		virtual int32_t getcategoryflags() const override { return EventCategoryWindow; } //!< get the catagory flags
	};
	/** \class WindowResizeEvent
** \brief An override class that contains the data for the Window Resize Event


**/

	class WindowResizeEvent : public Event {
		public:
			WindowResizeEvent(int32_t width, int32_t height) : m_width(width), m_height(height) {} //!< a constructor to get the window data for resizing
			static EventType getstatictype() { return EventType::WindowResize; }  //!< get the static type of event
			virtual inline EventType gettype() const override { return EventType::WindowResize; } //!< get the type
			virtual int32_t getcategoryflags() const override { return EventCategoryWindow; } //!< get the catagory flags
			inline glm::vec2 getsize() const {return glm::vec2{m_width,m_height}; } //!< gets the new size for the window
		private:
			int32_t m_width; //!< the width
			int32_t m_height;//!< the height
	};

	/** \class WindowFocusEvent
** \brief An override class that contains the data for the Window Focus Event


**/

	class WindowFocusEvent : public Event {
	public:
		WindowFocusEvent() {}; //!< default constructor
		static EventType getstatictype() { return EventType::WindowFocus; } //!< get the static type of event
		virtual inline EventType gettype() const override {return EventType::WindowFocus; } //!< get the type
		virtual inline int32_t getcategoryflags() const override { return EventCategoryWindow; } //!< get the catagory flags
	};

	/** \class WindowLostFocusEvent
** \brief An override class that contains the data for the Window Lost Focus Event


**/

	class WindowLostFocusEvent : public Event {
	public:
		WindowLostFocusEvent() {}; //!< default constructor
		static EventType getstatictype() { return EventType::WindowLostFocus; } //!< get the static type of event
		virtual inline EventType gettype() const override { return EventType::WindowLostFocus; } //!< get the type
		virtual inline int32_t getcategoryflags() const override { return EventCategoryWindow; }//!< get the catagory flags
	};

	/** \class WindowMovedEvent
** \brief An override class that contains the data for the Window Moved Event


**/

	class WindowMovedEvent : public Event {
	public:
		WindowMovedEvent(int32_t x, int32_t y) : xpos(x),ypos(y) {}; //!< a constructor to get the window data for the moved window
		static EventType getstatictype() { return EventType::WindowMoved; } //!< get the static type of event
		virtual inline EventType gettype() const override { return EventType::WindowMoved; } //!< get the type
		virtual inline int32_t getcategoryflags() const override { return EventCategoryWindow; } //!< get the catagory flags
		inline int32_t getx() const { return xpos; } //!< returns the x position
		inline int32_t gety() const { return ypos; } //!< returns the y position
		inline glm::vec2 getpos() const { return glm::vec2{ xpos,ypos }; } //!< gets the new position of the window
	private:
		int32_t xpos; //!< the x position
		int32_t ypos; //!< the y position
	};
}