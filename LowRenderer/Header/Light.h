#pragma once
#include "LibMath/Vector.h"
#include "LibMath/Matrix/Matrix4.h"
#include "LibMath/Vector/Vector3.h"
#include "LibMath/Matrix4Vector4Operation.h"
#include "LibMath/Angle/Radian.h"

#ifndef __gl_h_
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#endif // __gl_h_

class Light
{
public:
	Light() = default;
	~Light() = default;

	LibMath::Vector4 m_ambient;
	LibMath::Vector4 m_diffuse;
	LibMath::Vector4 m_specular;

	LibMath::Matrix4 m_transform;

	void uploadLightCountToGPU(GLuint shaderProgram, const std::string& uniformName, int count);

	virtual void uploadLightToGPU(GLuint shaderProgram, const std::string& uniformName, int index) = 0;
private:

};

class DirectionalLight : public Light
{
public:
	DirectionalLight() = default;
	DirectionalLight(LibMath::Vector3& const position, LibMath::Radian& const rotation, LibMath::Vector3& const scale);
	~DirectionalLight() = default;

	LibMath::Vector3 m_direction;

	void uploadLightToGPU(GLuint shaderProgram, const std::string& uniformName, int index) override;
private:

};

class PointLight : public Light
{
public:
	PointLight() = default;
	PointLight(LibMath::Vector3& const position, LibMath::Radian& const rotation, LibMath::Vector3& const scale);
	~PointLight() = default;

	LibMath::Vector3 m_position;
	float m_constant;
	float m_linear;
	float m_quadratic;

	void uploadLightToGPU(GLuint shaderProgram, const std::string& uniformName, int index) override;
private:

};

class SpotLight : public Light
{
public:
	SpotLight() = default;
	SpotLight(LibMath::Vector3& const position, LibMath::Radian& const rotation, LibMath::Vector3& const scale);
	void update(float deltaTime);
	~SpotLight() = default;

	LibMath::Vector3 m_position;
	LibMath::Vector3 m_direction;
	float m_constant;
	float m_linear;
	float m_quadratic;
	float m_cutOff;
	float m_outerCutOff;


	void uploadLightToGPU(GLuint shaderProgram, const std::string& uniformName, int index) override;
private:
};