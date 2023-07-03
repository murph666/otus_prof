#pragma once

#include "Filter.h"

class GrayscaleFilter : public Filter
{
public:
	GrayscaleFilter();

	void Bind(const std::weak_ptr<lolibox::Texture>& in) override;
	void Unbind() override;

	void DrawUI() override;

private:
	std::shared_ptr<lolibox::FramebufferShader> m_Shader;
	std::shared_ptr<lolibox::Vec3fUniform> m_Vec3fUniform;

	const glm::vec3 DEFAULT_MULTITPLIER = { .2126f, .7152f, .0722f };
};
