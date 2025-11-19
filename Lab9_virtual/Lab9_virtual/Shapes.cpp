//Shapes.cpp
#include "Shape.h"
#include <string>
#include <iostream>

//реалізація віртуальної функції getInfo, оголошеної в Shape.h
//ця реалізація є базовою і може бути перевизначена
std::string Shape::getInfo() const {
	//використовуємо поля базового класу
	return " \n Центр: (" + std::to_string(centerX) + ", " + std::to_string(centerY) +
		"), \n Кут: " + std::to_string(rotAngle) + "°, \n Масштаб: " + std::to_string(scaleFactor);
}