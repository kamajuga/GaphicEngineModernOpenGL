#include "LibMath/GeometricObject3.h"

#pragma region Point 3D

LibMath::Geometry3D::Point::Point(const float x, const float y, const float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

LibMath::Geometry3D::Point::Point(const Point& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	m_z = other.m_z;
}

LibMath::Geometry3D::Point& LibMath::Geometry3D::Point::operator=(const Point& other)
{
	m_x = other.m_x;
	m_y = other.m_y;

	return *this;
}

#pragma endregion All functions Point 3D 

#pragma region Line 3D
LibMath::Geometry3D::Line::Line(const Point& point, const Vector3& dir)
{
	m_origin = point;
	m_direction = dir;
	if (!m_direction.isUnitVector())
	{
		m_direction.normalize();
	}
	
}

LibMath::Geometry3D::Line::Line(const Line& other)
{
	m_origin = other.m_origin;
	m_direction = other.m_direction;
}

LibMath::Geometry3D::Line& LibMath::Geometry3D::Line::operator=(const Line& other)
{
	m_origin = other.m_origin;
	m_direction = other.m_direction;

	return *this;
}
#pragma endregion All functions Line 3D

#pragma region Plan 3D
LibMath::Geometry3D::Plan::Plan(const Vector3& normal, const float& distance)
{
	m_normal = normal;
	m_distance = distance;

	if (!m_normal.isUnitVector())
	{
		m_normal.normalize();
	}
	
}

LibMath::Geometry3D::Plan::Plan(const Plan& other)
{
	m_normal = other.m_normal;
	m_distance = other.m_distance;

}

LibMath::Geometry3D::Plan& LibMath::Geometry3D::Plan::operator=(const Plan& other)
{
	m_normal = other.m_normal;
	m_distance = other.m_distance;

	return *this;
}
#pragma endregion All functions Plan 3D

#pragma region AABB 3D

LibMath::Geometry3D::AABB::AABB(const Point& center, const float& width, const float& height, const float& depth)
{
	m_center = center;
	m_width = width;
	m_height = height;
	m_depth = depth;
}

LibMath::Geometry3D::AABB::AABB(const AABB& other)
{
	m_center = other.m_center;
	m_width = other.m_width;
	m_height = other.m_height;
	m_depth = other.m_depth;
}

LibMath::Geometry3D::AABB& LibMath::Geometry3D::AABB::operator=(const AABB& other)
{
	m_center = other.m_center;
	m_width = other.m_width;
	m_height = other.m_height;
	m_depth = other.m_depth;

	return *this;
}

LibMath::Geometry3D::Point LibMath::Geometry3D::AABB::center(void)
{
	return m_center;
}

float LibMath::Geometry3D::AABB::extentX(void) const
{
	return m_width / 2.f;
}

float LibMath::Geometry3D::AABB::extentY(void) const
{
	return m_height / 2.f;
}

float LibMath::Geometry3D::AABB::extentZ(void) const
{
	return m_depth / 2.f;
}

#pragma endregion All functions AABB

#pragma region OBB 3D

LibMath::Geometry3D::OBB::OBB(const Point& center, const float& width, const float& height, const float& depth, const Radian& rotation)
{
	m_center = center;
	m_width = width;
	m_height = height;
	m_depth = depth;
	m_rotation = rotation;

}

LibMath::Geometry3D::OBB::OBB(const OBB& other)
{
	m_center = other.m_center;
	m_width = other.m_width;
	m_height = other.m_height;
	m_depth = other.m_depth;
	m_rotation = other.m_rotation;
}

LibMath::Geometry3D::OBB& LibMath::Geometry3D::OBB::operator=(const OBB& other)
{
	m_center = other.m_center;
	m_width = other.m_width;
	m_height = other.m_height;
	m_depth = other.m_depth;
	m_rotation = other.m_rotation;

	return *this;
}

LibMath::Radian LibMath::Geometry3D::OBB::rotation(void)
{
	return m_rotation;
}

#pragma endregion All function OBB

#pragma region Sphere 3D

LibMath::Geometry3D::Sphere::Sphere(const Point& center, const float& radius)
{
	m_center = center;
	m_radius = radius;
}

LibMath::Geometry3D::Sphere::Sphere(const Sphere& other)
{
	m_center = other.m_center;
	m_radius = other.m_radius;
}

LibMath::Geometry3D::Sphere& LibMath::Geometry3D::Sphere::operator=(const Sphere& other)
{
	m_center = other.m_center;
	m_radius = other.m_radius;

	return *this;
}

#pragma endregion All function Sphere
