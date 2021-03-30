#include "Define.h"
#include <iostream>

Point::Point(double _x, double _y) {
    x = _x, y = _y;
}

Circle::Circle(double x, double y, double r) {
    center = Point(x, y);
    radius = r;
}
void Circle::Display() {
    std::cout << "This circle is in " << '(' << center.x << ',' << center.y << ')' << std::endl;
    std::cout << "This circle's area is" << 3.14 * radius * radius << std::endl;
}