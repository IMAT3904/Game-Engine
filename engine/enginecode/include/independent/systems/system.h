/** \file system.h
*/

#pragma once

#include <cstdarg>

/**
\class Interface class for all systems
*/

namespace Engine {
	/** \class System
** \brief A system class that runs the systems included in the engine


**/
	enum class SystemSignal { None = 0 };

	class System
	{
	public:
		virtual ~System() {}; //!< Deconstructor
		virtual void start(SystemSignal init = SystemSignal::None, ...) = 0; //!< Start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0; //!< Stop the system
	};
}
