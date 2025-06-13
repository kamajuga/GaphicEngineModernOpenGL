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

DirectionalLight::DirectionalLight(LibMath::Vector3& const position, LibMath::Radian& const rotation, LibMath::Vector3& const scale)
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
		glUniform3f(dirLoc, direction.getX(), direction.getY(), direction.getZ());

	GLint ambLoc = glGetUniformLocation(shaderProgram, (uniformName + ".ambient").c_str());
	if (ambLoc != -1)
		glUniform4f(ambLoc, m_ambient.getX(), m_ambient.getY(), m_ambient.getZ(), m_ambient.getK());

	GLuint diffLoc = glGetUniformLocation(shaderProgram, (uniformName + ".diffuse").c_str());
	if (diffLoc != -1)
		glUniform4f(diffLoc, m_diffuse.getX(), m_diffuse.getY(), m_diffuse.getZ(), m_diffuse.getK());

	GLuint specLoc = glGetUniformLocation(shaderProgram, (uniformName + ".specular").c_str());
	if (specLoc != -1)
		glUniform4f(specLoc, m_specular.getX(), m_specular.getY(), m_specular.getZ(), m_specular.getK());
}

PointLight::PointLight(LibMath::Vector3& const position, LibMath::Radian& const rotation, LibMath::Vector3& const scale)
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
		glUniform3f(loc, position.getX(), position.getY(), position.getZ());

	loc = glGetUniformLocation(shaderProgram, (base + ".ambient").c_str());
	if (loc != -1)
		glUniform4f(loc, m_ambient.getX(), m_ambient.getY(), m_ambient.getZ(), m_ambient.getK());

	loc = glGetUniformLocation(shaderProgram, (base + ".diffuse").c_str());
	if (loc != -1)
		glUniform4f(loc, m_diffuse.getX(), m_diffuse.getY(), m_diffuse.getZ(), m_diffuse.getK());

	loc = glGetUniformLocation(shaderProgram, (base + ".specular").c_str());
	if (loc != -1)
		glUniform4f(loc, m_specular.getX(), m_specular.getY(), m_specular.getZ(), m_specular.getK());

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

SpotLight::SpotLight(LibMath::Vector3& const position, LibMath::Radian& const rotation, LibMath::Vector3& const scale)
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
		glUniform3f(loc, position.getX(), position.getY(), position.getZ());

	// World-space direction = transform * (0,0,-1,0)
	LibMath::Vector4 direction = m_transform * LibMath::Vector4(0, 0, -1, 0);

	loc = glGetUniformLocation(shaderProgram, (base + ".direction").c_str());
	if (loc != -1)
		glUniform3f(loc, direction.getX(), direction.getY(), direction.getZ());

	// Ambient color
	loc = glGetUniformLocation(shaderProgram, (base + ".ambient").c_str());
	if (loc != -1)
		glUniform4f(loc, m_ambient.getX(), m_ambient.getY(), m_ambient.getZ(), m_ambient.getK());

	// Diffuse color
	loc = glGetUniformLocation(shaderProgram, (base + ".diffuse").c_str());
	if (loc != -1)
		glUniform4f(loc, m_diffuse.getX(), m_diffuse.getY(), m_diffuse.getZ(), m_diffuse.getK());

	// Specular color
	loc = glGetUniformLocation(shaderProgram, (base + ".specular").c_str());
	if (loc != -1)
		glUniform4f(loc, m_specular.getX(), m_specular.getY(), m_specular.getZ(), m_specular.getK());

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