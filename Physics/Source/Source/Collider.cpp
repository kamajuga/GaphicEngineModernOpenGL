#include "Collider.h"
#include "LibMath/Matrix4Vector4Operation.h"
#include <LibMath/Collisions.h>

Collider::Collider(const Collider& other)
{
	if (other.m_ColliderShape) 
	{
        if (auto* aabb = dynamic_cast<Geometry3D::AABB*>(other.m_ColliderShape)) {
            m_ColliderShape = new Geometry3D::AABB(*aabb);
        }
        else if (auto* capsule = dynamic_cast<Geometry3D::Capsule*>(other.m_ColliderShape)) {
            m_ColliderShape = new Geometry3D::Capsule(*capsule);
        }
        else if (auto* sphere = dynamic_cast<Geometry3D::Sphere*>(other.m_ColliderShape)) {
            m_ColliderShape = new Geometry3D::Sphere(*sphere);
        }
		else
		{
			m_ColliderShape = nullptr;
		}
    }
	else
	{
		m_ColliderShape = nullptr;
	}
}

Collider&		Collider::operator=(const Collider& other)
{
	if (this != &other) 
	{
		//delete m_ColliderShape;
		m_ColliderShape = nullptr;

		if (other.m_ColliderShape)
		{
			if (auto* aabb = dynamic_cast<Geometry3D::AABB*>(other.m_ColliderShape)) 
			{
				m_ColliderShape = new Geometry3D::AABB(*aabb);
			}
			else if (auto* capsule = dynamic_cast<Geometry3D::Capsule*>(other.m_ColliderShape)) 
			{
				m_ColliderShape = new Geometry3D::Capsule(*capsule);
			}
			else if (auto* sphere = dynamic_cast<Geometry3D::Sphere*>(other.m_ColliderShape)) 
			{
				m_ColliderShape = new Geometry3D::Sphere(*sphere);
			}
		}
	}
	return *this;
}

Collider::Collider(const ColliderType& Type, Mesh& mesh, const LibMath::Vector3& playerCenter)
{
	switch (Type)
	{
	case ColliderType::BOX:
		boxCollider(mesh);
		break;

	case ColliderType::CAPSULE:
		capsuleCollider(mesh);
		break;

	case ColliderType::SPHERE:
		sphereCollider(mesh);
		break;
	case ColliderType::PLAYER:
		playerCollider(playerCenter, 4, 2);
		break;

	default:
		m_ColliderShape = nullptr;
		break;
	}
}

Collider::~Collider()
{
	if (m_ColliderShape)
	{
		delete m_ColliderShape;
	}
}

MeshDimensions	Collider::getboxCollider(Model& model)
{
	std::vector<Vertex> vertices = model.getVertices();
	MeshDimensions dims = { 0.0f, 0.0f, 0.0f };

	if (vertices.empty()) return MeshDimensions();

	if (!vertices.empty()) 
	{
		float minX = vertices[0].m_position.m_x, maxX = vertices[0].m_position.m_x;
		float minY = vertices[0].m_position.m_y, maxY = vertices[0].m_position.m_y;
		float minZ = vertices[0].m_position.m_z, maxZ = vertices[0].m_position.m_z;

		for (const auto& vertex : vertices) 
		{
			minX = std::min(minX, vertex.m_position.m_x);
			maxX = std::max(maxX, vertex.m_position.m_x);
			minY = std::min(minY, vertex.m_position.m_y);
			maxY = std::max(maxY, vertex.m_position.m_y);
			minZ = std::min(minZ, vertex.m_position.m_z);
			maxZ = std::max(maxZ, vertex.m_position.m_z);
		}

		dims.width = maxX - minX;
		dims.height = maxY - minY;
		dims.depth = maxZ - minZ;
	}

	return dims;
}

void			Collider::updateCollider(LibMath::Matrix4& transMat)
{
	m_ColliderShape->update(transMat);
}

