#pragma once

#include <Lolibox.h>

class Filter
{
public:
	explicit Filter(const std::string& name) : m_Name(name) {}
	virtual ~Filter() = default;

	virtual void Bind(const std::weak_ptr<lolibox::Texture>& in) = 0;
	virtual void Unbind() = 0;

	virtual void DrawUI() = 0;

	virtual auto SetShowUI(bool show) -> void { m_ShowUI = show; }
	auto GetShowUI() const -> bool { return m_ShowUI; }
	auto GetName() const -> auto { return m_Name.c_str(); }

protected:
	std::string m_Name;
	bool m_ShowUI = false;
};
