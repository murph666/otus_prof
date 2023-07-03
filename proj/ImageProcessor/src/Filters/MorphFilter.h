#pragma once

#include "Filter.h"

class MorphFilter : public Filter
{
public:
	MorphFilter(const std::string& name = "Morph");

	void Bind(const std::weak_ptr<lolibox::Texture>& in) override;
	void Unbind() override;

	void DrawUI() override;

private:
	std::shared_ptr<lolibox::FramebufferShader> m_Shader;
	std::shared_ptr<lolibox::Int1Uniform> m_OperatorUniform;
	std::shared_ptr<lolibox::Int1Uniform> m_BrushUniform;
	std::shared_ptr<lolibox::FloatUniform> m_RadiusUniform;
};
