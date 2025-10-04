#ifndef GEOMETRIC_OBJECT3_H
#define	GEOMETRIC_OBJECT3_H

#include "LibMath/Angle/Radian.h"
#include "LibMath/Vector/Vector3.h"
#include "LibMath/Matrix/Matrix4.h"

namespace LibMath
{
	namespace Geometry3D
	{
		
		class Object3D
		{
		public:
			virtual void update(LibMath::Matrix4& transMat) = 0;
			virtual ~Object3D() = default;

		};

		// Todo: Implement tests for all the geometric objects
		class Point : public Object3D
		{
		public:
									Point() = default;
									Point(const float x, const float y, const float z);
									Point(const Point& other);
									Point(Vector3 const& vec);
									~Point() = default;

			Point&					operator=(const Point& other);

			Vector3					toVector3() const;

			virtual void			update(LibMath::Matrix4& transMat) override;

			float					getDistanceSquared(const Point&) const;
			float					getDistance(const Point&) const;

			LibMath::Vector3					operator-(const Point& point) const;

			float					m_x = 0.0f;
			float					m_y = 0.0f;
			float					m_z = 0.0f;

		private:
			

		};

		class Line : public Object3D
		{
		public:
			Line() = default;
			Line(const Point& point, const LibMath::Vector3& dir);   // Director vector should be a unit vector
			Line(const Point& pointStart, const Point& pointEnd);
			Line(const Point& point, const LibMath::Vector3& dir, const float& scalair);
			Line(const Line& other);
			~Line() = default;

			Line& operator=(const Line& other);
			Line operator*(const float& scalair);

			virtual void			update(LibMath::Matrix4& transMat) override;

			Point			m_origin;
			LibMath::Vector3			m_direction;
			float			m_length = 0.f;
		private:

		};

		class Plan : public Object3D
		{
		public:
			Plan() = default;
			Plan(const LibMath::Vector3& normal, const float& distance);
			Plan(const Plan& other);
			~Plan() = default;

			Plan& operator=(const Plan& other);



			Vector3			m_normal;
			float			m_distance = 0.f;

		private:
			

		};

		class AABB :public Object3D
		{
		public:
			AABB() = default;
			AABB(const Point& center, const float& width, const float& height, const float& depth);
			AABB(const AABB& other);
			~AABB() = default;

			AABB& operator=(const AABB& other);

			virtual void			update(LibMath::Matrix4& transMat) override;

			float			extentX(void) const;
			float			extentY(void) const;
			float			extentZ(void) const;

			Point			m_center;
			float			m_width = 0.f; // length on X axis
			float			m_height = 0.f; // length on Y axis
			float			m_depth = 0.f; // length on Z axis
		private:

			
		};

		class OBB : public Object3D
		{
		public:
			OBB() = default;
			OBB(const Point& center, const float& width, const float& height, const float& m_depth, const Radian& rotation);
			OBB(const OBB& other);
			~OBB() = default;

			virtual void			update(LibMath::Matrix4& transMat) override;

			OBB& operator=(const OBB& other);

			Point			m_center;
			float			m_width = 0.f;
			float			m_height = 0.f;
			float			m_depth = 0.f;
			Radian m_rotation;

		private:
			
		};

		class Sphere : public Object3D
		{
		public:
			Sphere() = default;
			Sphere(const Point& center, const float& radius);
			Sphere(const Sphere& other);
			~Sphere() = default;

			virtual void			update(LibMath::Matrix4& transMat) override;

			Sphere& operator=(const Sphere& other);

			Point			m_center;
			float			m_radius = 0.f;

		private:
			
		};

		class Capsule :public Object3D
		{
		public:
			Capsule() = default;
			Capsule(const Point& pointA, const Point& pointB, const float& radius);
			Capsule(const Capsule& other);
			~Capsule() = default;

			virtual void			update(LibMath::Matrix4& transMat) override;

			Capsule& operator=(const Capsule& other);

			Point			m_pointA;
			Point			m_pointB;
			float			m_radius = 0.f;

		private:

		};

		Point			getClosestToAABB(const LibMath::Geometry3D::AABB&, const Point&);
		Point			getClosestToSegment(const Point&, const Point&, const Point&);

	}

}

#endif // !GEOMETRIC_OBJECT3_H
