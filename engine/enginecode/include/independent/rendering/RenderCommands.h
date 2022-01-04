#pragma once

#include <functional>
//#include "RendererCommon.h"

/** \file RenderCommands.h
*/

namespace Engine {
	/** \class RenderCommand
** \brief A class that holds render commands to change values in OpenGL


**/
	class RendererCommon;
	class RenderCommand {
	public:
		enum class Commands {ClearDepthBuffer,ClearColourBuffer,ClearColourAndDepthBuffer,SetClearColour}; //!< a list of available commands
	private:
		std::function<void(void)> action; //!< the ongoing action being made
		friend class RenderCommandFactory;
		friend class RendererCommon;
	};


	/** \class RenderCommandFactory
** \brief A factory class that holds the actions that can be made


**/
	class RenderCommandFactory {
	public:
		template<typename ...Args> static RenderCommand* CreateCommand(RenderCommand::Commands command, Args&& ...args) { //!< Creates a command from the enum class Commands
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
		static std::function<void(void)> GetClearColourDepthBufferCommand(); //!< the GetClearColourDepthBufferCommand command
		static std::function<void(void)> GetSetClearColourCommand(float r, float g, float b, float a); //!< the GetSetClearColourCommand command
	};
}