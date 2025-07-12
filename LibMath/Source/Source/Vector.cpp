#include "LibMath/Vector.h"
#include "LibMath/Matrix/Matrix3.h"
#include "LibMath/GeometricObject3.h"
#include <cmath>

#define EPSILON 1e-5

#pragma region Vector2D
LibMath::Vector2::Vector2()
{
	m_x = 0.0f;
	m_y = 0.0f;
}

LibMath::Vector2::Vector2(float val)
{
	m_x = val;
	m_y = val;
}

LibMath::Vector2::Vector2(float valx, float valy)
{
	m_x = valx;
	m_y = valy;
}

LibMath::Vector2::Vector2(Vector2 const& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
}

LibMath::Vector2::Vector2(Geometry2D::Point const& point)
{
	m_x = point.m_x;
	m_y = point.m_y;
}


float& LibMath::Vector2::operator[](int n)
{
	if (n == 0)
	{
		return m_x;
	}

	if (n == 1)
	{
		return m_y;
	}

	throw(std::invalid_argument("Invalid argument"));
}

float LibMath::Vector2::operator[](int n) const
{
	if (n == 0)
	{
		return m_x;
	}

	if (n == 1)
	{
		return m_y;
	}

	throw(std::invalid_argument("Invalid argument"));;
}

