#pragma once
#include "event.h"
#include <glm/glm.hpp>

/** \file keyboardevent.h
*/

namespace Engine {
	/** \class KeyboardEvent
** \brief An override class that contains a list of keyboard events


**/

/** \class KeyPressed
** \brief A class to handle keyboard pressing functionalities


**/

/** \class KeyReleased
** \brief A class to handle keyboard releasing functionalities


**/
	class KeyboardEvent : public Event {
		virtual inline int32_t getcategoryflags() const override { return EventCategoryKeyboard | EventCategoryInput; } //!< gets a list of the flags
	};

	class KeyPressed : public Event {
	public:
		KeyPressed(int key) : keycode(key){}; //!< a constructor to find the key pressed
		static EventType getstatictype() { return EventType::KeyPressed; } //!< get the static type of event
		virtual inline EventType gettype() const override { return EventType::KeyPressed; } //!< get the type
		virtual inline int32_t getcategoryflags() const override { return EventCategoryKeyboard; } //!< get the catagory flags
		inline int getkeycode() const { return keycode; } //!< get the keycode pressed
	private:
		int keycode; //!< the keycode that's been pressed
	};

	class KeyReleased : public Event {
	public:
		KeyReleased(int key) : keycode(key) {};  //!< a constructor to find the key released
		static EventType getstatictype() { return EventType::KeyReleased; } //!< get the static type of event
		virtual inline EventType gettype() const override { return EventType::KeyReleased; } //!< get the type
		virtual inline int32_t getcategoryflags() const override { return EventCategoryKeyboard; } //!< get the catagory flags
		inline int getkeycode() const { return keycode; } //!< get the keycode released
	private:
		int keycode; //!< the keycode that's been released
	};
}