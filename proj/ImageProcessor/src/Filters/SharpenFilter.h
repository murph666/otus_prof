#pragma once

#include "Filter.h"

class SharpenFilter : public Filter
{
public:
	SharpenFilter();

	void Bind(const std::weak_ptr<lolibox::Texture>& in) override;
	void Unbind() override;

	void DrawUI() override;

private:
	static constexpr glm::mat3 S_KERNEL_BASIC = { 0, -1, 0, -1, 4, -1, 0, -1, 0 };
	static constexpr glm::mat3 S_KERNEL_DIAGONALS = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };

	std::shared_ptr<lolibox::FramebufferShader> m_Shader;
	std::shared_ptr<lolibox::Mat3Uniform> m_KernelUniform;
	std::shared_ptr<lolibox::FloatUniform> m_IntensityUniform;

	bool m_IsAdvanced = false;
};
