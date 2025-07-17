#ifndef GEOMERTIC_OBJECT2_H_
#define GEOMERTIC_OBJECT2_H_
#include <iostream>

#include "LibMath/LibMathFwd.h"
#include "LibMath/Vector/Vector2.h"
#include "LibMath/Angle/Radian.h"
#include "LibMath/Trigonometry.h"



namespace LibMath
{
	namespace Geometry2D
	{

		class Point
		{
		public:
							Point() = default;
							Point(float x, float y);
							Point(Point const& other);
							~Point() = default;

			Point&			operator=(const Point& other);
			operator		LibMath::Vector2() const; // add test


			float			m_x = 0.f;
			float			m_y = 0.f;
		private:
			

		};

		bool				operator==(Point point1, Point Point);
		float				DistancebBetweenPoint(Point const& point1, Point const& point2);


		class Line
		{
		public:
							Line() = default;
							Line(Point const& p1, Point const& p2);
							Line(const Line& other);
							~Line() = default;

			Line&			operator=(const Line& other);
			float			lenght(void) const;
			float			lenghtSquare(void) const;

			Point			m_start;
			Point			m_end;

		private:
			

		};
		bool				operator==(Line line1, Line Line);
		bool				isPointOnSegment(Point const& point, Point const& segStart, Point const& segEnd);

		class AABB
		{
		public:
							AABB() = default;
			explicit		AABB(Point const center, float const height, float const width);
							AABB(AABB const& other);
							~AABB() = default;

			AABB&			operator=(const AABB& other);

			float			extentX(void) const;
			float			extentY(void) const;

			Point			getTopRightCorner(void) const;
			Point			getTopLeftCorner(void) const;
			Point			getBottomRightCorner(void) const;
			Point			getBottomLeftCorner(void) const;

			Point			m_center;
			float			m_height = 0.f;
			float			m_width = 0.f;
		private:
			


		};

		class OBB
		{
		public:
								OBB() = default;
			explicit			OBB(Point center, float height, float width);
								OBB(OBB const& other);
								~OBB() = default;

			OBB&				operator=(const OBB& other);


			void				rotate(LibMath::Radian rad);

			Point				getTopRightCorner(void) const;
			Point				getTopLeftCorner(void) const;
			Point				getBotRightCorner(void) const;
			Point				getBotLeftCorner(void) const;

			Point				m_center;
			float				m_height = 0.f;
			float				m_width = 0.f;
			LibMath::Radian		m_rotation;
		private:
			

		};

		LibMath::Vector2		normalVector(Point const& p1, Point const& p2);
		bool					overlapOnAxis(float& min1, float& max1, float& min2, float& max2);
		void					projectRectangleOnAxis(OBB const& rectangle, const LibMath::Vector2& axis, float& min, float& max);

		class Circle
		{
		public:
			friend			class Point;
							Circle() = default;
			explicit		Circle(Point const center, float const radius);
							Circle(Circle const& other);
							~Circle() = default;

			Circle&			operator=(const Circle& other);

			float			perimeter(void) const;
			float			area(void) const;

			Point			m_center;
			float			m_radius = 0.f;

		private:
			

		};
	}
}

#endif // !GEOMERTIC_OBJECT2_H_
