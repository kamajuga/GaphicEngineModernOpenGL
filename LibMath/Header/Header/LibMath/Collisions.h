#pragma once
#pragma once
#include "GeometricObject3.h"
#include "GeometricObject2.h"

namespace LibMath
{
	namespace Collision2D
	{
		// Line Collisions
		bool checkCollisionLinePoint(const Geometry2D::Line& line, const Geometry2D::Point& point);
		bool checkCollisionLineLine(const Geometry2D::Line& line1, const Geometry2D::Line& line2);

		// AABB Collisions
		bool checkCollisionAABBPoint(const Geometry2D::AABB& aabb, const Geometry2D::Point& point);
		bool checkCollisionAABBLine(const Geometry2D::AABB& aabb, const Geometry2D::Line& line);
		bool checkCollisionAABBAABB(const Geometry2D::AABB& aabb1, const Geometry2D::AABB& aabb2);

		// OBB Collisions
		bool checkCollisionOBBOBB(const Geometry2D::OBB& obb1, const Geometry2D::OBB& obb2);

		// Circle Collisons
		bool checkCollisionCirclePoint(const Geometry2D::Circle& circle, const Geometry2D::Point& point);
		bool checkCollisionCircleLine(const Geometry2D::Circle& circle, const Geometry2D::Line& line);
		bool checkCollisionCircleCircle(const Geometry2D::Circle& circle1, const Geometry2D::Circle& circle2);
	}

	namespace Collisions3D
	{
		// Sphere Collisions
		bool checkCollisionSphereSphere(const Geometry3D::Sphere& sphere1, const Geometry3D::Sphere& sphere2);
		bool checkCollisionSpherePoint(const Geometry3D::Sphere& sphere, const Geometry3D::Point& point);
		bool checkCollisionSphereLine(const Geometry3D::Sphere& sphere, const Geometry3D::Line& line);
		bool checkCollisionSpherePlan(const Geometry3D::Sphere& sphere, const Geometry3D::Plan& plan);

		// Plan Collisions
		bool checkCollisionPlanPlan(const Geometry3D::Plan& plan1, const Geometry3D::Plan& plan2);
		bool checkCollisionPlanLine(const Geometry3D::Plan& plan, const Geometry3D::Line& line);
		bool checkCollisionPlanPoint(const Geometry3D::Plan& plan, const Geometry3D::Point& point);


		// Capsule Collisions
		bool checkCollisionCapsulePoint(const Geometry3D::Capsule& capsule, const Geometry3D::Point& point);
		bool checkCollisionCapsuleLine(const Geometry3D::Capsule& capsule, const Geometry3D::Line& line);
		bool checkCollisionCapsuleAABB(const Geometry3D::Capsule& capsule, const Geometry3D::AABB& aabb);
		bool checkCollisionCapsuleCapsule(const Geometry3D::Capsule& capsule1, const Geometry3D::Capsule& capsule2);
		bool checkCollisionCapsulePlan(const Geometry3D::Capsule& capsule1, const Geometry3D::Plan& plan);
		bool checkCollisionCapsuleSphere(const Geometry3D::Capsule& capsule1, const Geometry3D::Sphere& sphere);

		//AABB Collisions
		bool checkCollisionAABBLine(const Geometry3D::AABB& aabb, const Geometry3D::Line& line);
		bool checkCollisionAABBAABB(const Geometry3D::AABB& aabb1, const Geometry3D::AABB& aabb2);
		bool checkCollisionAABBPoint(const Geometry3D::AABB& aabb, const Geometry3D::Point& point);
		bool checkCollisionAABBShpere(const Geometry3D::AABB& aabb, const Geometry3D::Sphere& sphere);
	}
	
}