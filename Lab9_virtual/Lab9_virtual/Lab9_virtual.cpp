//Lab9_virtual.cpp
#include "Triangle.h"
#include <typeinfo> //для typeid
#include <iostream>
#include <stdexcept>
#include <Windows.h> //для функцій SetConsoleOutputCP та SetConsoleCP


void demoShapePolymorphism(Shape* shape) {
    //хоча shape має статичний тип Shape*, віртуальні функції
    //завжди викликають реалізацію похідного класу (Triangle).


    std::cout << " Поліморфний виклик об'єкту " << typeid(*shape).name() << " через Shape*\n";


    //Виклики перевизначених методів:

    std::cout << " Початкові значення полів:\n";
    shape->show(); //виклик Triangle::show


    std::cout << "\n Переміщення:\n";
    shape->move(10.5, -5.0); //виклик Triangle::move


    std::cout << "\n Поворот:\n";
    shape->rotate(90.0); //виклик Triangle::rotate


    std::cout << "\n Масштабування:\n";
    shape->scale(1.5); //виклик Triangle::scale


    std::cout << "\n Фінальний стан:\n";
    shape->show(); //виклик Triangle::show


    std::cout << "\n Знищення зображення:\n";
    shape->hide(); //виклик Triangle::hide


    shape->show(); //покаже параметри вже невидимого об'єкта
}


int main() {

    //для відображення і роботи з українськими символами в консолі
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    try {
        Triangle myTriangle(11.0, 13.0, 17.0);

        std::cout << " Створено об'єкт  Triangle з параметрами: " << myTriangle.getInfo() << "\n";

        //демонстрація поліморфізму
        //покажчик myTriangle (Triangle*) переданий до функції, що очікує базовий Shape*
        demoShapePolymorphism(&myTriangle);

        //перевірка фінальних параметрів об'єкта після перетворень
        std::cout << " Після перетворень myTriangle параметри змінились на \n" << myTriangle.getInfo() << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "\nПомилка часу виконання: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
