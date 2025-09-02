#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Базовый класс Figure
class Figure 
{
public:
    virtual void print_info() const 
    {
        std::cout << "Фигура:\n";
        std::cout << "Правильная: " << (check() ? "Да" : "Нет") << "\n";
        std::cout << "Количество сторон: 0\n";
    }

    virtual bool check() const 
    {
        return true;
    }
    virtual ~Figure() {}
};

// Базовый класс Triangle
class Triangle : public Figure
{
protected:
    double a, b, c; // Длины сторон
    double A, B, C; // Углы

public:
    Triangle(double a, double b, double c, double A, double B, double C)
        : a(a), b(b), c(c), A(A), B(B), C(C) {}

    void print_info() const override 
    {
        std::cout << "Треугольник:\n";
        std::cout << "Правильная: " << (check() ? "Да" : "Нет") << "\n";
        std::cout << "Количество сторон: 3\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << "\n";
    }

    bool check() const override 
    {
        return (A + B + C == 180) && (Figure::check());
    }
};

// Прямоугольный треугольник
class RightTriangle : public Triangle
{
public:
    RightTriangle(double a, double b)
        : Triangle(a, b, std::sqrt(a* a + b * b), 90.0, std::atan(b / a) * 180 / M_PI, 90.0) {}

    void print_info() const override 
    {
     std::cout << "Прямоугольный треугольник:\n";
     Triangle::print_info();
    }

    bool check() const override 
    {
        return (C == 90) && Triangle::check();
    }
};

// Равнобедренный треугольник
class IsoscelesTriangle : public Triangle 
{
public:
    IsoscelesTriangle(double a, double b)
        : Triangle(a, b, a, 50.0, 60.0, 50.0) {}

    void print_info() const override 
    {
        Triangle::print_info();
        std::cout << "Равнобедренный треугольник:\n";
    }

    bool check() const override 
    {
        return (a == c) && (A == C) && Triangle::check();
    }
};

// Равносторонний треугольник
class EquilateralTriangle : public Triangle 
{
public:
    EquilateralTriangle(double side)
        : Triangle(side, side, side, 60.0, 60.0, 60.0) {}

    void print_info() const override 
    {
        std::cout << "Равносторонний треугольник:\n";
    }

    bool check() const override 
    {
        return (a == b && b == c) && (A == B && B == C) && Triangle::check();
    }
};

// Базовый класс Quadrilateral
class Quadrilateral : public Figure 
{
protected:
    double a, b, c, d; // Длины сторон
    double A, B, C, D; // Углы

public:
    Quadrilateral(double a, double b, double c, double d, double A, double B, double C, double D)
        : a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {}

    void print_info() const override 
    {
        Figure::print_info();
        std::cout << "Четырёхугольник:\n";
        std::cout << "Правильная: " << (check() ? "Да" : "Нет") << "\n";
        std::cout << "Количество сторон: 4\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
    }

    bool check() const override 
    {
        return (A + B + C + D == 360) && Figure::check();
    }
};

// Прямоугольник
class RectangleOld : public Quadrilateral 
{
public:
    RectangleOld(double width, double height)
        : Quadrilateral(width, height, width, height, 90.0, 90.0, 90.0, 90.0) {}

    void print_info() const override 
    {
        Quadrilateral::print_info();
        std::cout << "Прямоугольник:\n";
    }
    bool check() const override
    {
        return (a == c && b == d) && (A == B && B == C && C == D) && Quadrilateral::check();
    }
};

// Квадрат
class Square : public RectangleOld
{
public:
    Square(double side)
        : RectangleOld(side, side) {}

    void print_info() const override
    {
        RectangleOld::print_info();
        std::cout << "Квадрат:\n";
    }

    bool check() const override
    {
        return (a == b && b == c && c == d) && (A == B && B == C && C == D) && RectangleOld::check();
    }
};

// Параллелограмм
class Parallelogram : public Quadrilateral
{
public:
    Parallelogram(double side1, double side2, double angleA, double angleB)
        : Quadrilateral(side1, side2, side1, side2, angleA, angleB, angleA, angleB) {}

    void print_info() const override
    {
        Quadrilateral::print_info();
        std::cout << "Параллелограмм:\n";
    }

    bool check() const override
    {
        return (a == c && b == d) && (A == C && B == D) && Quadrilateral::check();
    }
};

// Ромб
class Rhombus : public Parallelogram 
{
public:
    Rhombus(double sideLength)
        : Parallelogram(sideLength, sideLength, 30.0, 40.0) {}

    void print_info() const override 
    {
        Parallelogram::print_info();
        std::cout << "Ромб:\n";
    }

    bool check() const override 
    {
        return (a == b && a == c && a == d) && (A == C && B == D) && Parallelogram::check();
    }
};

void print_figure_info(const Figure* figure) 
{
    figure->print_info();
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Figure* figure[] =
    {
        new Figure(),
        new Triangle(10.0, 20.0, 30.0, 50.0, 60.0, 70.0),
        new RightTriangle(10.0, 20.0),
        new IsoscelesTriangle(10.0, 20.0),
        new EquilateralTriangle(30.0),
        new Quadrilateral(10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0),\
        new RectangleOld(10.0, 20.0),
        new Square(20.0),
        new Parallelogram(20.0, 30.0, 30.0, 40.0),
        new Rhombus(30.0)
    };

    for (Figure* figure : figure)
    {
        figure->print_info();
        std::cout << "\n";
    }
    for (Figure* figure : figure)
    {
        delete figure;
    }
    return 0;
}