#pragma once

namespace Engine {
	class RenderAPI {
	public:
		enum class API {None = 0, OpenGL = 1, Direct3D = 2, Vulkan = 3};
		static API getAPI() { return sAPI; }
	private:
		static API sAPI;
	};
}