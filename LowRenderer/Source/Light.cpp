#define _USE_MATH_DEFINES
#include <cmath>
#include "Light.h"

void Light::uploadLightCountToGPU(GLuint shaderProgram, const std::string& uniformName, int count)
{
	GLint location = glGetUniformLocation(shaderProgram, uniformName.c_str());
	if (location == -1) {
		std::cerr << "Warning: uniform '" << uniformName << "' not found in shader program." << std::endl;
		//throw std::runtime_error("Model matrix uniform not found: " + uniformName);
		//return;
	}
	glUniform1i(location, count);
}

DirectionalLight::DirectionalLight(const LibMath::Vector3& position, const LibMath::Radian& rotation, const LibMath::Vector3& scale)
{
	m_transform = LibMath::Matrix4::createTransform(position, rotation, scale);
	m_direction = LibMath::Vector3(0.0f, 0.0f, -1.0f); // Default direction
	m_ambient = LibMath::Vector4(0.4f, 0.4f, 0.4f, 1.f);
	m_diffuse = LibMath::Vector4(0.6f, 0.6f, 0.6f, 1.f);
	m_specular = LibMath::Vector4(0.5f, 0.5f, 0.5f, 1.f);
}

void DirectionalLight::uploadLightToGPU(GLuint shaderProgram, const std::string& uniformName, int index)
{
	// world‐space direction = transform * (0,0,-1,0)
	/*LibMath::Vector4 direction = m_transform * LibMath::Vector4(0, 0, -1, 0);
	direction.normalize();*/

	LibMath::Vector3 direction (0.f, -10.f, 0.f);

	GLint dirLoc = glGetUniformLocation(shaderProgram, (uniformName + ".direction").c_str());
	if (dirLoc != -1)
		glUniform3f(dirLoc, direction.m_x, direction.m_y, direction.m_z);

	GLint ambLoc = glGetUniformLocation(shaderProgram, (uniformName + ".ambient").c_str());
	if (ambLoc != -1)
		glUniform4f(ambLoc, m_ambient.m_x, m_ambient.m_y, m_ambient.m_z, m_ambient.m_k);

	GLuint diffLoc = glGetUniformLocation(shaderProgram, (uniformName + ".diffuse").c_str());
	if (diffLoc != -1)
		glUniform4f(diffLoc, m_diffuse.m_x, m_diffuse.m_y, m_diffuse.m_z, m_diffuse.m_k);

	GLuint specLoc = glGetUniformLocation(shaderProgram, (uniformName + ".specular").c_str());
	if (specLoc != -1)
		glUniform4f(specLoc, m_specular.m_x, m_specular.m_y, m_specular.m_z, m_specular.m_k);
}

PointLight::PointLight(const LibMath::Vector3& position, const LibMath::Radian& rotation, const LibMath::Vector3& scale)
{
	m_transform = LibMath::Matrix4::createTransform(position, rotation, scale);
	m_ambient = LibMath::Vector4(20.f, 20.1f, 10.f, 1.0f);
	m_diffuse = LibMath::Vector4(1.0f, 0.8f, 0.6f, 1.f);
	m_specular = LibMath::Vector4(1.f, 0.f, 0.f, 1.f);
	m_constant = 1.0f;
	m_linear = 0.09f;;
	m_quadratic = 0.0032f;
}

void PointLight::uploadLightToGPU(GLuint shaderProgram, const std::string& uniformName, int index)
{
	std::string base = uniformName + "[" + std::to_string(index) + "]";
	LibMath::Vector4 position = m_transform * LibMath::Vector4(1, 1, 1, 1);

	GLint loc = glGetUniformLocation(shaderProgram, (base + ".position").c_str());
	if (loc != -1) 
		glUniform3f(loc, position.m_x, position.m_y, position.m_z);

	loc = glGetUniformLocation(shaderProgram, (base + ".ambient").c_str());
	if (loc != -1)
		glUniform4f(loc, m_ambient.m_x, m_ambient.m_y, m_ambient.m_z, m_ambient.m_k);

	loc = glGetUniformLocation(shaderProgram, (base + ".diffuse").c_str());
	if (loc != -1)
		glUniform4f(loc, m_diffuse.m_x, m_diffuse.m_y, m_diffuse.m_z, m_diffuse.m_k);

	loc = glGetUniformLocation(shaderProgram, (base + ".specular").c_str());
	if (loc != -1)
		glUniform4f(loc, m_specular.m_x, m_specular.m_y, m_specular.m_z, m_specular.m_k);

	loc = glGetUniformLocation(shaderProgram, (base + ".constant").c_str());
	if (loc != -1)
		glUniform1f(loc, m_constant);

	loc = glGetUniformLocation(shaderProgram, (base + ".linear").c_str());
	if (loc != -1)
		glUniform1f(loc, m_linear);

	loc = glGetUniformLocation(shaderProgram, (base + ".quadratic").c_str());
	if (loc != -1)
		glUniform1f(loc, m_quadratic);
}

