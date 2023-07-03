#pragma once

#include "Shader.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace lolibox
{
	struct Element
	{
		glm::vec3 m_Vertex;
		glm::vec2 m_TexCoord;

        Element(glm::vec3 vertex, glm::vec2 uv) : m_Vertex(vertex), m_TexCoord(uv) {}
	};

	class Mesh
	{
	public:
		Mesh(const std::vector<Element>& elements, const std::vector<GLuint>& indices);
		~Mesh();

		void Draw();

		static std::shared_ptr<Mesh> Quad();

	private:
		void Free();

		GLuint m_VAO = 0, m_VBO = 0, m_EBO = 0;
		int m_ElementCount = 0;
	};
}
