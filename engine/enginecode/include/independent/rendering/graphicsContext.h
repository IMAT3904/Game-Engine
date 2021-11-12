#pragma once

namespace Engine {
	class GraphicsContext {
	public:
		virtual void init() = 0;
		virtual void swapbuffers() = 0;
	};
}