LibMath::Vector2& LibMath::Vector2::operator=(const Vector2& other)
{
	m_x = other.m_x;
	m_y = other.m_y;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator-(void)
{
	m_x = -m_x;
	m_y = -m_y;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator+=(const Vector2& other)
{
	m_x += other.m_x;
	m_y += other.m_y;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator-=(const Vector2& other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator*=(const Vector2& other)
{
	m_x *= other.m_x;
	m_y *= other.m_y;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator*=(const float& val)
{
	m_x *= val;
	m_y *= val;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator/=(const Vector2& other)
{
	if (other.m_x == 0.f || other.m_y == 0.f)
	{
		throw std::runtime_error("Error: Division by zero \n x or y component is null.");
	}

	m_x /= other.m_x;
	m_y /= other.m_y;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator/=(const float& val)
{
	if (val == 0.f)
	{
		throw std::runtime_error("Error: Division by zero");
	}

	m_x /= val;
	m_y /= val;

	return *this;
}

float LibMath::Vector2::magnitude(void) const
{
	return sqrtf(powf(m_x, 2) + powf(m_y, 2));
}

bool LibMath::Vector2::isUnit(void) const
{
	return (abs(magnitude() - 1.0f)) <= 0.0000001f;
}

float LibMath::Vector2::dotProduct(Vector2 vec) const
{
	return (float)m_x * vec.m_x + m_y * vec.m_y;
}

float LibMath::Vector2::magnitudeSquare(void) const
{
	//float mag = magnitude();
	return powf(m_x, 2) + powf(m_y, 2);
}

void LibMath::Vector2::normalize(void)
{
	float mag = magnitude();

	m_x /= mag;
	m_y /= mag;
}

LibMath::Radian LibMath::Vector2::angleBetween(Vector2 vec) const
{
	float dot_p = dotProduct(vec);

	float mag = magnitude();

	float other_mag = vec.magnitude();

	float cos_angle = dot_p / (mag * other_mag);

	Radian angle = acos(cos_angle); // return radian

	return angle;
}

float LibMath::Vector2::crossProduct(Vector2 vec) const
{
	return (m_x * vec.m_y - m_y * vec.m_x);
}

LibMath::Vector2 LibMath::Vector2::projectOnto(Vector2 vec)
{
	float coef = dotProduct(vec) / vec.magnitudeSquare();

	m_x = coef * vec.m_x;

	m_y = coef * vec.m_y;

	return *this;
}

LibMath::Vector2 LibMath::Vector2::reflectOnto(Vector2 vec)
{
	// w = v - 2 ( projonto(vec))

	Vector2 normalized_vec = vec;

	normalized_vec.normalize();

	float dot_p = dotProduct(normalized_vec);

	Vector2 vec2 = normalized_vec * dot_p;

	m_x = m_x - 2 * dot_p * normalized_vec.m_x;
	m_y = m_y - 2 * dot_p * normalized_vec.m_y;

	return *this;
}

bool LibMath::operator==(Vector2 vec1, Vector2 vec2)
{
	return (vec1.m_x == vec2.m_x && vec1.m_y == vec2.m_y);
}

LibMath::Vector2 LibMath::operator-(Vector2 vec1, Vector2 vec2)
{
	return Vector2(vec1.m_x - vec2.m_x, vec1.m_y - vec2.m_y);
}

LibMath::Vector2 LibMath::operator+(Vector2 vec1, Vector2 vec2)
{
	return Vector2(vec1.m_x + vec2.m_x, vec1.m_y + vec2.m_y);
}

LibMath::Vector2 LibMath::operator*(Vector2 vec, float val)
{
	return Vector2(vec.m_x * val, vec.m_y * val);
}

LibMath::Vector2 LibMath::operator*(Vector2 vec1, Vector2 vec2)
{
	return Vector2(vec1.m_x * vec2.m_x, vec1.m_y * vec2.m_y);
}

LibMath::Vector2 LibMath::operator/(Vector2 vec, float val)
{
	if (val == 0.f)
	{
		throw(std::invalid_argument("Error: Division by zero"));
	}
	return Vector2(vec.m_x / val, vec.m_y / val);
}

LibMath::Vector2 LibMath::operator/(Vector2 vec1, Vector2 vec2)
{
	return Vector2(vec1.m_x / vec2.m_x, vec1.m_y / vec2.m_y);
}

#pragma endregion 

#pragma region Vector3D

LibMath::Vector3::Vector3(float val)
{
	m_x = val;
	m_y = val;
	m_z = val;
}

LibMath::Vector3::Vector3(float val_x, float val_y, float val_z)
{
	m_x = val_x;
	m_y = val_y;
	m_z = val_z;
}

LibMath::Vector3::Vector3(Vector3 const& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	m_z = other.m_z;
}

LibMath::Vector3::Vector3(LibMath::Geometry3D::Point const& point)
{
	m_x = point.m_x;
	m_y = point.m_y;
	m_z = point.m_z;
}

LibMath::Vector3 LibMath::Vector3::zero(void)
{
	return Vector3(0.0f);
}

LibMath::Vector3 LibMath::Vector3::one(void)
{
	return Vector3(1.0f);
}

LibMath::Vector3 LibMath::Vector3::up(void)
{
	return Vector3(0.0f, 1.0f, 0.0f);
}

LibMath::Vector3 LibMath::Vector3::down(void)
{
	return Vector3(0.0f, -1.0f, 0.0f);
}

LibMath::Vector3 LibMath::Vector3::left(void)
{
	return Vector3(-1.0f, 0.0f, 0.0f);
}

LibMath::Vector3 LibMath::Vector3::right(void)
{
	return Vector3(1.0f, 0.0f, 0.0f);
}

LibMath::Vector3 LibMath::Vector3::front(void)
{
	return Vector3(0.0f, 0.0f, 1.0f);
}

LibMath::Vector3 LibMath::Vector3::back(void)
{
	return Vector3(0.0f, 0.0f, -1.0f);
}

float& LibMath::Vector3::operator[](int n)
{
	if (n == 0)
	{
		return m_x;
	}

	if (n == 1)
	{
		return m_y;
	}

	if (n == 2)
	{
		return m_z;
	}

	throw(std::out_of_range("Error: index out of range"));
}

float LibMath::Vector3::operator[](int n) const
{
	if (n == 0)
	{
		return m_x;
	}

	if (n == 1)
	{
		return m_y;
	}

	if (n == 2)
	{
		return m_z;
	}

	throw(std::out_of_range("Error: index out of range"));
}

LibMath::Radian LibMath::Vector3::angleFrom(Vector3 const& vec) const
{
	float dot_p = dot(vec);
	float mag_a = magnitude();
	float mag_b = vec.magnitude();

	float cos_theta = dot_p / (mag_a * mag_b);

	return Radian(LibMath::acos(cos_theta));
}

LibMath::Vector3 LibMath::Vector3::cross(Vector3 const& vec) const
{
	float x = (m_y * vec.m_z) - (m_z * vec.m_y);
	float y = -((m_x * vec.m_z) - (m_z * vec.m_x));
	float z = (m_x * vec.m_y) - (m_y * vec.m_x);

	return Vector3(x, y, z);
}

float LibMath::Vector3::distanceFrom(Vector3 const& vec) const
{
	float x_comp = powf(vec.m_x - m_x, 2);
	float y_comp = powf(vec.m_y - m_y, 2);
	float z_comp = powf(vec.m_z - m_z, 2);

	return sqrtf(x_comp + y_comp + z_comp);
}

float LibMath::Vector3::distanceSquaredFrom(Vector3 const& vec) const
{
	float x_comp = powf(vec.m_x - m_x, 2);
	float y_comp = powf(vec.m_y - m_y, 2);
	float z_comp = powf(vec.m_z - m_z, 2);

	return x_comp + y_comp + z_comp;
}

float LibMath::Vector3::distance2DFrom(Vector3 const& vec) const
{
	float x_comp = powf(vec.m_x - m_x, 2);
	float y_comp = powf(vec.m_y - m_y, 2);

	return sqrtf(x_comp + y_comp);
}

float LibMath::Vector3::distance2DSquaredFrom(Vector3 const& vec) const
{
	float x_comp = powf(vec.m_x - m_x, 2);
	float y_comp = powf(vec.m_y - m_y, 2);

	return x_comp + y_comp;
}

float LibMath::Vector3::dot(Vector3 const& vec) const
{
	float x_comp = m_x * vec.m_x;
	float y_comp = m_y * vec.m_y;
	float z_comp = m_z * vec.m_z;

	return x_comp + y_comp + z_comp;
}

bool LibMath::Vector3::isLongerThan(Vector3 const& vec) const
{
	float mag_a = magnitude();
	float mag_b = vec.magnitude();

	return mag_a > mag_b;
}

bool LibMath::Vector3::isShorterThan(Vector3 const& vec) const
{
	float mag_a = magnitude();
	float mag_b = vec.magnitude();

	return mag_a < mag_b;
}

bool LibMath::Vector3::isUnitVector(void) const
{
	return std::abs(magnitude() - 1) <= EPSILON  ;
}

float LibMath::Vector3::magnitude(void) const
{
	return sqrtf(powf(m_x, 2) + powf(m_y, 2) + powf(m_z, 2));
}

float LibMath::Vector3::magnitudeSquared(void) const
{
	return powf(m_x, 2) + powf(m_y, 2) + powf(m_z, 2);
}

void LibMath::Vector3::normalize(void)
{
	float mag = magnitude();

	// Avoid division by zero

	if (mag == 0.f)
	{
		throw(std::invalid_argument("Error: Can not normalize vector of Magnitude zero"));
	}

	if (mag == 1)
	{
		return;
	}
	m_x /= mag;
	m_y /= mag;
	m_z /= mag;
}

void LibMath::Vector3::projectOnto(Vector3 const& vec)
{
	float coef = dot(vec) / vec.magnitudeSquared();

	m_x = coef * vec.m_x;

	m_y = coef * vec.m_y;

	m_z = coef * vec.m_z;
}

void LibMath::Vector3::reflectOnto(Vector3 const& vec)
{

	Vector3 normalized_vec = vec;

	normalized_vec.normalize();

	float dot_p = dot(normalized_vec);

	Vector3 vec3 = normalized_vec * dot_p;

	m_x = m_x - 2 * dot_p * normalized_vec.m_x;
	m_y = m_y - 2 * dot_p * normalized_vec.m_y;
	m_z = m_z - 2 * dot_p * normalized_vec.m_z; 
}

// Ajoutez ces fonctions à votre classe Vector3

void LibMath::Vector3::rotateX(Radian angle)
{
	float c = cos(angle);
	float s = sin(angle);

	float newY = c * m_y - s * m_z;
	float newZ = s * m_y + c * m_z;

	m_y = newY;
	m_z = newZ;
}

void LibMath::Vector3::rotateY(Radian angle)
{
	float c = cos(angle);
	float s = sin(angle);

	float newX = c * m_x + s * m_z;
	float newZ = -s * m_x + c * m_z;

	m_x = newX;
	m_z = newZ;
}

void LibMath::Vector3::rotateZ(Radian angle)
{
	float c = cos(angle);
	float s = sin(angle);

	float newX = c * m_x - s * m_y;
	float newY = s * m_x + c * m_y;

	m_x = newX;
	m_y = newY;
}

void LibMath::Vector3::rotate(Radian rad_x, Radian rad_y, Radian rad_z)
{
	// GLM utilise yawPitchRoll(angles.z, angles.x, angles.y)
	// avec une matrice en column-major
	float yaw = rad_z.raw();    // angles.z
	float pitch = rad_x.raw();  // angles.x
	float roll = rad_y.raw();   // angles.y

	// Calcul des cosinus et sinus
	float ch = std::cos(yaw);   // cos(yaw)
	float sh = std::sin(yaw);   // sin(yaw)
	float cp = std::cos(pitch); // cos(pitch)
	float sp = std::sin(pitch); // sin(pitch)
	float cb = std::cos(roll);  // cos(roll)
	float sb = std::sin(roll);  // sin(roll)

	// Matrice de rotation yawPitchRoll de GLM (column-major)
	float m00 = ch * cb + sh * sp * sb;
	float m01 = sb * cp;
	float m02 = -sh * cb + ch * sp * sb;
	float m10 = -ch * sb + sh * sp * cb;
	float m11 = cb * cp;
	float m12 = sb * sh + ch * sp * cb;
	float m20 = sh * cp;
	float m21 = -sp;
	float m22 = ch * cp;

	// Application de la matrice au vecteur (column-major)
	float x = m_x;
	float y = m_y;
	float z = m_z;

	m_x = (m00 * x + m10 * y + m20 * z);  // Colonne 0
	m_y = (m01 * x + m11 * y + m21 * z);  // Colonne 1
	m_z = (m02 * x + m12 * y + m22 * z);  // Colonne 2
}

void LibMath::Vector3::rotate(Radian angle, Vector3 const& vec)
{
	Vector3 normalizedAxis = vec;

	normalizedAxis.normalize();

	*this = rotateArroundAxis(*this, normalizedAxis, angle);
}

void LibMath::Vector3::scale(Vector3 const& vec)
{
	m_x *= vec.m_x;
	m_y *= vec.m_y;
	m_z *= vec.m_z;
}

std::string LibMath::Vector3::string(void) const
{
	return std::string("{" + formatNumber(m_x) + "," + formatNumber(m_y) + "," + formatNumber(m_z) + "}");
}

std::string LibMath::Vector3::stringLong(void) const
{
	return std::string("Vector3{ x:" + formatNumber(m_x) + ", y:" + formatNumber(m_y) + ", z:" + formatNumber(m_z) + " }");
	//return std::string();
}

void LibMath::Vector3::translate(Vector3 const& vec)
{
	m_x += vec.m_x;
	m_y += vec.m_y;
	m_z += vec.m_z;
}

LibMath::Vector3 LibMath::rotateArroundAxis(Vector3 const& vector, Vector3 const& axis, Radian angle)
{
	// Normalize the axis vector
	Vector3 normalizedAxis = axis;
	normalizedAxis.normalize();

	// Precompute trigonometric values
	float cosTheta = cos(angle);
	float sinTheta = sin(angle);
	float oneMinusCosTheta = 1 - cosTheta;

	// Extract axis components
	float x = normalizedAxis.m_x;
	float y = normalizedAxis.m_y;
	float z = normalizedAxis.m_z;

	// Compute the rotation matrix elements
	float r11 = cosTheta + x * x * oneMinusCosTheta;
	float r12 = x * y * oneMinusCosTheta - z * sinTheta;
	float r13 = x * z * oneMinusCosTheta + y * sinTheta;

	float r21 = y * x * oneMinusCosTheta + z * sinTheta;
	float r22 = cosTheta + y * y * oneMinusCosTheta;
	float r23 = y * z * oneMinusCosTheta - x * sinTheta;

	float r31 = z * x * oneMinusCosTheta - y * sinTheta;
	float r32 = z * y * oneMinusCosTheta + x * sinTheta;
	float r33 = cosTheta + z * z * oneMinusCosTheta;

	// Apply the rotation matrix to the vector
	float newX = vector.m_x * r11 + vector.m_y * r12 + vector.m_z * r13;
	float newY = vector.m_x * r21 + vector.m_y * r22 + vector.m_z * r23;
	float newZ = vector.m_x * r31 + vector.m_y * r32 + vector.m_z * r33;

	return { newX, newY, newZ };
}

std::string LibMath::formatNumber(float value)
{
	bool isNegative = value < 0; // Check if the value is negative
	value = std::abs(value); // Work with the absolute value

	if (std::fmod(value, 1.0f) == 0.0f) { // Check if the value is whole
		return std::to_string(isNegative ? -static_cast<int>(value) : static_cast<int>(value)); // Handle negative numbers
	}
	else {
		// Manually format to 1 decimal place
		int intPart = static_cast<int>(value);
		float fracPart = value - intPart;
		int decimal = static_cast<int>(std::round(fracPart * 10));
		return (intPart == 0 && isNegative ? "-0" : std::to_string(isNegative ? -intPart : intPart)) + "." + std::to_string(decimal);
	}
}

bool LibMath::operator==(Vector3 const& vec1, Vector3 const& vec2)
{
	
	return (vec1.m_x == vec2.m_x && vec1.m_y == vec2.m_y && vec1.m_z == vec2.m_z);
}

bool LibMath::operator!=(Vector3 const& vec1, Vector3 const& vec2)
{
	return (vec1.m_x != vec2.m_x || vec1.m_y != vec2.m_y || vec1.m_z != vec2.m_z);
}

LibMath::Vector3 LibMath::operator-(Vector3 vec)
{
	return Vector3(-vec.m_x, -vec.m_y, -vec.m_z);
}

LibMath::Vector3 LibMath::operator+(Vector3 vec1, Vector3 const& vec2)
{
	return Vector3(vec1.m_x + vec2.m_x, vec1.m_y + vec2.m_y, vec1.m_z + vec2.m_z);
}

LibMath::Vector3 LibMath::operator-(Vector3 vec1, Vector3 const& vec2)
{
	return Vector3(vec1.m_x - vec2.m_x, vec1.m_y - vec2.m_y, vec1.m_z - vec2.m_z);
}

LibMath::Vector3 LibMath::operator*(Vector3 vec1, Vector3 const& vec2)
{
	return Vector3(vec1.m_x * vec2.m_x, vec1.m_y * vec2.m_y, vec1.m_z * vec2.m_z);
}

LibMath::Vector3 LibMath::operator*(Vector3 vec, float val)
{
	return Vector3(vec.m_x * val, vec.m_y * val, vec.m_z * val);
}

LibMath::Vector3 LibMath::operator/(Vector3 vec1, Vector3 const& vec2)
{
	return Vector3(vec1.m_x / vec2.m_x, vec1.m_y /vec2.m_y, vec1.m_z / vec2.m_z);
}

LibMath::Vector3 LibMath::operator/(Vector3 vec, float val)
{
	if (val == 0)
	{
		throw(std::invalid_argument("Division by zero"));
	}
	return Vector3(vec.m_x / val, vec.m_y / val, vec.m_z /val );
}

LibMath::Vector3& LibMath::operator+=(Vector3& vec1, Vector3 const& vec2)
{
	vec1.m_x += vec2.m_x;
	vec1.m_y += vec2.m_y;
	vec1.m_z += vec2.m_z;

	return vec1;
}

LibMath::Vector3& LibMath::operator-=(Vector3& vec1, Vector3 const& vec2)
{
	vec1.m_x -= vec2.m_x;
	vec1.m_y -= vec2.m_y;
	vec1.m_z -= vec2.m_z;

	return vec1;
}

LibMath::Vector3& LibMath::operator*=(Vector3& vec1, Vector3 const& vec2)
{
	vec1.m_x *= vec2.m_x;
	vec1.m_y *= vec2.m_y;
	vec1.m_z *= vec2.m_z;

	return vec1;
}

LibMath::Vector3& LibMath::operator*=(Vector3& vec, float val)
{
	vec.m_x *= val;
	vec.m_y *= val;
	vec.m_z *= val;

	return vec;
}

LibMath::Vector3& LibMath::operator/=(Vector3& vec1, Vector3 const& vec2)
{
	if (vec2.m_x == 0.f || vec2.m_y == 0.f || vec2.m_z == 0.f)
	{
		throw std::runtime_error("Error: Division by zero. \n x, y or z component is zero");
	}

	vec1.m_x /= vec2.m_x;
	vec1.m_y /= vec2.m_y;
	vec1.m_z /= vec2.m_z;

	return vec1;
}

LibMath::Vector3& LibMath::operator/=(Vector3& vec, float val)
{
	if (val == 0.f)
	{
		throw std::runtime_error("Error: Division by zero");
	}

	vec.m_x /= val;
	vec.m_y /= val;
	vec.m_z /= val;

	return vec;
}

std::ostream& LibMath::operator<<(std::ostream& os, Vector3 const& vec)
{
	return os << "{" << vec.m_x << "," << vec.m_y << "," << vec.m_z << "}";
}

std::istream& LibMath::operator>>(std::istream& is, Vector3& vec)
{
	char c;
	is >> c;
	is >> vec.m_x;
	is >> c;
	is >> vec.m_y;
	is >> c;
	is >> vec.m_z;
	is >> c;

	return is;
}

#pragma endregion

#pragma region Vector4D

LibMath::Vector4::Vector4(float val)
{
	m_x = val;
	m_y = val;
	m_z = val;
	m_k = val;
}

LibMath::Vector4::Vector4(float x, float y, float z, float k)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_k = k;
}

LibMath::Vector4::Vector4(Vector4 const& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	m_z = other.m_z;
	m_k = other.m_k;
}

LibMath::Vector4::Vector4(LibMath::Vector3 const& vec3, const float& val)
{
	m_x = vec3.m_x;
	m_y = vec3.m_y;
	m_z = vec3.m_z;
	m_k = val;
}

float& LibMath::Vector4::operator[](int n)
{
	if (n == 0)
	{
		return m_x;
	}

	if (n == 1)
	{
		return m_y;
	}

	if (n == 2)
	{
		return m_z;
	}

	if (n == 3)
	{
		return m_k;
	}

	throw(std::out_of_range("Error: Index out of range"));
}

float LibMath::Vector4::operator[](int n) const
{
	if (n == 0)
	{
		return m_x;
	}

	if (n == 1)
	{
		return m_y;
	}

	if (n == 2)
	{
		return m_z;
	}

	if (n == 3)
	{
		return m_k;
	}

	throw(std::out_of_range("Error: Index out of range"));
}

bool LibMath::Vector4::isUnit(void) const
{
	return std::abs(magnitude() - 1) <= EPSILON;
}

float LibMath::Vector4::dotProduct(Vector4 const& vec)
{
	float x_comp = m_x * vec.m_x;
	float y_comp = m_y * vec.m_y;
	float z_comp = m_z * vec.m_z;
	float k_comp = m_k * vec.m_k;

	return x_comp + y_comp + z_comp + k_comp;
}

float LibMath::Vector4::magnitude(void) const
{
	float x = powf(m_x, 2.0f);
	float y = powf(m_y, 2.0f);
	float z = powf(m_z, 2.0f);
	float k = powf(m_k, 2.0f);

	return sqrtf(x + y + z + k);
}

float LibMath::Vector4::magnitudeSquare(void) const
{
	float x = powf(m_x, 2.0f);
	float y = powf(m_y, 2.0f);
	float z = powf(m_z, 2.0f);
	float k = powf(m_k, 2.0f);

	return x + y + z + k;
}

void LibMath::Vector4::homogenize(void)
{
	m_x /= m_k;
	m_y /= m_k;
	m_z /= m_k;
	m_k = 1;
}

bool LibMath::operator==(Vector4 const& vec1, Vector4 const& vec2)
{
	return ((vec1.m_x == vec2.m_x) && (vec1.m_y == vec2.m_y) && (vec1.m_z == vec2.m_z) && (vec1.m_k == vec2.m_k));
}

LibMath::Vector4 LibMath::operator-(Vector4 vec)
{
	return Vector4(-vec.m_x, -vec.m_y, -vec.m_z, -vec.m_k);
}

LibMath::Vector4 LibMath::operator+(Vector4 vec1, Vector4 vec2)
{
	return Vector4(vec1.m_x + vec2.m_x, vec1.m_y + vec2.m_y, vec1.m_z + vec2.m_z, vec1.m_k + vec2.m_k);
}

LibMath::Vector4 LibMath::operator-(Vector4 vec1, Vector4 vec2)
{
	return Vector4(vec1.m_x - vec2.m_x, vec1.m_y - vec2.m_y, vec1.m_z - vec2.m_z, vec1.m_k - vec2.m_k);
}

LibMath::Vector4 LibMath::operator*(Vector4 vec, float val)
{
	return Vector4(vec.m_x * val, vec.m_y * val, vec.m_z * val, vec.m_k * val);
}

LibMath::Vector4 LibMath::operator/(Vector4 vec, float val)
{
	if (val == 0)
	{
		throw(std::invalid_argument("Error: division by zero"));
	}
	return Vector4(vec.m_x / val, vec.m_y / val, vec.m_z / val, vec.m_k / val);
}

#pragma endregion