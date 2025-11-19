//RightTriangle.h
#pragma once
#ifndef RIGHT_TRIANGLE_H
#define RIGHT_TRIANGLE_H

#include "Triangle.h" // Потрібно успадкувати клас Triangle

class RightTriangle : public Triangle {
public:

    RightTriangle(double side_a, double side_b, double side_c);

    //перевизначення isRight та printInfo
    bool isRight() const;
    void printInfo() const override;

    //методи для радіусів
    double calcInRad() const;
    double calcCircumRad() const;
};

#endif 