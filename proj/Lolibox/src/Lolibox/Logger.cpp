#include "pch.h"
#include "Logger.h"

#include "Utility/Time.h"

namespace lolibox
{

	Logger& Logger::GetInstance()
	{
		if (!s_Instance)
		{
			s_Instance = new Logger();
		}

		return *s_Instance;
	}

	static void AddLogWithPrefix(std::string prefix, std::string fmt, va_list args)
	{
		va_list args_copy;
		va_copy(args_copy, args);

		std::stringstream ss;
		ss << util::CurrentTimeStr() << " " << prefix << " " << fmt << std::endl;
		Logger::GetInstance().AddLog(ss.str().c_str(), args_copy);
		va_end(args_copy);
	}

	Logger* Logger::s_Instance = nullptr;

	Logger::Logger()
	{
		m_AutoScroll = true;
		Clear();
	}

	void Logger::Clear()
	{
		m_Buf.clear();
		m_LineOffsets.clear();
		m_LineOffsets.push_back(0);
	}

	void Logger::AddLog(const char* fmt, va_list args)
	{
		int old_size = m_Buf.size();
		va_list args_copy;
		va_copy(args_copy, args);
		m_Buf.appendfv(fmt, args_copy);
		va_end(args_copy);
		for (int new_size = m_Buf.size(); old_size < new_size; old_size++)
			if (m_Buf[old_size] == '\n')
				m_LineOffsets.push_back(old_size + 1);
	}

	void Logger::Draw(bool* p_Open)
	{
		ImGui::SetNextWindowSize(ImVec2(640, 480), ImGuiCond_FirstUseEver);
		ImGui::Begin("Application Logger", p_Open);

		// Options menu
		if (ImGui::BeginPopup("Options"))
		{
			ImGui::Checkbox("Auto-scroll", &m_AutoScroll);
			ImGui::EndPopup();
		}

		// Main window
		if (ImGui::Button("Options"))
			ImGui::OpenPopup("Options");
		ImGui::SameLine();
		bool clear = ImGui::Button("Clear");
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
		ImGui::SameLine();
		m_Filter.Draw("Filter", -100.0f);

		ImGui::Separator();
		ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

		if (clear)
			Clear();
		if (copy)
			ImGui::LogToClipboard();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		const char* buf = m_Buf.begin();
		const char* buf_end = m_Buf.end();
		if (m_Filter.IsActive())
		{
			for (int line_no = 0; line_no < m_LineOffsets.Size; line_no++)
			{
				const char* line_start = buf + m_LineOffsets[line_no];
				const char* line_end = (line_no + 1 < m_LineOffsets.Size) ? (buf + m_LineOffsets[line_no + 1] - 1) : buf_end;
				if (m_Filter.PassFilter(line_start, line_end))
					ImGui::TextUnformatted(line_start, line_end);
			}
		}
		else
		{
			ImGuiListClipper clipper;
			clipper.Begin(m_LineOffsets.Size);
			while (clipper.Step())
			{
				for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
				{
					const char* line_start = buf + m_LineOffsets[line_no];
					const char* line_end = (line_no + 1 < m_LineOffsets.Size) ? (buf + m_LineOffsets[line_no + 1] - 1) : buf_end;
					ImGui::TextUnformatted(line_start, line_end);
				}
			}
			clipper.End();
		}
		ImGui::PopStyleVar();

		if (m_AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
		ImGui::End();
	}

	void Logger::Debug(std::string fmt, ...)
	{
		#ifdef _DEBUG
			va_list args;
			va_start(args, fmt);
			AddLogWithPrefix("DEBUG", fmt, args);
			va_end(args);
		#endif
	}

	void Logger::Info(std::string fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		AddLogWithPrefix(" INFO", fmt, args);
		va_end(args);
	}

	void Logger::Warn(std::string fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		AddLogWithPrefix(" WARN", fmt, args);
		va_end(args);
	}

	void Logger::Error(std::string fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		AddLogWithPrefix("ERROR", fmt, args);
		va_end(args);
	}

	void Logger::Fatal(std::string fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		AddLogWithPrefix("FATAL", fmt, args);
		va_end(args);
	}

}
