#pragma once

#include "Events/EventBus.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace lolibox
{
	class Window
	{
	public:
		Window(const std::string& title, const glm::u32vec2 size = { 1280, 720 });
		~Window();

		void BeginUpdate();
		void EndUpdate();

		auto GetSize() const -> auto { return m_Size; }
		auto GetNativeWindow() const -> auto { return m_Window; }
		auto GetOpenGLContext() const -> auto { return m_GLContext; }

		auto IsVSync() const -> bool { return m_VSync; }
		void SetVSync(bool enabled);

		auto SetCallbackFn(const std::function<EventBus::CallbackFn>& fn) -> void { m_CallbackFunction = fn; }

	private:
		std::string m_Title;
		glm::u32vec2 m_Size;

		bool m_VSync;

		SDL_GLContext m_GLContext;
		SDL_Window* m_Window;

		std::function<EventBus::CallbackFn> m_CallbackFunction;

		void Init();
		void Shutdown();

		void ProcessEvents(SDL_Event* even);
		void ProcessWindowEvents(SDL_Event* event);
	};
}
