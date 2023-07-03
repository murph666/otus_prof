#include "pch.h"
#include "Mesh.h"

namespace lolibox
{

	Mesh::Mesh(const std::vector<Element>& elements, const std::vector<GLuint>& indices)
	{
		m_ElementCount = indices.size();

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, elements.size() * sizeof(Element), &elements[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)offsetof(Element, m_TexCoord));

		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		Free();
	}

	void Mesh::Draw()
	{
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_ElementCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Mesh::Free()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}

	std::shared_ptr<Mesh> Mesh::Quad()
	{
		std::vector<Element> vertices =
		{
			Element({-1, -1, 0}, {0, 0}),
			Element({-1,  1, 0}, {0, 1}),
			Element({ 1,  1, 0}, {1, 1}),
			Element({ 1, -1, 0}, {1, 0})
		};

		std::vector<GLuint> indices =
		{
			0, 2, 1,
			0, 3, 2
		};

		return std::make_shared<Mesh>(vertices, indices);
	}

}