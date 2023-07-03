#pragma once

#include "Filter.h"

class NegativeFilter : public Filter
{
public:
	NegativeFilter();

	void Bind(const std::weak_ptr<lolibox::Texture>& in) override;
	void Unbind() override;

	void DrawUI() override {};
	auto SetShowUI(bool show) -> void override {}

private:
	std::shared_ptr<lolibox::FramebufferShader> m_Shader;
};

