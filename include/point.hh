#ifndef POINT_H_
#define POINT_H_

class point {
   private:
    float x_, y_;

   public:
    point();
    point(float x, float y);
    ~point();

    // point &operator=(point &p);
    // point operator=(point p);
    // point &operator+=(point &p);
    // point &operator-=(point &p);
    // point &operator*=(point &p);
    // point &operator/=(point &p);

    point operator+(point p);
    point operator-(point p);
    point operator*(point p);
    point operator/(point p);

    bool operator==(point p);
    bool operator!=(point p);

    float x() {
        return x_;
    };
    float y() {
        return y_;
    };

    void move(point p);

    float distance(point p);
    float distance(float x, float y);
    float magnitude();

    void print();
};

#endif
