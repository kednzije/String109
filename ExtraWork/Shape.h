#pragma once
class Shape
{
private:
	double m_w, m_h;
	double m_r;
public:
	Shape()
	{
		m_w = 1;
		m_h = 1;
		m_r = 1;
	}
	Shape(double w, double h, double r)
	{
		m_w = w;
		m_h = h;
		m_r = r;
	}
	void getArea()
	{
		return;
	}
	void getPerimeter()
	{
		return;
	}

};
class Circle : public Shape
{
private:
	double m_r;
public:
	Circle()
	{
		m_r = 1;
	}
	Circle(double r)
	{
		m_r = r;
	}
	void circle(double r)
	{
		m_r = r;
	}
	double GetArea()
	{
		return 3.14 * m_r * m_r;
	}
	double GetPerimeter()
	{
		return 3.14 * 2 * m_r;
	}
};
class Rectangle : public Shape
{
private:
    double m_w, m_h;
public:
    Rectangle()
    {
        m_w = 1;
        m_h = 1;
    }
    Rectangle(double w, double h)
    {
        m_w = w;
        m_h = h;
    }
    void rectangle(double w, double h)
    {
        m_w = w;
        m_h = h;
    }
    double getArea()
    {
        return m_w * m_h;
    }
    double getPerimeter()
    {
        return 2 * m_w + 2 * m_h;
    }
};