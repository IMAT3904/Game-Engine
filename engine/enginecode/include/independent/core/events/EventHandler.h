#pragma once

#include "windowsEvent.h"
#include <functional>
namespace Engine {
	class EventHandler {
	public:
		void setonclosecallback(const std::function<bool(WindowCloseEvent&)>& fn) { m_onclosecallback = fn; }
		std::function<bool(WindowCloseEvent&)> getonclosecallback() { return m_onclosecallback; }

		void setonresizecallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onresizecallback = fn; }
		std::function<bool(WindowResizeEvent&)> getonresizecallback() { return m_onresizecallback; }

		
	private:
		std::function<bool(WindowCloseEvent&)> m_onclosecallback = std::bind(&EventHandler::defaultonclose,this,std::placeholders::_1);
		bool defaultonclose(WindowCloseEvent&) { return false; }

		std::function<bool(WindowResizeEvent&)> m_onresizecallback = std::bind(&EventHandler::defaultonresize, this, std::placeholders::_1);
		bool defaultonresize(WindowResizeEvent&) { return false; }

		std::function<bool(WindowMovedEvent&)> m_onmovedcallback = std::bind(&EventHandler::defaultonmoved, this, std::placeholders::_1);
		bool defaultonmoved(WindowMovedEvent&) { return false; }

		std::function<bool(WindowFocusEvent&)> m_ongainfocuscallback = std::bind(&EventHandler::defaultonfocus, this, std::placeholders::_1);
		bool defaultonfocus(WindowFocusEvent&) { return false; }

		std::function<bool(WindowLostFocusEvent&)> m_onlostfocuscallback = std::bind(&EventHandler::defaultonlostfocus, this, std::placeholders::_1);
		bool defaultonlostfocus(WindowLostFocusEvent&) { return false; }

		std::function<bool(KeyPressed&)> m_onkeypressedcallback = std::bind(&EventHandler::defaultonkeypress, this, std::placeholders::_1);
		bool defaultonkeypress(KeyPressed&) { return false; }

		std::function<bool(KeyReleased&)> m_onkeyreleasedcallback = std::bind(&EventHandler::defaultonkeyreleased, this, std::placeholders::_1);
		bool defaultonkeyreleased(KeyReleased&) { return false; }

		std::function<bool(MouseButtonPressedEvent&)> m_onmousepressed = std::bind(&EventHandler::defaultonmousepressed, this, std::placeholders::_1);
		bool defaultonmousepressed(MouseButtonPressedEvent&) { return false; }

		std::function<bool(MouseButtonReleasedEvent&)> m_onmousereleased = std::bind(&EventHandler::defaultonmousereleased, this, std::placeholders::_1);
		bool defaultonmousereleased(MouseButtonReleasedEvent&) { return false; }

		std::function<bool(MouseMovedEvent&)> m_onmousemoved = std::bind(&EventHandler::defaultonmousemoved, this, std::placeholders::_1);
		bool defaultonmousemoved(MouseMovedEvent&) { return false; }
	};
}