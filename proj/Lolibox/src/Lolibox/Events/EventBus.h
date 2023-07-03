#pragma once

#include "Event.h"

#include <eventpp/eventdispatcher.h>
#include <eventpp/utilities/orderedqueuelist.h>

namespace lolibox
{

	class EventBus
	{
	public:
		using EventPtr = std::shared_ptr<Event>;
		using CallbackFn = void(const EventPtr&);

		EventBus();

		struct PriorityCompare
		{
			template <typename T>
			bool operator() (const T& a, const T& b) const {
				return std::get<0>(a.arguments)->GetPriority() > std::get<0>(b.arguments)->GetPriority();
			}
		};

		struct EventPolicy
		{
			template <typename Item>
			using QueueList = eventpp::OrderedQueueList<Item, PriorityCompare>;

			static EventType getEvent(const EventPtr& e)
			{
				return e->GetType();
			}
		};

		// auto Enqueue(const EventPtr& event) -> void { m_EventBusImpl->enqueue(event); }
		// auto Enqueue(const EventType type, const EventPtr& event) -> void { m_EventBusImpl->enqueue(type, event); }

		auto Dispatch(const EventPtr& event) -> void { m_EventBusImpl->dispatch(event); }
		auto Dispatch(const EventType type, const EventPtr& event) -> void { m_EventBusImpl->dispatch(type, event); }

		// auto ProcessQueue() -> void { m_EventBusImpl->process(); }

		auto AppendListener(const EventType type, const std::function<CallbackFn> cb) -> void { m_EventBusImpl->appendListener(type, cb); }

	private:
		std::unique_ptr<eventpp::EventDispatcher<EventType, CallbackFn, EventPolicy>> m_EventBusImpl;
	};

}
