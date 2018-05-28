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

    double distance(point p);
    double distance(float x, float y);

    void print();
};

#endif
