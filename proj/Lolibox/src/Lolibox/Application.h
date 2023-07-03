#pragma once

#include "Window.h"
#include "Events/EventBus.h"
#include "Events/WindowEvents.h"
#include "UI/UIBase.h"

#include <glm/glm.hpp>

namespace lolibox
{

	class Application
	{
	public:
		Application(const std::string& title, const glm::u32vec2 size = { 1280, 720 });
		~Application();

		void Run();

		auto GetWindow() -> std::shared_ptr<Window>& { return m_Window; }

		void AttachRenderModule(const std::shared_ptr<RenderModule>& m);
		void DetachRenderModule(const std::shared_ptr<RenderModule>& m);

		auto SetShowLogs(bool show) -> void { m_ShowLogs = show; }
		auto GetShowLogs() -> const bool { return m_ShowLogs; }

		static auto GetInstance() -> Application& { return *s_Instance; };

	private:
		bool m_Running;
		std::string m_Title;

		std::shared_ptr<Window> m_Window;
		std::unique_ptr<EventBus> m_EventBus;
		
		std::unique_ptr<UIBase> m_UIBase;

		static Application* s_Instance;

		std::vector<std::shared_ptr<RenderModule>> m_RenderModules;

		bool m_ShowLogs = false;

		void HandleEventCallback(const EventBus::EventPtr& event);

		void OnBackendEvent(const std::shared_ptr<BackendEvent>& event);
		void OnWindowClose(const std::shared_ptr<WindowCloseEvent>& event);
		void OnWindowResize(const std::shared_ptr<WindowResizeEvent>& event);
	};

	Application* CreateApp();

}
