#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

class Vector2
{
private:
    double mag; // magnitude is another way of saying "length"

public:
    Vector2() {}
    Vector2(double x, double y);
    virtual ~Vector2() {}

    double x, y; // for ease of access

    double getMagnitude();

    Vector2 normalize();

    Vector2 operator=(Vector2 b);

    bool operator==(double const& b) const;
    bool operator!=(double const& b) const;
    bool operator>(double const& b) const;
    bool operator<(double const& b) const;
    bool operator>=(double const& b) const;
    bool operator<=(double const& b) const;
    Vector2 operator+(double b);
    Vector2 operator-(double b);
    Vector2 operator/(double b);
    Vector2 operator*(double b);
    Vector2 operator+=(double b);
    Vector2 operator-=(double b);
    Vector2 operator*=(double b);
    Vector2 operator/=(double b);

    bool operator==(Vector2 const& b) const;
    bool operator!=(Vector2 const& b) const;
    bool operator>(Vector2 const& b) const;
    bool operator<(Vector2 const& b) const;
    bool operator>=(Vector2 const& b) const;
    bool operator<=(Vector2 const& b) const;
    Vector2 operator+(Vector2 b);
    Vector2 operator-(Vector2 b);
    Vector2 operator/(Vector2 b);
    Vector2 operator*(Vector2 b);
    Vector2 operator+=(Vector2 b);
    Vector2 operator-=(Vector2 b);
    Vector2 operator*=(Vector2 b);
    Vector2 operator/=(Vector2 b);

    static double GetDistance(Vector2 a, Vector2 b);
};

#endif // VECTOR_H_INCLUDED
