#pragma once

#include "Lolibox/Events/EventBus.h"

namespace lolibox
{

	class RenderModule
	{
	public:
		explicit RenderModule() : m_EventBus(std::make_unique<EventBus>()) {};
		virtual ~RenderModule() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {};
		virtual void OnUiUpdate() {};

		virtual void HandleEventCallback(const EventBus::EventPtr& event) { DispatchEvent(event); };

	protected:
		auto DispatchEvent(const EventBus::EventPtr& event) -> void { m_EventBus->Dispatch(event); }
		auto AppendEventListener(const EventType type, const std::function<EventBus::CallbackFn> cb) -> void { m_EventBus->AppendListener(type, cb); }

	private:
		std::unique_ptr<EventBus> m_EventBus;
	};

}
