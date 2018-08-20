#include <cstdio>

#include <cmath>

#include <point.hh>

point::point() : x_(0.0), y_(0.0) {
}
point::point(float x, float y) : x_(x), y_(y) {
}
point::~point() {
}

// point &point::operator=(point &p) {
//     return p;
// }
// point point::operator=(point p) {
//     return p;
// }
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
    if (fabs(x_ - p.x()) <= __FLT_EPSILON__ &&
        fabs(y_ - p.y()) <= __FLT_EPSILON__)
        return true;
    else
        return false;
}
bool point::operator!=(point p) {
    if (fabs(x_ - p.x()) >= __FLT_EPSILON__ ||
        fabs(y_ - p.y()) >= __FLT_EPSILON__)
        return true;
    else
        return false;
}

void point::move(point p) {
    x_ += p.x();
    y_ += p.y();
}

float point::distance(point p) {
    return sqrt(pow(x_ - p.x(), 2) + pow(y_ - p.y(), 2));
}

float point::distance(float x, float y) {
    return sqrt(pow(x_ + x, 2) + pow(y_ - y, 2));
}

float point::magnitude() {
    return   sqrt(pow(x_, 2) + pow(y_, 2));
}

void point::print() {
    printf("x=%.2f y=%.2f\n", x_, y_);
}