void			Collider::playerCollider(const LibMath::Vector3& center, float height, float radius)
{
	// Point du bas de la capsule (pied du joueur)
	LibMath::Vector3 bottomPoint = center;
	bottomPoint.m_y -= (height / 2.0f - radius); // Soustraire la demi-hauteur moins le rayon

	// Point du haut de la capsule (tête du joueur)  
	LibMath::Vector3 topPoint = center;
	topPoint.m_y += (height / 2.0f - radius); // Ajouter la demi-hauteur moins le rayon

	// Créer les objets Point à partir des Vector3
	Geometry3D::Point pointA(bottomPoint.m_x, bottomPoint.m_y, bottomPoint.m_z);
	Geometry3D::Point pointB(topPoint.m_x, topPoint.m_y, topPoint.m_z);

	m_ColliderShape = new Geometry3D::Capsule(pointA, pointB, radius);
}

void			Collider::boxCollider(Mesh& mesh)
{
	std::vector<Vertex> vertices = mesh.getModelVertices();
	if (vertices.empty()) return;

	LibMath::Matrix4 modelMatrix = mesh.getModelMatrix();

	// Reste de votre code...
	LibMath::Vector3 min = { std::numeric_limits<float>::max(),
							std::numeric_limits<float>::max(),
							std::numeric_limits<float>::max() };
	LibMath::Vector3 max = { std::numeric_limits<float>::lowest(),
							std::numeric_limits<float>::lowest(),
							std::numeric_limits<float>::lowest() };

	for (const auto& vertex : vertices) 
	{
		LibMath::Vector4 worldPos = modelMatrix * LibMath::Vector4(
			vertex.m_position.m_x,
			vertex.m_position.m_y,
			vertex.m_position.m_z,
			1.0f);

		min.m_x = std::min(min.m_x, worldPos.m_x);
		min.m_y = std::min(min.m_y, worldPos.m_y);
		min.m_z = std::min(min.m_z, worldPos.m_z);
		max.m_x = std::max(max.m_x, worldPos.m_x);
		max.m_y = std::max(max.m_y, worldPos.m_y);
		max.m_z = std::max(max.m_z, worldPos.m_z);
	}

	// DEBUG: Afficher les dimensions calculées
	float width = max.m_x - min.m_x;
	float height = max.m_y - min.m_y;
	float depth = max.m_z - min.m_z;


	Geometry3D::Point center = 
	{
		(min.m_x + max.m_x) / 2.0f,
		(min.m_y + max.m_y) / 2.0f,
		(min.m_z + max.m_z) / 2.0f
	};

	m_ColliderShape = new Geometry3D::AABB(center, width, height, depth);
}

void			Collider::capsuleCollider(Mesh& mesh)
{
	std::vector<Vertex> vertices = mesh.getModelVertices();
	if (vertices.size() < 2) return;

	// Get the mesh's model matrix
	LibMath::Matrix4 modelMatrix = mesh.getModelMatrix(); // or mesh.getTransform().getMatrix()

	// Transform all vertices and store them
	std::vector<LibMath::Vector3> transformedVertices;
	transformedVertices.reserve(vertices.size());

	for (const auto& vertex : vertices)
	{
		// Transform vertex by model matrix
		LibMath::Vector4 worldPos = /*modelMatrix **/ LibMath::Vector4(vertex.m_position.m_x,
			vertex.m_position.m_y,
			vertex.m_position.m_z,
			1.0f);

		// Store transformed position
		transformedVertices.push_back({ worldPos.m_x, worldPos.m_y, worldPos.m_z });
	}

	// Find the two farthest points using transformed vertices
	LibMath::Vector3 farthest_p1 = transformedVertices[0];
	LibMath::Vector3 farthest_p2 = transformedVertices[1];
	float max_dist_sq = 0.0f;

	for (size_t i = 0; i < transformedVertices.size(); ++i)
	{
		for (size_t j = i + 1; j < transformedVertices.size(); ++j)
		{
			float dist_sq = (transformedVertices[i].m_x - transformedVertices[j].m_x) * (transformedVertices[i].m_x - transformedVertices[j].m_x) +
				(transformedVertices[i].m_y - transformedVertices[j].m_y) * (transformedVertices[i].m_y - transformedVertices[j].m_y) +
				(transformedVertices[i].m_z - transformedVertices[j].m_z) * (transformedVertices[i].m_z - transformedVertices[j].m_z);
			if (dist_sq > max_dist_sq) {
				max_dist_sq = dist_sq;
				farthest_p1 = transformedVertices[i];
				farthest_p2 = transformedVertices[j];
			}
		}
	}

	// Calculate approximate radius based on transformed distance
	float approximate_radius = std::sqrt(max_dist_sq) / 2.0f;

	m_ColliderShape = new Geometry3D::Capsule(Geometry3D::Point{ farthest_p1.m_x, farthest_p1.m_y, farthest_p1.m_z },
		Geometry3D::Point{ farthest_p2.m_x, farthest_p2.m_y, farthest_p2.m_z },
		approximate_radius);
}

