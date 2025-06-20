#pragma once

#include <vector>
#ifndef __gl_h_
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#endif // !__gl_h_


#include "LibMath/Matrix/Matrix4.h"
#include "Mesh.h"
#include "Shader.h"

class SceneNode
{
public:
	SceneNode() = default;

	void addChild(std::shared_ptr<SceneNode> child);

	void addChild(Mesh* mesh, Shader* shader, const LibMath::Matrix4& trasformMat);

	void initialize(Mesh* mesh, Shader* shader, const LibMath::Matrix4& transformMat);

	void update(LibMath::Matrix4 const& parentTransform = LibMath::Matrix4::identity());

	void draw(const LibMath::Matrix4& VPMatrix);
	void deleteRecursive(void);


	~SceneNode();

	LibMath::Matrix4 m_localTransform = LibMath::Matrix4::identity();
	LibMath::Matrix4 m_worldTransform = LibMath::Matrix4::identity();

	SceneNode* m_parent = nullptr;
	Mesh* m_mesh = nullptr;
	Shader* m_shader = nullptr;

private:
	std::vector<std::shared_ptr<SceneNode>> m_children;


private:

};

template<typename T>
class Graph
{
public:
	Graph() = default;
	
	void addNode(std::shared_ptr<T> node)
	{
		m_nodes.emplace_back(node);
	}

	void updateAll(LibMath::Matrix4 const& parentTransform = LibMath::Matrix4::identity())
	{
		for (std::shared_ptr<T>& node : m_nodes)
		{
			node->Update(parentTransform);
		}
	}

	void drawAll(const LibMath::Matrix4& VPMatrix)
	{
		for (std::shared_ptr<T>& node : m_nodes)
		{
			node->draw(VPMatrix);
		}
	}

	void clearNodes(void)
	{
		m_nodes.clear();
	}

	~Graph();



	std::vector<std::shared_ptr<T>> m_nodes;

private:

};

template<typename T>
inline Graph<T>::~Graph()
{
	if (!m_nodes.empty())
	{
		for (auto& node : m_nodes)
			node->deleteRecursive(); 
	}
}
