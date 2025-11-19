//Triangle.h
#pragma once
#include "Shape.h"


class Triangle : public Shape {
private:
    //додане власне поле для довжина сторони трикутника 
    double sideLength;

    //власне поле прапор видимості
    bool isVisible;

public:
    //конструктор викликає конструктор базового класу
    Triangle(double x, double y, double side)
        : Shape(x, y), sideLength(side), isVisible(true) {
    }

    //деструктор з override
    ~Triangle() override;


    //реалізація чистих віртуальних функцій (override)

    void show() const override;
    void hide() override;
    void rotate(double angleDegrees) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

    //перевизначення getInfo (з додаванням інформації про сторону)
    std::string getInfo() const override;


    //перевизначені геттери

    double getSideLength() const { return sideLength; }
};
