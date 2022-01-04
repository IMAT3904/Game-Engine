#pragma once

/** \file RenderAPI.h
*/

namespace Engine {
	/** \class RenderAPI
** \brief class to decide on what API is being used


**/
	class RenderAPI {
	public:
		enum class API {None = 0, OpenGL = 1, Direct3D = 2, Vulkan = 3}; //!< an enum class named API with values to explain what API is being used
		static API getAPI() { return sAPI; } //!< returns the API
	private:
		static API sAPI; //!< static API of what is being used
	};
}