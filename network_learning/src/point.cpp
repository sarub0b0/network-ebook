#include <cstdio>

#include <math.h>

#include <point.hpp>

point &point::operator=(point &p) {
    return p;
}

point point::operator+(point p) {
    return point(x_ + p.x(), y_ + p.y());
}

point point::operator-(point p) {
    return point(x_ - p.x(), y_ - p.y());
}

point point::operator*(point p) {
    return point(x_ * p.x(), y_ * p.y());
}

point point::operator/(point p) {
    return point(x_ / p.x(), y_ / p.y());
}

bool point::operator==(point p) {
    if (x_ == p.x() && y_ == p.y())
        return true;
    else
        return false;
}
bool point::operator!=(point p) {
    if (x_ != p.x() || y_ != p.y())
        return true;
    else
        return false;
}

void point::move(point p) {
    x_ += p.x();
    y_ += p.y();
}

double point::distance(point p) {
    return sqrt(pow(x_ - p.x(), 2) + pow(y_ - p.y(), 2));
}

double point::distance(float x, float y) {
    return sqrt(pow(x_ + x, 2) + pow(y_ - y, 2));
}

void point::print() {
    fprintf(stderr, "x:%.2f y:%.2f\n", x_, y_);
}
