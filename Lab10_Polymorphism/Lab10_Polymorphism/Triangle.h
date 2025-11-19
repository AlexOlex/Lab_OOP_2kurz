//Triangle.h
#pragma once
#include <iostream> 
#include <cmath>
#include <algorithm>
#include <numeric> 
#include <vector>
#include <stdexcept> 

//координати точки
struct Point
{
    double x, y; // поля публічні за замовчуванням
};

//константа для коретного порівняня double
const double EPSILON = 1e-9;


// ця пуста структура буде тегом - 4ым параметром в конструкторы 
// для Tag Dispatching, щоб уникнути конфлікту конструкторів з однаковою кількістю параметрів.
struct InitByMedians {}; // <-- ВИПРАВЛЕНО: Винесено з класу

class Triangle {
protected: //модифікотор робить поля доступні похідним класам
    double a, b, c; //поля для довжин сторін

    //функція для перевірки чи існує трикутник
    bool checkTriangleInequality() const;

public:
    //дефолтний конструктор
    Triangle();

    //конструктор з трьома параметрами (довжини сторон трикутника)
    Triangle(double side_a, double side_b, double side_c);

    //конструктор з трьома параметрами (основи трьох медіан ma, mb, mc - пункт 2 завдання)
    Triangle(double ma, double mb, double mc, InitByMedians tag); // Тег використовується тут

    //віртуальний деструктор
    virtual ~Triangle() = default;

    //методи для поліморфних викликів, пункт 1 завдання (абстрактний клас з двома реалізаціми)    
    virtual double getArea() const;
    virtual void printInfo() const;

    //методи для додаткових обчислень
    double getPerimeter() const;
    double calcMedian(char side) const;
    double calculateMidline(char side) const;
};


//////////////////////////////////////////////////////////////////////////////////////////////

class TriangleByVertices : public Triangle
{
private:
    Point v1, v2, v3; //координат вершин.
    void calcSides(); //обчислення сторін

public:
    TriangleByVertices(const Point& p1, const Point& p2, const Point& p3);

    double getArea() const override;
    void printInfo() const override;
};

//похідний клас прямокутний трикутник з реалізацією 
//функції обчислення довжин радіусів вписаного і описаного кіл



//////////////////////////////////////////////////////////////////////////////////////////////

class RightTriangle : public Triangle
{
public:

    //перевірка на прямокутність
    bool isRight() const;

    RightTriangle(double side_a, double side_b, double side_c);

    //обчислення радіуса вписаного кола 
    double calcInRad() const;

    //обчислення радіуса описаного кола 
    double calcCircumRad() const;

    //перевизначення 
    void printInfo() const override;
};