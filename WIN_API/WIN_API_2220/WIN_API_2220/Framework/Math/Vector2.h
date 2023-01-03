#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(int x, int y);
	~Vector2();

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const float& value) const;

	bool operator<(const Vector2& other) const;
	bool operator>(const Vector2& other) const;
	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	Vector2& operator+=(const Vector2& other);
	Vector2& operator=(const Vector2& other);

	Vector2& operator++();
	Vector2 operator++(int);

	float Length() const;
	float Manhattan(const Vector2& other) const;
	float Dot(const Vector2& other);
	float Cross(const Vector2& other);

	bool IsBetween(const Vector2& a, const Vector2& b);

	Vector2 NormalVector2();
	void Normalize();

public:
	float x;
	float y;
};

