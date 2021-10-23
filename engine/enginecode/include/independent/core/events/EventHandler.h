#pragma once

#include "event.h"
#include <functional>
namespace Engine {
	class EventHandler {
	public:
		void setonclosecallback(const std::is_function<bool(WindowCloseEvent&)>& fn) { m_onclosecallback = fn; }
		std::function<bool(WindowCloseEvent&)> getonclosecallback() { return m_onclosecallback; }

		
	private:
		std::function<bool(WindowCloseEvent&)> m_onclosecallback = std::bind(&EventHandler::defaultonclose,this,std::placeholders::_1);
		bool defaultonclose(WindowCloseEvent&) { return false; }
	};
}