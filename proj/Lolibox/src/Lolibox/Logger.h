#pragma once

#include <imgui.h>

namespace lolibox
{

	class Logger
	{
	public:
		Logger();

		void Clear();
		void AddLog(const char* fmt, va_list args);
		void Draw(bool* p_Open);

		static Logger& GetInstance();

		static void Debug(std::string fmt, ...);
		static void Info(std::string fmt, ...);
		static void Warn(std::string fmt, ...);
		static void Error(std::string fmt, ...);
		static void Fatal(std::string fmt, ...);

	private:
		ImGuiTextBuffer m_Buf;
		ImGuiTextFilter m_Filter;
		ImVector<int> m_LineOffsets;
		bool m_AutoScroll;

		static Logger* s_Instance;
	};

}
