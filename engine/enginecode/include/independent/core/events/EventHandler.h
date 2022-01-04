#pragma once

#include "windowsEvent.h"
#include "keyboardevent.h"
#include "mouseevent.h"
#include <functional>
/** \file EventHandler.h
*/

namespace Engine {
	/** \class EventHandler
** \brief A class to handle events


**/
	class EventHandler {
	public:
		void setonclosecallback(const std::function<bool(WindowCloseEvent&)>& fn) { m_onclosecallback = fn; } //!< will be set on close
		std::function<bool(WindowCloseEvent&)> getonclosecallback() { return m_onclosecallback; }

		void setonresizecallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onresizecallback = fn; } //!< will be set on resize
		std::function<bool(WindowResizeEvent&)> getonresizecallback() { return m_onresizecallback; }

		void setonmovedcallback(const std::function<bool(WindowMovedEvent&)>& fn) { m_onmovedcallback = fn; } //!< will be set on moving the window
		std::function<bool(WindowMovedEvent&)> getonmovedcallback() { return m_onmovedcallback; }

		void setonfocuscallback(const std::function<bool(WindowFocusEvent&)>& fn) { m_ongainfocuscallback = fn; } //!< will be set on window focus
		std::function<bool(WindowFocusEvent&)> getonfocuscallback() { return m_ongainfocuscallback; }

		void setonlostfocuscallback(const std::function<bool(WindowLostFocusEvent&)>& fn) { m_onlostfocuscallback = fn; } //!< will be set on losing focus
		std::function<bool(WindowLostFocusEvent&)> getonlostfocuscallback() { return m_onlostfocuscallback; }

		void setonkeypressedcallback(const std::function<bool(KeyPressed&)>& fn) { m_onkeypressedcallback = fn; } //!< will be set on a key press
		std::function<bool(KeyPressed&)> getonkeypressedcallback() { return m_onkeypressedcallback; }

		void setonkeyreleasedcallback(const std::function<bool(KeyReleased&)>& fn) { m_onkeyreleasedcallback = fn; } //!< will be set on a keys release
		std::function<bool(KeyReleased&)> getonkeyreleasedcallback() { return m_onkeyreleasedcallback; }

		void setonmousepressedcallback(const std::function<bool(MouseButtonPressedEvent&)>& fn) { m_onmousepressedcallback = fn; } //!< will be set on a mouse press
		std::function<bool(MouseButtonPressedEvent&)> getonmousepressedcallback() { return m_onmousepressedcallback; }

		void setonmousereleasedcallback(const std::function<bool(MouseButtonReleasedEvent&)>& fn) { m_onmousereleasedcallback = fn; } //!< will be set on a mouse release
		std::function<bool(MouseButtonReleasedEvent&)> getonmousereleasedcallback() { return m_onmousereleasedcallback; }

		void setonmousemovedcallback(const std::function<bool(MouseMovedEvent&)>& fn) { m_onmousemovedcallback = fn; } //!< will be set on the mouse moving
		std::function<bool(MouseMovedEvent&)> getonmousemovedcallback() { return m_onmousemovedcallback; }

		
	private:
		std::function<bool(WindowCloseEvent&)> m_onclosecallback = std::bind(&EventHandler::defaultonclose,this,std::placeholders::_1); //!< will activate on close
		bool defaultonclose(WindowCloseEvent&) { return false; }

		std::function<bool(WindowResizeEvent&)> m_onresizecallback = std::bind(&EventHandler::defaultonresize, this, std::placeholders::_1); //!< will activate on resize
		bool defaultonresize(WindowResizeEvent&) { return false; }

		std::function<bool(WindowMovedEvent&)> m_onmovedcallback = std::bind(&EventHandler::defaultonmoved, this, std::placeholders::_1); //!< will activate on window movement
		bool defaultonmoved(WindowMovedEvent&) { return false; }

		std::function<bool(WindowFocusEvent&)> m_ongainfocuscallback = std::bind(&EventHandler::defaultonfocus, this, std::placeholders::_1); //!< will activate on window focus
		bool defaultonfocus(WindowFocusEvent&) { return false; }

		std::function<bool(WindowLostFocusEvent&)> m_onlostfocuscallback = std::bind(&EventHandler::defaultonlostfocus, this, std::placeholders::_1); //!< will activate on losing focus
		bool defaultonlostfocus(WindowLostFocusEvent&) { return false; }

		std::function<bool(KeyPressed&)> m_onkeypressedcallback = std::bind(&EventHandler::defaultonkeypress, this, std::placeholders::_1); //!< will activate on a key press
		bool defaultonkeypress(KeyPressed&) { return false; }

		std::function<bool(KeyReleased&)> m_onkeyreleasedcallback = std::bind(&EventHandler::defaultonkeyreleased, this, std::placeholders::_1); //!< will activate on a key release
		bool defaultonkeyreleased(KeyReleased&) { return false; }

		std::function<bool(MouseButtonPressedEvent&)> m_onmousepressedcallback = std::bind(&EventHandler::defaultonmousepressed, this, std::placeholders::_1); //!< will activate on a mouse press
		bool defaultonmousepressed(MouseButtonPressedEvent&) { return false; }

		std::function<bool(MouseButtonReleasedEvent&)> m_onmousereleasedcallback = std::bind(&EventHandler::defaultonmousereleased, this, std::placeholders::_1); //!< will activate on a mouse release
		bool defaultonmousereleased(MouseButtonReleasedEvent&) { return false; }

		std::function<bool(MouseMovedEvent&)> m_onmousemovedcallback = std::bind(&EventHandler::defaultonmousemoved, this, std::placeholders::_1);//!< will activate on mouse movement
		bool defaultonmousemoved(MouseMovedEvent&) { return false; }
	};
}