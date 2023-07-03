#include "MorphFilter.h"

#include <sstream>

MorphFilter::MorphFilter(const std::string& name) : Filter(name)
{
	m_OperatorUniform = std::make_shared<lolibox::Int1Uniform>("operator_u", 0);
	m_BrushUniform = std::make_shared<lolibox::Int1Uniform>("brush_u", 0);
	m_RadiusUniform = std::make_shared<lolibox::FloatUniform>("radius_u", 1.0f);
	m_Shader = std::make_shared<lolibox::FramebufferShader>("shaders/passthrough.vert", "shaders/morph.frag");
	m_Shader->AttachUniform(m_OperatorUniform);
	m_Shader->AttachUniform(m_BrushUniform);
	m_Shader->AttachUniform(m_RadiusUniform);
}

void MorphFilter::Bind(const std::weak_ptr<lolibox::Texture>& in)
{
	if (auto t = in.lock())
		t->Bind();

	m_Shader->Use();
}

void MorphFilter::Unbind()
{
	m_Shader->Unuse();
}

void MorphFilter::DrawUI()
{
	ImGui::SetNextWindowSize(ImVec2(480, 80), ImGuiCond_FirstUseEver);

	std::stringstream ss;
	ss << GetName() << " Filter Settings";

	static std::string op = "Neutral";
	static std::string br = "Disc";

	if (ImGui::Begin(ss.str().c_str(), &m_ShowUI))
	{
		ImGui::Columns(2);
		if (ImGui::SliderInt("Operator", &m_OperatorUniform->m_Value, 0, 2))
		{
			switch (m_OperatorUniform->m_Value)
			{
			case 0: op = "Neutral"; break;
			case 1: op = "Dilatation"; break;
			case 2: op = "Erosion"; break;
			default:
				break;
			}

			m_OperatorUniform->SetNeedUpdate(true);
		}

		ImGui::NextColumn();
		ImGui::Text(op.c_str());
		ImGui::NextColumn();

		if (ImGui::SliderInt("Brush", &m_BrushUniform->m_Value, 0, 3))
		{
			switch (m_BrushUniform->m_Value)
			{
			case 0: br = "Disc"; break;
			case 1: br = "Star"; break;
			case 2: br = "Diamond"; break;
			case 3: br = "Square"; break;
			default:
				break;
			}
			m_BrushUniform->SetNeedUpdate(true);
		}

		ImGui::NextColumn();
		ImGui::Text(br.c_str());
		ImGui::NextColumn();

		if (ImGui::SliderFloat("Radius", &m_RadiusUniform->m_Value, 1.0f, 10.0f))
		{
			m_RadiusUniform->SetNeedUpdate(true);
		}

		ImGui::End();
	}
}
