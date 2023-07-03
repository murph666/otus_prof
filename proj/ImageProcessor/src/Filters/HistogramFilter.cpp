#include "HistogramFilter.h"

float getFloat_(void* data, int idx)
{
	return ((GLuint*)data)[idx];
}

HistogramFilter::HistogramFilter(size_t binCount) : Filter("Histogram"), m_BinCount(binCount)
{
	m_HistTex = GenOutputTexture({ m_BinCount, 3 });
	m_CdfTex = GenOutputTexture({ m_BinCount, 3 });

	m_HistShader = std::make_shared<lolibox::ComputeShader>("shaders/histogram.comp");
	m_HistShader->AttachUniform(std::make_shared<lolibox::TextureUniform>("i_in", 0));
	m_HistShader->AttachUniform(std::make_shared<lolibox::TextureUniform>("i_out", 1));

	m_CdfShader = std::make_shared<lolibox::ComputeShader>("shaders/cdf.comp");
	m_CdfShader->AttachUniform(std::make_shared<lolibox::TextureUniform>("i_hist", 0));
	m_CdfShader->AttachUniform(std::make_shared<lolibox::TextureUniform>("i_cdf", 1));

	m_EquShader = std::make_shared<lolibox::ComputeShader>("shaders/equalization.comp");
	m_EquShader->AttachUniform(std::make_shared<lolibox::TextureUniform>("i_target", 0));
	m_EquShader->AttachUniform(std::make_shared<lolibox::TextureUniform>("i_cdf", 1));

	m_RenderShader = std::make_shared<lolibox::FramebufferShader>("shaders/passthrough.vert", "shaders/texture.frag");

	m_Values = new GLuint[m_BinCount * 3];
}

void HistogramFilter::Bind(const std::weak_ptr<lolibox::Texture>& in)
{
	if (auto t = in.lock())
	{
		t->Bind(0);
		m_RenderShader->Use();
	}

	m_InputTexture = in;
}

void HistogramFilter::Unbind()
{
	m_RenderShader->Unuse();

	if (auto t = m_InputTexture.lock())
	{
		auto size = t->GetSize();

		m_HistShader->Use();
		glBindImageTexture(0, t->GetID(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(1, m_HistTex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI);

		glDispatchCompute(size.x / 8, size.y / 4, 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		m_HistShader->Unuse();

		m_CdfShader->Use();
		glBindImageTexture(0, m_HistTex, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32UI);
		glBindImageTexture(1, m_CdfTex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI);

		glDispatchCompute(m_BinCount / 32, 3, 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		m_CdfShader->Unuse();

		m_EquShader->Use();
		glBindImageTexture(0, t->GetID(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(1, m_CdfTex, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32UI);

		glDispatchCompute(size.x / 8, size.y / 4, 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		m_EquShader->Unuse();
	}

	glBindTexture(GL_TEXTURE_2D, m_HistTex);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, m_Values);

	GLuint c = 0;
	glClearTexImage(m_HistTex, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, &c);
}

void HistogramFilter::DrawUI()
{
	static float scaley = 10000;

	ImGui::SetNextWindowSize(ImVec2(512, 640), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Histogram Viewer Settings", &m_ShowUI))
	{

		ImVec2 hsize = { (ImGui::GetContentRegionAvail().x / 3) - 4, ImGui::GetContentRegionAvail().y - 54 };

		ImGui::Columns(3, nullptr, false);
		ImGui::Text("Red");
		ImGui::PlotHistogram("##Red1", getFloat_, m_Values, m_BinCount, 0, NULL, 0.0f, scaley, hsize);
		ImGui::NextColumn();
		ImGui::Text("Green");
		ImGui::PlotHistogram("##Green1", getFloat_, m_Values + m_BinCount, m_BinCount, 0, NULL, 0.0f, scaley, hsize);
		ImGui::NextColumn();
		ImGui::Text("Blue");
		ImGui::PlotHistogram("##Blue1", getFloat_, m_Values + m_BinCount * 2, m_BinCount, 0, NULL, 0.0f, scaley, hsize);
		ImGui::Columns(1);
		ImGui::SliderFloat("Scale", &scaley, 1000.0f, 50000.0f);

		ImGui::End();
	}
}

GLuint HistogramFilter::GenOutputTexture(const glm::i32vec2& size)
{
	GLuint tex = 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, size.x, size.y, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, nullptr);

	return tex;
}

HistogramFilter::~HistogramFilter()
{
	glDeleteTextures(1, &m_HistTex);
	delete[] m_Values;
}
