#pragma once

#include <functional>
//#include "RendererCommon.h"

namespace Engine {
	class RendererCommon;
	class RenderCommand {
	public:
		enum class Commands {ClearDepthBuffer,ClearColourBuffer,ClearColourAndDepthBuffer,SetClearColour};
	private:
		std::function<void(void)> action;
		friend class RenderCommandFactory;
		friend class RendererCommon;
	};

	class RenderCommandFactory {
	public:
		template<typename ...Args> static RenderCommand* CreateCommand(RenderCommand::Commands command, Args&& ...args) {
			RenderCommand* result = new RenderCommand;

			switch (command) {
			case RenderCommand::Commands::ClearColourAndDepthBuffer:
				result->action = GetClearColourDepthBufferCommand();
				return result;
			case RenderCommand::Commands::SetClearColour:
				float r, g, b, a;
				r = 1.0f,
				g = 0.0f,
				b = 0.0f;
				a = 1.0f;

				result->action = GetSetClearColourCommand(r,g,b,a);
				return result;
			}
		}
	private:
		static std::function<void(void)> GetClearColourDepthBufferCommand();
		static std::function<void(void)> GetSetClearColourCommand(float r, float g, float b, float a);
	};
}