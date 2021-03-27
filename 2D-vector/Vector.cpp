#include "Vector.h"
#include <cmath>

#define EPSILON 1e-7
#define PI 3.14

Vector::Vector(void) {
    X = 0;
    Y = 0;
}

Vector::Vector(double x, double y) {
    X = x;
    Y = y;
}

Vector::Vector(const Vector &that) {
    X = that.X;
    Y = that.Y;
}

Vector &Vector::operator=(const Vector &that) = default;

Vector Vector::makePolar(double rad, double alpha) const {
    Vector polar_vector;
    polar_vector.X = rad * cos(alpha);
    polar_vector.Y = rad * sin(alpha);
    return polar_vector;
}

double Vector::x(void) const {
    return X;
}

double Vector::y(void) const {
    return Y;
}

void Vector::x(double newX) {
    X = newX;
}

void Vector::y(double newY) {
    Y = newY;
}

Vector Vector::operator+(const Vector &that) const {
    return Vector(X + that.X, Y + that.Y);
}

Vector Vector::operator-(const Vector &that) const {
    return Vector(X - that.X, Y - that.Y);
}

double Vector::operator*(const Vector &that) const {
    double result = this->X * that.X + this->Y * that.Y;
    return result;
}

Vector Vector::operator*(const double &that) const {
    return Vector(that * this->X, that * this->Y);
}

Vector Vector::operator/(const double &that) const {
    if (that == 0) {
        throw "Can not divide vector by a zero scalar";
    } else return Vector(X / that, Y / that);
}

Vector &Vector::operator+=(const Vector &that) {
    X = X + that.X;
    Y = Y + that.Y;
    return *this;
}

Vector &Vector::operator-=(const Vector &that) {
    X = X - that.X;
    Y = Y - that.Y;
    return *this;
}

Vector &Vector::operator*=(const double &that) {
    X = X * that;
    Y = Y * that;

    return *this;
}

Vector &Vector::operator/=(const double &that) {
    if (that == 0) {
        throw "Can not divide vector by a zero scalar";
    }
    X = X / that;
    Y = Y / that;
    return *this;
}

Vector Vector::operator-() {
    X = -X;
    Y = -Y;
    return *this;
}

bool Vector::operator==(const Vector &that) const {
    return (abs(X - that.X) <= EPSILON && abs(Y - that.Y) <= EPSILON);
}

bool Vector::operator!=(const Vector &that) const {
    if (this->operator==(that))
        return false;
    else return true;
}

Vector &Vector::rotate(double angle) {
    X = X * cos(angle) - Y * sin(angle);
    Y = Y * cos(angle) + X * sin(angle);
    return *this;
}

Vector &Vector::rotate(int quad) {
    X = X * cos(PI * quad / 2) - Y * sin(PI * quad / 2);
    Y = Y * cos(PI * quad / 2) + X * sin(PI * quad / 2);
    return *this;
}

double Vector::module2(void) const {
    double module2 = X * X + Y * Y;
    return module2;
}

double Vector::angle(void) const {
    if (X <= EPSILON) {
        return PI / 2;
    }
    double angle = atan2(Y, X);
    return angle;
}

double Vector::angle(const Vector &that) {
    double module_a = sqrt(X * X + Y * Y);
    double module_b = sqrt(that.X * that.X + that.Y * that.Y);
    if (module_a <= EPSILON || module_b <= EPSILON) {
        throw "Can not find the angle between Vector and Zero-Vector";
    }
    double scalar_product = X * that.X + Y * that.Y;
    double angle = acos(scalar_product / (module_a * module_b));
    return angle;
}

double Vector::projection(const Vector &base) const {
    double module_b = sqrt(base.X * base.X + base.Y * base.Y);
    double scalar_product = X * base.X + Y * base.Y;
    double projection = scalar_product / module_b;
    return projection;
}

Vector &Vector::normalize(void) {
    this->operator/=(sqrt(this->module2()));
    return *this;
}

Vector &Vector::transformTo(const Vector &e1, const Vector &e2) {
    X = e2.Y * X - e1.Y * Y;
    Y = -e2.X * X + e1.Y * Y;
    return *this;
}

Vector &Vector::transformFrom(const Vector &e1, const Vector &e2) {
    X = e1.X * X + e2.X * Y;
    Y = e1.Y * X + e2.Y * Y;
    return *this;
}

Vector operator*(const double &lhs, const Vector &rhs) {
    double x = lhs * rhs.x();
    double y = lhs * rhs.y();
    return Vector(x, y);
}

Vector rotate(const Vector &v, double angle) {
    double x = v.x() * cos(angle) - v.y() * sin(angle);
    double y = v.y() * cos(angle) + v.x() * sin(angle);
    return Vector(x, y);
}

Vector rotate(const Vector &v, int quad) {
    double x = v.x() * cos(PI * quad / 2) - v.y() * sin(PI * quad / 2);
    double y = v.y() * cos(PI * quad / 2) + v.x() * sin(PI * quad / 2);
    return Vector(x, y);
}

double module2(const Vector &v) {
    return v.module2();
}

double angle(const Vector &v) {
    return v.angle();
}

double angle(const Vector &v1, const Vector &v2) {
    double phi = v1.operator*(v2) / sqrt(v1.module2() * v2.module2());
    return phi;
}

double projection(const Vector &v, const Vector &base) {
    double projection = v.operator*(base) / sqrt(base.module2());
    return projection;
}

Vector normalize(const Vector &v) {
    return v.operator/(sqrt(v.module2()));
}

Vector transformTo(const Vector &v, const Vector &e1, const Vector &e2) {
    double x = e2.y() * v.x() - e1.y() * v.y();
    double y = -e2.x() * v.x() + e1.y() * v.y();
    return Vector(x, y);
}

Vector transformFrom(const Vector &v, const Vector &e1, const Vector &e2) {
    double x = e1.x() * v.x() + e2.x() * v.y();
    double y = e1.y() * v.x() + e2.y() * v.y();
    return Vector(x, y);
}