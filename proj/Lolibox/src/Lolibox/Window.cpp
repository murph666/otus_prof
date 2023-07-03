#include "pch.h"
#include "Window.h"

#include "Logger.h"

#include "Events/EventBus.h"
#include "Events/WindowEvents.h"

#include "UI/NativeMessages.h"

#include <glad/glad.h>
#include <SDL.h>
#include <SDL_syswm.h>

namespace lolibox
{

	void GLAPIENTRY
		MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		if (type == GL_DEBUG_TYPE_ERROR)
		{
			Logger::Error(message);
		}
	}

	Window::Window(const std::string& title, const glm::u32vec2 size) : m_Title(title), m_Size(size)
	{
		Init();
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
		{
			native::showErrorMessageBox("SDL Error", SDL_GetError());
			return;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Size.x, m_Size.y, window_flags);

		SDL_GLContext gl_context = SDL_GL_CreateContext(m_Window);
		SDL_GL_MakeCurrent(m_Window, gl_context);
		SDL_GL_SetSwapInterval(m_VSync = false);

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		{
			native::showErrorMessageBox("GLAD Error", "Failed to initialize OpenGL context");
			return;
		}

		// During init, enable debug output
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		Logger::Info("OpenGL context successfully loaded!");
		Logger::Info("- Renderer: %s", glGetString(GL_RENDERER));
		Logger::Info("- Vendor:   %s", glGetString(GL_VENDOR));
		Logger::Info("- Version:  %s", glGetString(GL_VERSION));
		Logger::Info("- GLSL:     %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
		Logger::Info("- Ext:      %s\n", glGetString(GL_EXTENSIONS));
	}

	void Window::BeginUpdate()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (m_CallbackFunction)
			{
				ProcessEvents(&event);
			}
		}
	}

	void Window::EndUpdate()
	{
		SDL_GL_SwapWindow(m_Window);
	}

	void Window::SetVSync(bool enabled)
	{
		SDL_GL_SetSwapInterval((int)(m_VSync = enabled));
	}

	void Window::Shutdown()
	{
		SDL_GL_DeleteContext(m_GLContext);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	void Window::ProcessEvents(SDL_Event* event)
	{
		m_CallbackFunction(std::make_shared<BackendEvent>(event));

		if (event->type == SDL_QUIT)
			m_CallbackFunction(std::make_shared<WindowCloseEvent>());

		// TODO: Support multiple windows
		if (event->window.windowID != SDL_GetWindowID(m_Window))
			return;

		switch (event->type)
		{
		case SDL_WINDOWEVENT:
			ProcessWindowEvents(event);
			break;
		}

	}

	void Window::ProcessWindowEvents(SDL_Event* event)
	{
		switch (event->window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			event->type = SDL_QUIT;
			SDL_PushEvent(event);
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			m_Size = { event->window.data1, event->window.data2 };
			m_CallbackFunction(std::make_shared<WindowResizeEvent>(m_Size));
			break;
		}
	}
}
