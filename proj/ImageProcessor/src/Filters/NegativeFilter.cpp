#include "NegativeFilter.h"

NegativeFilter::NegativeFilter() : Filter("Negative")
{
	m_ShowUI = false;
	m_Shader = std::make_shared<lolibox::FramebufferShader>("shaders/passthrough.vert", "shaders/negative.frag");
}

void NegativeFilter::Bind(const std::weak_ptr<lolibox::Texture>& in)
{
	if (auto t = in.lock())
		t->Bind();

	m_Shader->Use();
}

void NegativeFilter::Unbind()
{
	m_Shader->Unuse();
}
