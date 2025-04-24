#include "vector.h"

#include "common.h"

Vector2::Vector2(double x, double y)
{
    using namespace std;

    this->x = x;
    this->y = y;

    mag = sqrt(pow(x, 2) + pow(y, 2));
}

double Vector2::getMagnitude()
{
    return mag;
}

Vector2 Vector2::normalize()
{
    return Vector2(x / mag, y / mag);
}

Vector2 Vector2::operator=(Vector2 b)
{
    x = b.x;
    y = b.y;
    return b;
}

bool Vector2::operator==(double const& b) const
{
    return x == b && y == b;
}

bool Vector2::operator!=(double const& b) const
{
    return x != b && y != b;
}

bool Vector2::operator>(double const& b) const
{
    return x > b && y > b;
}

bool Vector2::operator<(double const& b) const
{
    return x < b && y < b;
}

bool Vector2::operator>=(double const& b) const
{
    return x >= b && y >= b;
}

bool Vector2::operator<=(double const& b) const
{
    return x <= b && y <= b;
}

Vector2 Vector2::operator+(double b)
{
    return Vector2(x + b, y + b);
}

Vector2 Vector2::operator-(double b)
{
    return Vector2(x - b, y - b);
}

Vector2 Vector2::operator*(double b)
{
    return Vector2(x * b, y * b);
}

Vector2 Vector2::operator/(double b)
{
    return Vector2(x / b, y / b);
}

Vector2 Vector2::operator+=(double b)
{
    return Vector2(x + b, y + b);
}

Vector2 Vector2::operator-=(double b)
{
    return Vector2(x - b, y - b);
}

Vector2 Vector2::operator*=(double b)
{
    return Vector2(x * b, y * b);
}

Vector2 Vector2::operator/=(double b)
{
    return Vector2(x / b, y / b);
}

bool Vector2::operator==(Vector2 const& b) const
{
    return x == b.x && y == b.y;
}

bool Vector2::operator!=(Vector2 const& b) const
{
    return x != b.x && y != b.y;
}

bool Vector2::operator>(Vector2 const& b) const
{
    return x > b.x && y > b.y;
}

bool Vector2::operator<(Vector2 const& b) const
{
    return x < b.x && y < b.y;
}

bool Vector2::operator>=(Vector2 const& b) const
{
    return x >= b.x && y >= b.y;
}

bool Vector2::operator<=(Vector2 const& b) const
{
    return x <= b.x && y <= b.y;
}

Vector2 Vector2::operator+(Vector2 b)
{
    return Vector2(x + b.x, y + b.y);
}

Vector2 Vector2::operator-(Vector2 b)
{
    return Vector2(x - b.x, y - b.y);
}

Vector2 Vector2::operator*(Vector2 b)
{
    return Vector2(x * b.x, y * b.y);
}

Vector2 Vector2::operator/(Vector2 b)
{
    return Vector2(x / b.x, y / b.y);
}

Vector2 Vector2::operator+=(Vector2 b)
{
    return Vector2(x + b.x, y + b.y);
}

Vector2 Vector2::operator-=(Vector2 b)
{
    return Vector2(x - b.x, y - b.y);
}

Vector2 Vector2::operator*=(Vector2 b)
{
    return Vector2(x * b.x, y * b.y);
}

Vector2 Vector2::operator/=(Vector2 b)
{
    return Vector2(x / b.x, y / b.y);
}
