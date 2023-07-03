#pragma once

#include "Event.h"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace lolibox
{

	class BackendEvent : public Event
	{
	public:
		explicit BackendEvent(SDL_Event* event) : Event(EventType::BackendEvent, INT_MAX), m_BackendEvent(event) {}

		auto GetBackendEvent() -> SDL_Event* { return m_BackendEvent; }

	private:
		SDL_Event* m_BackendEvent;
	};


	class WindowCloseEvent : public Event
	{
	public:
		explicit WindowCloseEvent() : Event(EventType::WindowClosed) {}
	};


	class WindowResizeEvent : public Event
	{
	public:
		explicit WindowResizeEvent(const glm::u32vec2 newSize) : Event(EventType::WindowResized), m_Size(newSize) {}

		auto GetSize() const -> glm::u32vec2 { return m_Size; }

	private:
		glm::u32vec2 m_Size;
	};

}
