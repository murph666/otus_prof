#pragma once

#include "Filter.h"

class SmoothingFilter : public Filter
{
public:
	SmoothingFilter();

	void Bind(const std::weak_ptr<lolibox::Texture>& in) override;
	void Unbind() override;

	void DrawUI() override;

private:
	std::shared_ptr<lolibox::FramebufferShader> m_Shader;
	std::shared_ptr<lolibox::Int1Uniform> m_AlgUniform;
};
