#ifndef GEOMETRIC_OBJECT3_H
#define	GEOMETRIC_OBJECT3_H

#include "LibMath/Vector/Vector3.h"

namespace LibMath
{
	namespace Geometry3D
	{
		// Todo: Implement tests for all the geometric objects
		class Point
		{
		public:
							Point() = default;
							Point(const float x, const float y, const float z);
							Point(const Point& other);
							~Point() = default;

			Point&			operator=(const Point& other);

			const Vector3			toVector3(void) const { return Vector3(m_x, m_y, m_z); };

			float			getX(void) { return m_x; };
			float			getY(void) { return m_y; };
			float			getZ(void) { return m_z; };

			float const		getX(void) const { return m_x; };
			float const		getY(void) const { return m_y; };
			float const		getZ(void) const { return m_x; };

			

		private:
			float			m_x = 0.0f;
			float			m_y = 0.0f;
			float			m_z = 0.0f;

		};

		class Line
		{
		public:
									Line() = default;
									Line(const Point& point, const Vector3& dir);   // Director vector should be a unit vector
									Line(const Line& other);
									~Line() = default;

			Line&					operator=(const Line& other);

			const Point&			getOrigin(void) const { return m_origin; };
			const Vector3&			getDirection(void) const { return m_direction; };

			

		private:
			Point			m_origin;
			Vector3			m_direction;
		};

		class Plan
		{
		public:
							Plan() = default;
							Plan(const Vector3& normal, const float& distance);
							Plan(const Plan& other);
							~Plan() = default;

			Plan&			operator=(const Plan& other);

			const Vector3			normal(void) const { return m_normal; };
			const float			distance(void) const { return m_distance; };

			


		private:
			Vector3			m_normal;
			float			m_distance;

		};

		class AABB
		{
		public:
							AABB() = default;
							AABB(const Point& center, const float& width, const float& height, const float& depth);
							AABB(const AABB& other);
							~AABB() = default;

			AABB&			operator=(const AABB& other);

			Point			center(void);
			float			extentX(void) const;
			float			extentY(void) const;
			float			extentZ(void) const;

		private:

			Point			m_center;
			float			m_width = 0.f; // length on X axis
			float			m_height = 0.f; // length on Y axis
			float			m_depth = 0.f; // length on Z axis
		};

		class OBB
		{
		public:
							OBB() = default;
							OBB(const Point& center, const float& width, const float& height, const float& m_depth, const Radian& rotation);
							OBB(const OBB& other);
							~OBB() = default;

			OBB&			operator=(const OBB& other);

			Radian			rotation(void);


		private:
			Point			m_center;
			float			m_width = 0.f;
			float			m_height = 0.f;
			float			m_depth = 0.f;
			LibMath::Radian m_rotation; 
		};

		class Sphere
		{
		public:
							Sphere() = default;
							Sphere(const Point& center, const float& radius);
							Sphere(const Sphere& other);
							~Sphere() = default;

			Sphere&			operator=(const Sphere& other);

			const Point&			center(void) const { return m_center; };
			const float&			radius(void) const { return m_radius; };

		private:
			Point			m_center;
			float			m_radius = 0.f;
		};

		class Capsule
		{
		public:
			Capsule();
			~Capsule();




		private:
			Point			m_pointA;
			Point			m_pointB;
			float			m_radius = 0.f;

		};

	}
	
}


#endif // !GEOMETRIC_OBJECT3_H
