#include "LibMath/Collisions.h"

#pragma region Sphere Collision 3D
bool LibMath::Collisions3D::checkCollision(const Geometry3D::Sphere& sphere1, const Geometry3D::Sphere& sphere2)
{
	// Distance between the center of the two sphere
	float distance = sqrtf(powf(sphere1.center().getX() - sphere2.center().getX(), 2) +
		powf(sphere1.center().getY() - sphere2.center().getY(), 2) +
		powf(sphere1.center().getZ() - sphere2.center().getZ(), 2));

	// Check if the distance is less than the sum of the radius of the two spheres
	if (distance < (sphere1.radius() + sphere2.radius()))
		return true;

	// No collision
	return false;
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Sphere& sphere, const Geometry3D::Point& point)
{
	// Distance between the center of the sphere and the point
	float distance = sqrtf(powf(sphere.center().getX() - point.getX(), 2) +
		powf(sphere.center().getY() - point.getY(), 2) +
		powf(sphere.center().getZ() - point.getZ(), 2));

	// Check if the distance is less than the radius of the sphere
	if (distance < sphere.radius())
		return true;

	// No collision
	return false;
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Sphere& sphere, const Geometry3D::Line& line)
{
	Vector3 lineToSphere = sphere.center().toVector3() - line.getOrigin().toVector3();
	Vector3 lineDirection = line.getDirection();
	lineDirection.normalize();

	Vector3 center = sphere.center().toVector3();

	// Calculate the discriminant

	float d = lineToSphere.dot(lineDirection); 
	
	float c = lineToSphere.dot(lineToSphere) - (sphere.radius() * sphere.radius());

	float discriminant = d * d - c;

	// Check if the discriminant is less than 0
	if (discriminant < 0)
		// No collision
		return false;

	return true;
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Sphere& sphere, const Geometry3D::Plan& plan)
{
	Vector3 planNormal = plan.normal();
	float planDistance = plan.distance();

	// Calculate the distance between the center of the sphere and the plan

	// Find a point on the plan
	// Let a point of coordinate = (0, 0, z) z = -d/nz
	float z = - planDistance /planNormal.getZ();
	Vector3 pointOnPlan(0, 0, z);

	// Calculate the vector from the point on the plan to the center of the sphere
	Vector3 vectorToSphere = sphere.center().toVector3() - pointOnPlan;

	float distance = vectorToSphere.dot(planNormal);

	// Check if the distance is less than the radius of the sphere
	if (distance < sphere.radius())
		return true;

	// No collision
	return false;
}

#pragma endregion All functions Sphere 3D


#pragma region Plan Collision 3D

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Plan& plan1, const Geometry3D::Plan& plan2)
{
	Vector3 plan1Normal = plan1.normal();
	Vector3 plan2Normal = plan2.normal();

	Vector3 crossProduct = plan1Normal.cross(plan2Normal);

	// Check if the two plans are parallel
	if (crossProduct.magnitude() == 0.f)
	{
		// Check if the two plans are overlapping
		if (plan1.distance() / plan2.distance() != plan1Normal.getX() / plan2Normal.getX())
		{
			return false;
		}
	}	

	// Collision
	return true;
}

bool LibMath::Collisions3D::checkCollision(const Geometry3D::Plan& plan, const Geometry3D::Line& line)
{
	Vector3 planNormal = plan.normal();
	
	// Calculate the dot product between the plan normal and the line direction

	float dotProduct = planNormal.dot(line.getDirection());

	// Check if the dot product is equal to 0
	if (dotProduct == 0.f)
	{
		// The line is parallel to the plan
		return false;
	}
	 
	return true;
}

#pragma endregion All functions Plan 3D
