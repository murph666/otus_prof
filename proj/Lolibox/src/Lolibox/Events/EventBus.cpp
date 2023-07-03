#include "pch.h"
#include "EventBus.h"

namespace lolibox
{

	EventBus::EventBus()
	{
		m_EventBusImpl = std::make_unique<eventpp::EventDispatcher<EventType, CallbackFn, EventPolicy>>();
	}
}
