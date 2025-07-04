#ifndef LIBMATH_VECTOR_VECTOR4_H_
#define LIBMATH_VECTOR_VECTOR4_H_

namespace LibMath
{
	class Vector4
	{
	public:
						Vector4() = default;
		explicit		Vector4(float val);
						Vector4(float x, float y, float z, float k);
						Vector4(Vector4 const& other);


		Vector4&		operator=(Vector4 const& other) = default;

		float&			operator[](int n);								
		float			operator[](int n) const;

		bool			isUnit(void) const;

		float			dotProduct(Vector4 const& vec);

		float			magnitude(void) const;
		float			magnitudeSquare(void) const;

		void			normalize(void);

		void			homogenize(void);

		float			getX(void) const { return m_x; };
		float&			getX(void) { return m_x; };

		float			getY(void) const { return m_y; };
		float&			getY(void) { return m_y; };

		float			getZ(void) const { return m_z; };
		float&			getZ(void) { return m_z; };

		float			getK(void) const { return m_k; };
		float&			getK(void) { return m_k; };

	private:
		float m_x = 0.0f;
		float m_y = 0.0f;
		float m_z = 0.0f;
		float m_k = 0.0f;
	};

	bool				operator==(Vector4 const& vec1, Vector4 const& vec2);

	Vector4				operator-(Vector4 vec);

	Vector4				operator+(Vector4 vec1, Vector4 vec2);
	Vector4				operator-(Vector4 vec1, Vector4 vec2);
	Vector4				operator*(Vector4 vec, float val);
	Vector4				operator/(Vector4 vec, float val);


}



#endif // !LIBMATH_VECTOR_VECTOR4_H_