SpotLight::SpotLight(const LibMath::Vector3& position, const LibMath::Radian& rotation, const LibMath::Vector3& scale)
{
	m_transform = LibMath::Matrix4::createTransform(position, rotation, scale);
	m_position = position;
	m_ambient = LibMath::Vector4(20.f, 20.1f, 10.f, 1.0f);
	m_diffuse = LibMath::Vector4(1.f, 1.f, 1.f, 1.f);
	m_specular = LibMath::Vector4(1.0f, 1.0f, 1.0f, 1.f);
	m_constant = 1.0f;
	m_linear = 0.09f;
	m_quadratic = 0.032f;
	m_cutOff = static_cast<float>(cos(M_PI / 4));
	m_outerCutOff = static_cast<float>(cos(M_PI / 3));
}

void SpotLight::uploadLightToGPU(GLuint shaderProgram, const std::string& uniformName, int index)
{
	std::string base = "sLight[" + std::to_string(index) + "]";

	// World-space position = transform * (0,0,0,1)
	LibMath::Vector4 position = m_transform * LibMath::Vector4(0, 0, 0, 1);
	GLint loc = glGetUniformLocation(shaderProgram, (base + ".position").c_str());
	if (loc != -1)
		glUniform3f(loc, position.m_x, position.m_y, position.m_z);

	// World-space direction = transform * (0,0,-1,0)
	LibMath::Vector4 direction = m_transform * LibMath::Vector4(0, 0, -1, 0);

	loc = glGetUniformLocation(shaderProgram, (base + ".direction").c_str());
	if (loc != -1)
		glUniform3f(loc, direction.m_x, direction.m_y, direction.m_z);

	// Ambient color
	loc = glGetUniformLocation(shaderProgram, (base + ".ambient").c_str());
	if (loc != -1)
		glUniform4f(loc, m_ambient.m_x, m_ambient.m_y, m_ambient.m_z, m_ambient.m_k);

	// Diffuse color
	loc = glGetUniformLocation(shaderProgram, (base + ".diffuse").c_str());
	if (loc != -1)
		glUniform4f(loc, m_diffuse.m_x, m_diffuse.m_y, m_diffuse.m_z, m_diffuse.m_k);

	// Specular color
	loc = glGetUniformLocation(shaderProgram, (base + ".specular").c_str());
	if (loc != -1)
		glUniform4f(loc, m_specular.m_x, m_specular.m_y, m_specular.m_z, m_specular.m_k);

	// Attenuation - Constant
	loc = glGetUniformLocation(shaderProgram, (base + ".constant").c_str());
	if (loc != -1)
		glUniform1f(loc, m_constant);

	// Attenuation - Linear
	loc = glGetUniformLocation(shaderProgram, (base + ".linear").c_str());
	if (loc != -1)
		glUniform1f(loc, m_linear);

	// Attenuation - Quadratic
	loc = glGetUniformLocation(shaderProgram, (base + ".quadratic").c_str());
	if (loc != -1)
		glUniform1f(loc, m_quadratic);

	// Inner cutoff angle
	loc = glGetUniformLocation(shaderProgram, (base + ".cutOff").c_str());
	if (loc != -1)
		glUniform1f(loc, m_cutOff);

	// Outer cutoff angle
	loc = glGetUniformLocation(shaderProgram, (base + ".outerCutOff").c_str());
	if (loc != -1)
		glUniform1f(loc, m_outerCutOff);
}

void SpotLight::update(float deltaTime)
{
	static float time = 0.0f;
	time += deltaTime;

	// Test de mouvement circulaire
	float radius = 10.0f;
	LibMath::Vector3 newPosition(
		cos(time) * radius,
		5.0f,
		5.f
	);
	

	// Recalculer la matrice de transformation
	m_transform = LibMath::Matrix4::createTransform(
		newPosition,
		LibMath::Radian(0), // Rotation qui suit le mouvement
		LibMath::Vector3(1.0f, 1.0f, 1.0f)
	);

}