#include "EdgeDetectFilter.h"

EdgeDetectFilter::EdgeDetectFilter() : Filter("Edge Detect")
{
	m_KernelXUniform = std::make_shared<lolibox::Mat3Uniform>("kernel_x", GetKernelX());
	m_KernelYUniform = std::make_shared<lolibox::Mat3Uniform>("kernel_y", GetKernelY());
	m_IntensityUniform = std::make_shared<lolibox::FloatUniform>("intensity", 1.0f);
	m_BlendSwitchUniform = std::make_shared<lolibox::Int1Uniform>("blending", 0);

	m_Shader = std::make_shared<lolibox::FramebufferShader>("shaders/passthrough.vert", "shaders/edgedetect.frag");

	m_Shader->AttachUniform(m_KernelXUniform);
	m_Shader->AttachUniform(m_KernelYUniform);
	m_Shader->AttachUniform(m_IntensityUniform);
	m_Shader->AttachUniform(m_BlendSwitchUniform);
}

void EdgeDetectFilter::Bind(const std::weak_ptr<lolibox::Texture>& in)
{
	if (auto t = in.lock())
		t->Bind();

	m_Shader->Use();
}

void EdgeDetectFilter::Unbind()
{
	m_Shader->Unuse();
}

void EdgeDetectFilter::DrawUI()
{
	ImGui::SetNextWindowSize(ImVec2(360, 80), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Edge Detect Filter Settings", &m_ShowUI))
	{
		bool upd = ImGui::RadioButton("Roberts Cross", (int*)&m_Alg, (int)EdgeDetectAlg::ROBERTS_CROSS);
		ImGui::SameLine();
		upd |= ImGui::RadioButton("Sobel", (int*)&m_Alg, (int)EdgeDetectAlg::SOBEL);

		if (upd)
		{
			m_KernelXUniform->m_Value = GetKernelX();
			m_KernelXUniform->SetNeedUpdate(true);
			m_KernelYUniform->m_Value = GetKernelY();
			m_KernelYUniform->SetNeedUpdate(true);
		}

		if (ImGui::SliderFloat("Intensity", &m_IntensityUniform->m_Value, 0.f, 1.f))
		{
			m_IntensityUniform->SetNeedUpdate(true);
		}

		if (ImGui::Checkbox("Blending", &m_Blend))
		{
			m_BlendSwitchUniform->m_Value = m_Blend;
			m_BlendSwitchUniform->SetNeedUpdate(true);
		}

		ImGui::End();
	}
}

const glm::mat3& EdgeDetectFilter::GetKernelX()
{
	switch (m_Alg)
	{
	case EdgeDetectAlg::SOBEL:
		return S_KERNEL_SOBEL_X;
	case EdgeDetectAlg::ROBERTS_CROSS:
		return S_KERNEL_ROBERTS_CROSS_X;
	}
}

const glm::mat3& EdgeDetectFilter::GetKernelY()
{
	switch (m_Alg)
	{
	case EdgeDetectAlg::SOBEL:
		return S_KERNEL_SOBEL_Y;
	case EdgeDetectAlg::ROBERTS_CROSS:
		return S_KERNEL_ROBERTS_CROSS_Y;
	}
}
