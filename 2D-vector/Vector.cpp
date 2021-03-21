#include "Vector.h"
#include <cmath>

Vector::Vector(void) {
    X = 0;
    Y = 0;
    Rad = 0;
    Alpha = 0;
}

Vector::Vector(double x, double y) {
    X = x;
    Y = y;
    //////
    Rad = sqrt(X * X + Y * Y);

    Alpha = acos(X / Rad);
}

Vector::Vector(const Vector &that) {
    X = that.X;
    Y = that.Y;
    //////
    Rad = that.Rad;
    Alpha = that.Alpha;
}

Vector &Vector::operator=(const Vector &that) = default;

Vector Vector::makePolar(double rad, double alpha) const {
    Vector polar_vector;
    polar_vector.Rad = rad;
    polar_vector.Alpha = alpha;
    //////
    polar_vector.X = Rad * cos(alpha);
    polar_vector.Y = Rad * sin(alpha);
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
    //////
    Rad = sqrt(X * X + Y * Y);
    Alpha = acos(X / Rad);
}

void Vector::y(double newY) {
    Y = newY;
    //////
    Rad = sqrt(X * X + Y * Y);
    Alpha = acos(X / Rad);
}

Vector Vector::operator+(const Vector &that) const {
    Vector result;
    result.X = this->X + that.X;
    result.Y = this->Y + that.Y;
    //////
    result.Rad = sqrt(result.X * result.X + result.Y * result.Y);
    result.Alpha = acos(result.X / Rad);
    return result;
}

Vector Vector::operator-(const Vector &that) const {
    Vector result;
    result.X = this->X - that.X;
    result.Y = this->Y - that.Y;
    //////
    result.Rad = sqrt(result.X * result.X + result.Y * result.Y);
    result.Alpha = acos(result.X / Rad);
    return result;
}

double Vector::operator*(const Vector &that) const {
    double result = this->X * that.X + this->Y * that.Y;
    return result;

}

Vector Vector::operator*(const double &that) const {
    Vector result;
    result.X = that * this->X;
    result.Y = that * this->Y;
    //////
    result.Rad = sqrt(result.X * result.X + result.Y * result.Y);
    result.Alpha = acos(result.X / Rad);
    return result;
}

Vector Vector::operator/(const double &that) const {
    Vector result;
    result.X = that / this->X;
    result.Y = that / this->Y;
    //////
    result.Rad = sqrt(result.X * result.X + result.Y * result.Y);
    result.Alpha = acos(result.X / Rad);
    return result;
}

Vector &Vector::operator+=(const Vector &that) {
    X = X + that.X;
    Y = Y + that.Y;
    //////
    Rad = sqrt(X * X + Y * Y);
    Alpha = acos(X / Rad);
    return *this;
}

Vector &Vector::operator-=(const Vector &that) {
    X = X - that.X;
    Y = Y - that.Y;
    //////
    Rad = sqrt(X * X + Y * Y);
    Alpha = acos(X / Rad);
    return *this;
}

Vector &Vector::operator*=(const double &that) {
    X = X * that;
    Y = Y * that;
    //////
    Rad = sqrt(X * X + Y * Y);
    Alpha = acos(X / Rad);
    return *this;
}

Vector &Vector::operator/=(const double &that) {
    X = X / that;
    Y = Y / that;
    //////
    Rad = sqrt(X * X + Y * Y);
    Alpha = acos(X / Rad);
    return *this;
}

Vector Vector::operator-() {
    X = -X;
    Y = -Y;
    //////
    Alpha = acos(X / Rad);
    return *this;
}

bool Vector::operator==(const Vector &that) const {
    if (X == that.X && Y == that.Y)
        return true;
    else return false;
}

bool Vector::operator!=(const Vector &that) const {
    if (X != that.X || Y != that.Y)
        return true;
    else return false;
}

Vector &Vector::rotate(double angle) {
    X = X * cos(angle) - Y * sin(angle);
    Y = Y * cos(angle) + X * sin(angle);
    //////
    Rad = sqrt(X * X + Y * Y);
    Alpha = acos(X / Rad);
    return *this;
}

Vector &Vector::rotate(int quad) {
    X = X * cos(3.14 * quad / 2) - Y * sin(3.14 * quad / 2);
    Y = Y * cos(3.14 * quad / 2) + X * sin(3.14 * quad / 2);
    //////
    Rad = sqrt(X * X + Y * Y);
    Alpha = acos(X / Rad);
    return *this;
}

double Vector::module2(void) const {
    double module2 = X * X + Y * Y;
    return module2;
}

double Vector::angle(void) const {
///    double angle = atan(Y / X);
///    return angle;
    return Alpha;
}

double Vector::angle(const Vector &that) {
    double module_a = sqrt(X * X + Y * Y);
    double module_b = sqrt(that.X * that.X + that.Y * that.Y);
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
    X = X / sqrt(X * X + Y * Y);
    Y = Y / sqrt(X * X + Y * Y);
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
//    X = X * cos(3.14 * quad / 2) - Y * sin(3.14 * quad / 2);
//    Y = Y * cos(3.14 * quad / 2) + X * sin(3.14 * quad / 2);
    double x = v.x() * cos(3.14 * quad / 2) - v.y() * sin(3.14 * quad / 2);
    double y = v.y() * cos(3.14 * quad / 2) + v.x() * sin(3.14 * quad / 2);
    return Vector(x, y);
}

double module2(const Vector &v) {

}

double angle(const Vector &v);

double angle(const Vector &v1, const Vector &v2);

double projection(const Vector &v, const Vector &base);

Vector normalize(const Vector &v);

Vector transformTo(const Vector &v, const Vector &e1, const Vector &e2);

Vector transformFrom(const Vector &v, const Vector &e1, const Vector &e2);