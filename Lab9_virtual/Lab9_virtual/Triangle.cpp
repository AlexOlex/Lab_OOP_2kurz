//Triangle.cpp
#include "Triangle.h"
#include <iostream>
#include <string>
#include <cmath> // для демонстрації rotAngle

//Реалізація деструктора з override
Triangle::~Triangle() {
    std::cout << " ~Triangle. Викликано деструктор Triangle .\n";
}

//Реалізація чистих віртуальних функцій з Shape (override)

//показує фігуру на екрані
void Triangle::show() const {
    std::cout << " Виклик Triangle::show. Трикутник " << (isVisible ? "видимий" : "невидимий") << " з параметрами: " << getInfo() << "\n";
}

//робить фігуру невидимою
void Triangle::hide() {
    isVisible = false;
    std::cout << " Виклик Triangle::hide. Зображення трикутника приховано.\n";
}

//повертає фігуру на заданий кут
void Triangle::rotate(double angleDegrees) {
    rotAngle += angleDegrees;
    // обмежуємо кут діапазоном [0, 360) для чистоти
    if (rotAngle >= 360.0 || rotAngle < 0.0) {
        rotAngle = fmod(rotAngle, 360.0);
    }
    std::cout << " Виклик Triangle::rotate. Трикутник повернуто на " << angleDegrees << "°. Новий кумулятивний кут: " << rotAngle << "°.\n";
}

//для пересунення фігури на наданий вектор
void Triangle::move(double dx, double dy) {
    centerX += dx;
    centerY += dy;
    std::cout << " ВикликTriangle::move. Трикутник переміщено на вектор (" << dx << ", " << dy << "). Новий центр: (" << centerX << ", " << centerY << ").\n";
}

//масштабний фактор
void Triangle::scale(double factor) {
    scaleFactor *= factor;
    sideLength *= factor; //масштабуємо також власне поле
    std::cout << " Виклик Triangle::scale. Трикутник відмасштабовано на " << factor << ". Новий коеф. масштабу: " << scaleFactor << ". Нова сторона: " << sideLength << ".\n";
}

//перевизначення getInfo (додає інформацію про сторону)
std::string Triangle::getInfo() const {
    //викликаємо getInfo() базового класу і додаємо інформацію про сторону
    return Shape::getInfo() + ", Довжина сторони: " + std::to_string(sideLength);
}