#pragma once

namespace lolibox
{

	enum class EventType
	{
		BackendEvent, WindowClosed, WindowResized
		// TODO: Input Events
	};

	class Event
	{
	public:
		explicit Event(const EventType type, const int priority = 0) : m_Type(type), m_Priority(priority) {}
		virtual ~Event() = default;

		auto GetType() const -> EventType { return m_Type; };

		auto GetPriority() const -> int { return m_Priority; };

	private:
		EventType m_Type;
		int m_Priority;
	};

}
