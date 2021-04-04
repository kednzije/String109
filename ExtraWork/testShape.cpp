#include<iostream>
using namespace std;
#include"Shape.h"

int main()
{
	int r = 3;
	int w = 5, h = 8;
	Circle circle(r);
	Rectangle rectangle(w, h);
	cout << "圆的面积为："<< circle.GetArea() << endl
		<< "圆的周长为：" << circle.GetPerimeter() << endl
		<< "矩形的面积为：" << rectangle.getArea() << endl
		<< "矩形的周长为：" << rectangle.getPerimeter() << endl;

}