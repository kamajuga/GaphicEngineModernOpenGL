#pragma once
#pragma once
#include "GeometricObject3.h"

namespace LibMath
{
	namespace Collisions3D
	{
		// Sphere Collisions
		bool checkCollision(const Geometry3D::Sphere& sphere1, const Geometry3D::Sphere& sphere2);
		bool checkCollision(const Geometry3D::Sphere& sphere, const Geometry3D::Point& point);
		bool checkCollision(const Geometry3D::Sphere& sphere, const Geometry3D::Line& line);
		bool checkCollision(const Geometry3D::Sphere& sphere, const Geometry3D::Plan& plan);

		//Plan Collisions
		bool checkCollision(const Geometry3D::Plan& plan1, const Geometry3D::Plan& plan2);
		bool checkCollision(const Geometry3D::Plan& plan, const Geometry3D::Line& line);

	}
	
}