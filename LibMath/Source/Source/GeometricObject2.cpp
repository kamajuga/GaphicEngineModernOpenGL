#define _USE_MATH_DEFINES
#include <cmath>
#include "LibMath/GeometricObject2.h"

#define COLLISION_ACCURACY	0.000001f

#pragma region Point
LibMath::Geometry2D::Point::Point(float x, float y)
{
	m_x = x;
	m_y = y;
}

LibMath::Geometry2D::Point::Point(Point const& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
}

LibMath::Geometry2D::Point& LibMath::Geometry2D::Point::operator=(const Point& other)
{
	m_x = other.m_x;
	m_y = other.m_y;

	return *this;
}

 LibMath::Geometry2D::Point::operator LibMath::Vector2() const
{
	 return LibMath::Vector2(m_x, m_y);
}

bool LibMath::Geometry2D::operator==(Point point1, Point Point)
{
	return (std::abs(point1.m_x - Point.m_x) <= 1e-6f && std::abs(point1.m_y - Point.m_y) <=1e-6f);
}
float LibMath::Geometry2D::DistancebBetweenPoint(Point const& point1, Point const& point2)
{
	float deltaX = point2.m_x - point1.m_x;
	float deltaY = point2.m_y - point1.m_y;

	float sumDeltaSquare = (deltaX * deltaX) + (deltaY * deltaY);


	return std::sqrtf(sumDeltaSquare);
}
#pragma endregion All functions for Point

#pragma region Line

LibMath::Geometry2D::Line::Line(Point const& p1, Point const& p2)
{
	m_start = p1;
	m_end = p2;
}

LibMath::Geometry2D::Line::Line(const Line& other)
{
	m_start = other.m_start;
	m_end = other.m_end;
}

LibMath::Geometry2D::Line& LibMath::Geometry2D::Line::operator=(const Line& other)
{
	m_start = other.m_start;
	m_end = other.m_end;

	return *this;
}

float LibMath::Geometry2D::Line::lenght(void) const
{

	return sqrtf(powf(m_start.m_x - m_end.m_x, 2.0f) + powf(m_start.m_y - m_end.m_y, 2.0f));
}

float LibMath::Geometry2D::Line::lenghtSquare(void) const
{
	return powf(m_start.m_x - m_end.m_x, 2.0f) + powf(m_start.m_y - m_end.m_y, 2.0f);
}

bool LibMath::Geometry2D::operator==(Line line1, Line Line)
{
	return (line1.m_start == Line.m_start && Line.m_end == Line.m_end);
}

bool LibMath::Geometry2D::isPointOnSegment(Point const& point, Point const& segStart, Point const& segEnd)
{
	const float EPSILON =  1e-6f;
	float crossProduct = (point.m_y - segStart.m_y) * (segEnd.m_x - segStart.m_x) -
		(point.m_x - segStart.m_x) * (segEnd.m_y - segStart.m_y);

	if (std::abs(crossProduct) > EPSILON)
	{
		return false; // Not colinear
	}

	float dotProduct = (point.m_x - segStart.m_x) * (segEnd.m_x - segStart.m_x) +
		(point.m_y - segStart.m_y) * (segEnd.m_y - segStart.m_y);
	if (dotProduct < 0) {
		return false; // Outside segment
	}

	float squaredLength = (segEnd.m_x - segStart.m_x) * (segEnd.m_x - segStart.m_x) +
		(segEnd.m_y - segStart.m_y) * (segEnd.m_y - segStart.m_y);
	if (dotProduct > squaredLength) {
		return false; // Outside segment
	}

	return true; // Colinear and within bounds
}
#pragma endregion All functions for Line

#pragma region AABB

LibMath::Geometry2D::AABB::AABB(Point const center, float const height, float const width)
{
	m_center = center;
	m_height = height;
	m_width = width;
}

LibMath::Geometry2D::AABB::AABB(AABB const& other)
{
	m_center = other.m_center;
	m_height = other.m_height;
	m_width = other.m_width;
}

LibMath::Geometry2D::AABB& LibMath::Geometry2D::AABB::operator=(const AABB& other)
{
	m_center = other.m_center;
	m_height = other.m_height;
	m_width = other.m_width;

	return *this;
}

float LibMath::Geometry2D::AABB::extentX(void) const
{
	return m_width / 2;
}

float LibMath::Geometry2D::AABB::extentY(void) const
{
	return m_height / 2;
}

LibMath::Geometry2D::Point LibMath::Geometry2D::AABB::getTopRightCorner(void) const
{
	Point point(m_center.m_x + extentX(), m_center.m_y + extentY());

	return point;
}

LibMath::Geometry2D::Point LibMath::Geometry2D::AABB::getTopLeftCorner(void) const
{
	Point point(m_center.m_x - extentX(), m_center.m_y + extentY());

	return point;
}

LibMath::Geometry2D::Point LibMath::Geometry2D::AABB::getBottomRightCorner(void) const
{
	Point point(m_center.m_x + extentX(), m_center.m_y - extentY());

	return point;
}

LibMath::Geometry2D::Point LibMath::Geometry2D::AABB::getBottomLeftCorner(void) const
{
	Point point(m_center.m_x - extentX(), m_center.m_y - extentY());

	return point;
}
#pragma endregion All functions for AABB

