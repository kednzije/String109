#include<iostream>

class Point {
    public:
        double x, y;
        Point(double _x, double _y);
};

class Circle {
    private:
        Point center;
        double radius;
    public:
        Circle(double x, double y, double r);
        void Display();
};