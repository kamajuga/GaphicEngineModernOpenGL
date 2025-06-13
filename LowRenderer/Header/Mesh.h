#pragma once

#ifndef __glad_h_
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#endif // !__glad_h_


#include "LibMath/Matrix.h"
#include "Shader.h"
#include "Model.h"
#include "Material.h"

class Mesh
{
public:
	Mesh() = default;
	Mesh(Model* Model);

	void setModelMatrix(LibMath::Vector3 translate = LibMath::Vector3(0.0f, 0.0f, 0.0f), // returns T . R . S
						LibMath::Radian rotation = LibMath::Radian(0.0f),
						LibMath::Vector3 scale = LibMath::Vector3(1.0f, 1.0f, 1.0f),
						LibMath::Vector3 axis = LibMath::Vector3(0.0f, 1.0f, 0.0f));
	void setModelMatrix(LibMath::Matrix4 const& modelMatrix)
	{
		m_modelMatrix = modelMatrix;
	}

	void draw(Shader& shader, LibMath::Matrix4 VPMatrix);
	
	void uploadModelMatrixToGPU(GLuint shaderProgram, const std::string& uniformName);

	void uploadMaterialToGPU(GLuint shaderProgram, const std::string& uniformName)
	{
		m_material.uploadMaterialToGPU(shaderProgram, uniformName);
	}

	void SetMaterial(LibMath::Vector4 ambient, LibMath::Vector4 diffuse, LibMath::Vector4 specular, float shininess);

	void setMaterial(const Material& material)
	{
		m_material = material;
	}

	Model* getModel(void) const
	{
		return m_model;
	}


	~Mesh() = default;

private:
	Model* m_model;
	Material m_material;
	LibMath::Matrix4 m_modelMatrix;
	LibMath::Matrix4 m_MVPMatrix;

};