#pragma region OBB

LibMath::Geometry2D::OBB::OBB(Point center, float height, float width)
{
	m_center = center;
	m_height = height;
	m_width = width;
	m_rotation = LibMath::Radian();
}

LibMath::Geometry2D::OBB::OBB(OBB const& other)
{
	m_center = other.m_center;
	m_height = other.m_height;
	m_width = other.m_width;
	m_rotation = other.m_rotation;
}

LibMath::Geometry2D::OBB& LibMath::Geometry2D::OBB::operator=(const OBB& other)
{
	m_center = other.m_center;
	m_height = other.m_height;
	m_width = other.m_width;

	return *this;
}

void LibMath::Geometry2D::OBB::rotate(LibMath::Radian rad)
{
	m_rotation = rad;
}

LibMath::Geometry2D::Point LibMath::Geometry2D::OBB::getTopRightCorner(void) const
{

	float halfHeight = m_height / 2;
	float halfWidth = m_width / 2;

	float cosR = LibMath::cos(m_rotation);
	float sinR = LibMath::sin(m_rotation);

	float x = m_center.m_x + (halfWidth * cosR - halfHeight * sinR);
	float y = m_center.m_y + (halfWidth * sinR + halfHeight * cosR);

	
	Point point(x, y);

	return point;
}

LibMath::Geometry2D::Point LibMath::Geometry2D::OBB::getTopLeftCorner(void) const
{
	float halfHeight = m_height / 2;
	float halfWidth = m_width / 2;

	float cosR = LibMath::cos(m_rotation);
	float sinR = LibMath::sin(m_rotation);

	float x = m_center.m_x + (-halfWidth * cosR - halfHeight * sinR);
	float y = m_center.m_y + (-halfWidth * sinR + halfHeight * cosR);

	Point point(x, y);

	return point;
}

LibMath::Geometry2D::Point LibMath::Geometry2D::OBB::getBotRightCorner(void) const
{
	float halfHeight = m_height / 2;
	float halfWidth = m_width / 2;

	float cosR = LibMath::cos(m_rotation);
	float sinR = LibMath::sin(m_rotation);

	float x = m_center.m_x + (halfWidth * cosR - (-halfHeight) * sinR);
	float y = m_center.m_y + (halfWidth * sinR + (-halfHeight) * cosR);

	Point point(x, y);

	return point;
}

LibMath::Geometry2D::Point LibMath::Geometry2D::OBB::getBotLeftCorner(void) const
{
	float halfHeight = m_height / 2;
	float halfWidth = m_width / 2;

	float cosR = LibMath::cos(m_rotation);
	float sinR = LibMath::sin(m_rotation);

	float x = m_center.m_x + (-halfWidth * cosR - (-halfHeight) * sinR);
	float y = m_center.m_y + (-halfWidth * sinR + (-halfHeight) * cosR);

	Point point(x, y);

	return point;
}

LibMath::Vector2 LibMath::Geometry2D::normalVector(Point const& p1, Point const& p2)
{
	float x = p2.m_x - p1.m_x;
	float y = p2.m_y - p1.m_y;

	LibMath::Vector2 normal(-y, x);

	normal.normalize();

	return normal;
}

bool LibMath::Geometry2D::overlapOnAxis(float& min1, float& max1, float& min2, float& max2)
{
	return !(max1 < min2 || max2 < min1);
}

void LibMath::Geometry2D::projectRectangleOnAxis(OBB const& rectangle, const LibMath::Vector2& axis, float& min, float& max)
{
	Point center = rectangle.m_center;

	LibMath::Radian rotation = rectangle.m_rotation;

	Point topRight = rectangle.getTopRightCorner();
	Point topLeft = rectangle.getTopLeftCorner();
	Point botRight = rectangle.getBotRightCorner();
	Point botLeft = rectangle.getBotLeftCorner();
	
	//Compute the corners of the rectangle
	LibMath::Vector2 corners[4] = {
		{topRight.m_x, topRight.m_x},
		{topLeft.m_x, topLeft.m_y},
		{botRight.m_x, botRight.m_y},
		{botLeft.m_x, botLeft.m_x}
	};



	// Project the corners onto the axis and find the min and max projections
	min = max = axis.dotProduct(corners[0]);

	for (int i = 1; i < 4; ++i)
	{
		float projection = axis.dotProduct(corners[i]);
		if (projection < min)
		{
			min = projection;
		}
		if (projection > max)
		{
			max = projection;
		}
	}

}

#pragma endregion All functions for OBB

#pragma region Circle

LibMath::Geometry2D::Circle::Circle(Point const center, float const radius)
{
	m_center = center;
	m_radius = radius;
}

LibMath::Geometry2D::Circle::Circle(Circle const& other)
{
	m_center = other.m_center;
	m_radius = other.m_radius;

}

LibMath::Geometry2D::Circle& LibMath::Geometry2D::Circle::operator=(const Circle& other)
{
	m_center = other.m_center;
	m_radius = other.m_radius;

	return *this;
}

float LibMath::Geometry2D::Circle::perimeter(void) const
{
	return static_cast<float>(M_PI) * 2 * m_radius;
}

float LibMath::Geometry2D::Circle::area(void) const
{
	return static_cast<float>(M_PI) * powf(m_radius, 2);
}

#pragma endregion 
