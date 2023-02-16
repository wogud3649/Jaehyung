#include "Framework.h"

Vector2::Vector2()
: x(0)
, y(0)
{
}

Vector2::Vector2(float x, float y)
: x(x)
, y(y)
{
}

Vector2::~Vector2()
{
}

void Vector2::PrintVector2()
{
	cout << "x의 좌표 : " << x << endl;
	cout << "y의 좌표 : " << y << endl;
}

Vector2 Vector2::operator+(const Vector2& other) const // 내부에서 x와 y를 변경하지 않겠다.
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
	return this->Length() < other.Length();
}

bool Vector2::operator>(const Vector2& other) const
{
	return this->Length() > other.Length();
}

bool Vector2::operator==(const Vector2& other) const
{
	return (this->x == other.x && this->y == other.y);
}

//bool Vector2::operator!=(const Vector2& other) const
//{
//	return (this->x != other.x || this->y != other.y);
//}
bool Vector2::operator!=(const Vector2& other) const
{
	return !(this->x == other.x && this->y == other.y);
}

//float Vector2::Cross(const Vector2& other) const
//{
//	//TODO
//}
//
//Vector2 Vector2::Normal()
//{
//	//TODO
//}

Vector2& Vector2::operator=(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;

	return (*this);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	//TODO
}

Vector2& Vector2::operator++()
{
	++x;
	++y;

	return (*this);
}

Vector2& Vector2::operator++(int)
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