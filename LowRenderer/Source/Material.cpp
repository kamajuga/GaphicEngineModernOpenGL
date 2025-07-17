#include "Material.h"

void Material::uploadMaterialToGPU(GLuint shaderProgram, const std::string& uniformName)
{
	GLint loc = glGetUniformLocation(shaderProgram, "material.ambient");
	if (loc != -1)
		glUniform4f(loc, m_ambient.m_x, m_ambient.m_y, m_ambient.m_z, m_ambient.m_k);

	loc = glGetUniformLocation(shaderProgram, "material.diffuse");
	if (loc != -1)
		glUniform4f(loc, m_diffuse.m_x, m_diffuse.m_y, m_diffuse.m_z, m_diffuse.m_k);

	loc = glGetUniformLocation(shaderProgram, "material.specular");
	if (loc != -1)
		glUniform4f(loc, m_specular.m_x, m_specular.m_y, m_specular.m_z, m_specular.m_k);

	loc = glGetUniformLocation(shaderProgram, "material.shininess");
	if (loc != -1)
		glUniform1f(loc, m_shininess);

}