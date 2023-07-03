#pragma once

#include "Lolibox/Graphics/RenderModule.h"
#include "Lolibox/Events/WindowEvents.h"

namespace lolibox
{
	class UIBase : public RenderModule
	{
	public:
		UIBase() {};

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void BeginUpdate();
		void EndUpdate();
		void OnBackendEvent(const std::shared_ptr<BackendEvent>& event);

		virtual void HandleEventCallback(const EventBus::EventPtr& event) override {};
	};

}