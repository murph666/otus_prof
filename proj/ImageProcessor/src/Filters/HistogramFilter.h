#pragma once

#include "Filter.h"

class HistogramFilter : public Filter
{
public:
	HistogramFilter(size_t binCount = 256);
	~HistogramFilter();

	void Bind(const std::weak_ptr<lolibox::Texture>& in) override;
	void Unbind() override;

	void DrawUI() override;

private:
	GLuint m_HistTex = 0;
	GLuint m_CdfTex = 0;
	size_t m_BinCount;
	GLuint* m_Values;
	std::shared_ptr<lolibox::ComputeShader> m_HistShader;
	std::shared_ptr<lolibox::ComputeShader> m_CdfShader;
	std::shared_ptr<lolibox::ComputeShader> m_EquShader;
	std::shared_ptr<lolibox::FramebufferShader> m_RenderShader;

	std::weak_ptr<lolibox::Texture> m_InputTexture;

	static GLuint GenOutputTexture(const glm::i32vec2& size);
};