void			Collider::sphereCollider(Mesh& mesh)
{
	std::vector<Vertex> vertices = mesh.getModelVertices();
	if (vertices.empty()) return;

	// Get the mesh's model matrix
	LibMath::Matrix4 modelMatrix = mesh.getModelMatrix(); // or mesh.getTransform().getMatrix()

	LibMath::Vector3 min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
	LibMath::Vector3 max = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };
	LibMath::Vector3 sum = { 0.0f, 0.0f, 0.0f };

	// First pass: transform vertices and calculate bounds + sum
	std::vector<LibMath::Vector3> transformedVertices;
	transformedVertices.reserve(vertices.size());

	for (const auto& vertex : vertices)
	{
		// Transform vertex by model matrix
		LibMath::Vector4 worldPos = /*modelMatrix **/ LibMath::Vector4(vertex.m_position.m_x,
			vertex.m_position.m_y,
			vertex.m_position.m_z,
			1.0f);

		// Store transformed position
		LibMath::Vector3 transformedPos = { worldPos.m_x, worldPos.m_y, worldPos.m_z };
		transformedVertices.push_back(transformedPos);

		// Calculate bounds with transformed positions
		min.m_x = std::min(min.m_x, transformedPos.m_x);
		min.m_y = std::min(min.m_y, transformedPos.m_y);
		min.m_z = std::min(min.m_z, transformedPos.m_z);
		max.m_x = std::max(max.m_x, transformedPos.m_x);
		max.m_y = std::max(max.m_y, transformedPos.m_y);
		max.m_z = std::max(max.m_z, transformedPos.m_z);

		// Calculate sum for center computation
		sum.m_x += transformedPos.m_x;
		sum.m_y += transformedPos.m_y;
		sum.m_z += transformedPos.m_z;
	}

	// Calculate center with transformed positions
	LibMath::Vector3 center_vec = { sum.m_x / vertices.size(), sum.m_y / vertices.size(), sum.m_z / vertices.size() };

	// Calculate maximum radius with transformed positions
	float max_radius_sq = 0.0f;
	for (const auto& transformedPos : transformedVertices)
	{
		float dist_sq = (transformedPos.m_x - center_vec.m_x) * (transformedPos.m_x - center_vec.m_x) +
			(transformedPos.m_y - center_vec.m_y) * (transformedPos.m_y - center_vec.m_y) +
			(transformedPos.m_z - center_vec.m_z) * (transformedPos.m_z - center_vec.m_z);
		max_radius_sq = std::max(max_radius_sq, dist_sq);
	}

	float radius = std::sqrt(max_radius_sq);
	m_ColliderShape = new Geometry3D::Sphere(Geometry3D::Point{ center_vec.m_x, center_vec.m_y, center_vec.m_z }, radius);
}
