#pragma once

/** \file graphicsContext.h
*/

namespace Engine {
	/** \class GraphicsContext
** \brief The graphics context for the graphics


**/
	class GraphicsContext {
	public:
		virtual void init() = 0; //!< initialisation of the graphics context
		virtual void swapbuffers() = 0; //!< swapping buffers
	};
}