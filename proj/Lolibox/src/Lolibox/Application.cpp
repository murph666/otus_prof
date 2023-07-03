#include "pch.h"
#include "Application.h"

#include "Logger.h"
#include "UI/NativeMessages.h"

#include <glad/glad.h>
#include <imgui.h>

namespace lolibox
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& title, const glm::u32vec2 windowSize) : m_Title(title)
	{
		if (s_Instance)
		{
			native::showErrorMessageBox("Fatal error", "Application instance already exists");
			std::abort();
		}

		s_Instance = this;

		m_Window = std::make_unique<Window>(title, windowSize);
		//m_Window->SetCallbackFn(std::bind(&Application::HandleEventCallback, this, std::placeholders::_1));
		m_Window->SetCallbackFn([this](const EventBus::EventPtr& event) { HandleEventCallback(event); });

		m_EventBus = std::make_unique<EventBus>();
		m_EventBus->AppendListener(EventType::BackendEvent, [&](const EventBus::EventPtr& event) { OnBackendEvent(std::dynamic_pointer_cast<BackendEvent>(event)); });
		m_EventBus->AppendListener(EventType::WindowClosed, [&](const EventBus::EventPtr& event) { OnWindowClose(std::dynamic_pointer_cast<WindowCloseEvent>(event)); });
		m_EventBus->AppendListener(EventType::WindowResized, [&](const EventBus::EventPtr& event) { OnWindowResize(std::dynamic_pointer_cast<WindowResizeEvent>(event)); });

		m_Running = true;

		m_UIBase = std::make_unique<UIBase>();
		m_UIBase->OnAttach();
	}

	Application::~Application()
	{
		for (auto& m : m_RenderModules)
			DetachRenderModule(m);

		m_UIBase->OnDetach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->BeginUpdate();
			// m_EventBus->ProcessQueue();

			for (auto& m : m_RenderModules)
				m->OnUpdate();

			m_UIBase->BeginUpdate();

			for (auto& m : m_RenderModules)
				m->OnUiUpdate();

			if (m_ShowLogs)
				Logger::GetInstance().Draw(&m_ShowLogs);
			
			m_UIBase->EndUpdate();
			m_Window->EndUpdate();
		}
	}

	void Application::AttachRenderModule(const std::shared_ptr<RenderModule>& m)
	{
		m_RenderModules.push_back(m);
		m->OnAttach();
	}

	void Application::DetachRenderModule(const std::shared_ptr<RenderModule>& m)
	{
		m->OnDetach();

		auto t = std::find_if(m_RenderModules.begin(), m_RenderModules.end(),
			[&m](const std::shared_ptr<RenderModule>& p)
			{
				return p == m;
			});

		if (t != m_RenderModules.end())
		{
			m_RenderModules.erase(t);
		}

	}

	void Application::HandleEventCallback(const EventBus::EventPtr& event)
	{
		m_EventBus->Dispatch(event);

		for (auto& m : m_RenderModules)
			m->HandleEventCallback(event);
	}

	void Application::OnBackendEvent(const std::shared_ptr<BackendEvent>& event)
	{
		m_UIBase->OnBackendEvent(event);
	}

	void Application::OnWindowClose(const std::shared_ptr<WindowCloseEvent>& event)
	{
		m_Running = false;
	}

	void Application::OnWindowResize(const std::shared_ptr<WindowResizeEvent>& event)
	{
		glViewport(0, 0, event->GetSize().x, event->GetSize().y);
		Logger::Debug("New Window size is %dX%d", event->GetSize().x, event->GetSize().y);
	}

}
