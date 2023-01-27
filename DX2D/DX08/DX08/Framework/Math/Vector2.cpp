#include "framework.h"
#include "Vector2.h"

Vector2::Vector2()
: XMFLOAT2()
{
}

Vector2::Vector2(float x, float y)
: XMFLOAT2(x, y)
{
}

Vector2::Vector2(int x, int y)
: XMFLOAT2((float)x, (float)y)
{
}

Vector2::~Vector2()
{
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	Vector2 result;

	result.x = x + other.x;
	result.y = y + other.y;

	return result;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(const float& value) const
{
	return Vector2(x * value, y * value);
}

bool Vector2::operator<(const Vector2& other) const
{
	if (y != other.y)
		return y < other.y;
	return x < other.x;
}

bool Vector2::operator>(const Vector2& other) const
{
	if (y != other.y)
		return y > other.y;
	return x > other.x;
}

bool Vector2::operator==(const Vector2& other) const
{
	if (x == other.x && y == other.y)
		return true;
	return false;
}

bool Vector2::operator!=(const Vector2& other) const
{
	if (!(operator==(other)))
		return true;
	return false;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	this->x = this->x + other.x;
	this->y = this->y + other.y;

	return (*this);
}

Vector2& Vector2::operator=(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;

	return (*this);
}

Vector2& Vector2::operator*=(const float& value)
{
	this->x *= value;
	this->y *= value;

	return (*this);
}

Vector2& Vector2::operator++()
{
	++x;
	++y;

	return (*this);
}

Vector2 Vector2::operator++(int)
{
	Vector2 temp = *this;

	++x;
	++y;

	return temp;
}

float Vector2::Length() const
{
	return sqrt(powf(x, 2) + powf(y, 2));
}

float Vector2::Manhattan(const Vector2& other) const
{
	return abs(x - other.x) + abs(y - other.y);
}

float Vector2::Dot(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

float Vector2::Cross(const Vector2& other) const
{
	return x * other.y - y * other.x;
}

bool Vector2::IsBetween(const Vector2& a, const Vector2& b)
{
	float z1 = this->Cross(a);
	float z2 = this->Cross(b);

	if (z1 * z2 < 0)
		return true;

	return false;
}

float Vector2::Angle() const
{
	return atan2(y, x);
}

float Vector2::Angle(const Vector2& other) const
{
	float dot = this->Dot(other);
	float aLength = this->Length();
	float bLength = other.Length();

	float cos = dot / (aLength * bLength);

	return acosf(cos);
}

Vector2 Vector2::NormalVector2()
{
	Vector2 temp;
	temp.x = this->x / Length();
	temp.y = this->y / Length();

	return temp;
}

void Vector2::Normalize()
{
	float length = Length();

	this->x = this->x / length;
	this->y = this->y / length;
}

