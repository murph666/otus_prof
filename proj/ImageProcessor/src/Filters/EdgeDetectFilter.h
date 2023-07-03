#pragma once

#include "Filter.h"

enum class EdgeDetectAlg : int
{
	ROBERTS_CROSS,
	SOBEL
};

class EdgeDetectFilter : public Filter
{
public:
	EdgeDetectFilter();

	void Bind(const std::weak_ptr<lolibox::Texture>& in) override;
	void Unbind() override;

	void DrawUI() override;

	const glm::mat3& GetKernelX();
	const glm::mat3& GetKernelY();


private:
	static constexpr glm::mat3 S_KERNEL_ROBERTS_CROSS_X = { { 1.0f,  0.0f, 0.0f },
														    { 0.0f, -1.0f, 0.0f },
														    { 0.0f,  0.0f, 0.0f } };

	static constexpr glm::mat3 S_KERNEL_ROBERTS_CROSS_Y = { {  0.0f, 1.0f, 0.0f },
														    { -1.0f, 0.0f, 0.0f },
													        {  0.0f, 0.0f, 0.0f } };

	static constexpr glm::mat3 S_KERNEL_SOBEL_X = { { 1.0f,  0.0f, -1.0f },
												    { 2.0f,  0.0f, -2.0f },
											        { 1.0f,  0.0f, -1.0f } };

	static constexpr glm::mat3 S_KERNEL_SOBEL_Y = { { -1.0f, -2.0f, -1.0f },
									                {  0.0f,  0.0f,  0.0f },
												    {  1.0f,  2.0f,  1.0f } };

	std::shared_ptr<lolibox::FramebufferShader> m_Shader;
	std::shared_ptr<lolibox::Mat3Uniform> m_KernelXUniform;
	std::shared_ptr<lolibox::Mat3Uniform> m_KernelYUniform;
	std::shared_ptr<lolibox::FloatUniform> m_IntensityUniform;
	std::shared_ptr<lolibox::Int1Uniform> m_BlendSwitchUniform;

	EdgeDetectAlg m_Alg = EdgeDetectAlg::ROBERTS_CROSS;
	bool m_Blend = false;
};
