#ifndef LIBMATH_VECTOR_VECTOR2_H_
#define LIBMATH_VECTOR_VECTOR2_H_

#ifndef LIBMATH_ANGLE_RADIAN_H_
#include "LibMath/Angle/Radian.h"
#endif // !LIBMATH_ANGLE_RADIAN_H_

#include "LibMath/GeometricObject2.h"
#include "LibMath/LibMathFwd.h"

namespace LibMath
{
	class Vector2
	{
	public:
					Vector2();
		explicit	Vector2(float val);
					Vector2(float valx, float valy);
					Vector2(Vector2 const& other);
					Vector2(Geometry2D::Point const& point);
					~Vector2() = default;
	
		
		float&		operator[](int n);
		float		operator[](int n) const;
		Vector2&	operator=(const Vector2& other);
		Vector2&	operator-(void);							//prefix -Vector2
		Vector2&	operator+=(const Vector2& other);
		Vector2&	operator-=(const Vector2& other);
		Vector2&	operator*=(const Vector2& other);
		Vector2&	operator*=(const float& val);
		Vector2&	operator/=(const Vector2& other);
		Vector2&	operator/=(const float& val);

		float		magnitude(void) const;
		bool		isUnit(void) const;
		float		dotProduct(Vector2 vec) const;
		float		magnitudeSquare(void) const;
		void		normalize(void);
		LibMath::Radian		angleBetween(Vector2 vec) const;
		float		crossProduct(Vector2 vec) const;
		Vector2		projectOnto(Vector2 vec);
		Vector2		reflectOnto(Vector2 vec);

		friend		bool		operator==(Vector2 vec1, Vector2 vec2);
		friend		Vector2		operator-(Vector2 vec1, Vector2 vec2);
		friend		Vector2		operator+(Vector2 vec1, Vector2 vec2);
		friend		Vector2		operator*(Vector2 vec, float val);
		friend		Vector2		operator*(Vector2 vec1, Vector2 vec2);
		friend		Vector2		operator/(Vector2 vec, float val);
		friend		Vector2		operator/(Vector2 vec1, Vector2 vec2);

		float m_x = 0.f;
		float m_y = 0.f;
	private:
		
		 
	};

	bool		operator==(Vector2 vec1, Vector2 vec2);
	Vector2		operator-(Vector2 vec1, Vector2 vec2);
	Vector2		operator+(Vector2 vec1, Vector2 vec2);
	Vector2		operator*(Vector2 vec, float val);
	Vector2		operator/(Vector2 vec, float val);


}

#endif // !LIBMATH_VECTOR_VECTOR2_H_