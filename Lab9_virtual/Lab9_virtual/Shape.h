//Shape.h
#pragma once
#include <iostream>
#include <string>


class Shape {
protected:
    //поля
    double centerX;
    double centerY;
    double rotAngle;
    double scaleFactor;     //коефіцієнт маштабування;  

public:
    Shape(double x, double y)
        : centerX(x), centerY(y), rotAngle(0.0), scaleFactor(1.0) {
    }//початковий кумулятивний коефіцієнт масштабування = 1.0 

//віртуальний деструктор (!обов'язково для поліморфних базових класів)
    virtual ~Shape() = default;



    ///////////////////////////////////////////////////////////////////////////////////////
    //ІНТЕРФЕЙС (віртуальні функції, похідні класи повинні їх реалізувати

    //функція з =0 це чиста віртуальна функція, робить клас абстрактним, тобто 
    //не можна створит об'єкт цього класу, а похідні класи повинні мати 
    //конкретну реалізацію цих функцій (поліморфізм)

    //показує фігуру на екрані
    virtual void show() const = 0; //= 0 - це чиста віртуальна функція, робить клас абстрактним

    //робить фігуру невидимою (знищує її зображення)
    virtual void hide() = 0;

    //повертає фігуру на заданий кут(кут надається у градусах)
    virtual void rotate(double angleDegrees) = 0;

    //для пересунення фігури на наданий вектор
    virtual void move(double dx, double dy) = 0;

    //масштабний фактор (для обробки зміни масштабу фігури)
    virtual void scale(double factor) = 0;

    //віртуальна функція для отримання даних про об'єкт ;
    //має реалізацією за замовчуванням, яка можлива оскільки 
    //базовий Shape знає про свої координати, кут та масштаб ;
    //virtual дозволяє похідному Triangle перевизначити функцію (але не примушкє)
    virtual std::string getInfo() const;

    ////////////////////////////////////////////////////////////////////////////////////////
    //геттери

    double getX() const { return centerX; }

    double getY() const { return centerY; }

    double getAngle() const { return rotAngle; }

    double getScale() const { return scaleFactor; }
};

