#pragma once

#include "Filter.h"

class ThresholdingFilter : public Filter
{
public:
	ThresholdingFilter();

	void Bind(const std::weak_ptr<lolibox::Texture>& in) override;
	void Unbind() override;

	void DrawUI() override;

private:
	std::shared_ptr<lolibox::FramebufferShader> m_Shader;
	std::shared_ptr<lolibox::FloatUniform> m_ThresholdUniform;
	std::shared_ptr<lolibox::FloatUniform> m_ThresholdSmoothUniform;

	int m_ThresholdValue = 128;
};
