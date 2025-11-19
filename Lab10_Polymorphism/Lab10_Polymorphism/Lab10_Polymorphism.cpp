//Lab10_Polymorphism.cpp
#include "Triangle.h"
#include <vector>
#include <Windows.h> //для функцій SetConsoleOutputCP та SetConsoleCP

int main() {
    std::cout << "ЗАВДВННЯ 10 Варіант 2 Поліморфізм" << std::endl;

    //для відображення і роботи з українськими символами в консолі
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);


    //вектора покажчиків на базовий клас; зберігає покажчики на об'єкти різних
    //типів (TriangleByVertices, RightTriangle); звертається до всіх  як до Triangle (поліморфізм)

    //методи, які будуть використовуватися для std::vector:
    //push_back() - для додавання у vector нових об'єктів (!через new) 
    //for (const auto* t : triangles) 
    //delete - для явного очищення пам'яті 

    std::vector<Triangle*> triangles;

    try {
        //cтворення об'єктів різних типів

        Point p1 = { 2, 3 };
        Point p2 = { 5, 7 };
        Point p3 = { 2, 7 };
        triangles.push_back(new TriangleByVertices(p1, p2, p3)); //похідний

        //11 + 13 > 17
        triangles.push_back(new Triangle(11.0, 13.0, 17.0)); //базовий

        //з координатами(5.0, 12.0, 13.0) трикутник - існує, (11.0, 13.0, 17.0) - не існує
        triangles.push_back(new RightTriangle(5.0, 12.0, 13.0)); //похідний  


        std::cout << "\n\n Трикутник за медіанами " << std::endl;
        Triangle median_triangle(11, 13, 17, InitByMedians{});
        median_triangle.printInfo();

        //очікується вихідне значення ma
        std::cout << "   Медіана до сторони a  = " << median_triangle.calcMedian('a') << std::endl;

        //методу обчислення середньої лінії, очікується c / 2.0
        std::cout << "   Середньої лінії, що паралельна стороні c = " << median_triangle.calculateMidline('c') << std::endl;


    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "невірний аргумент, помилка ініціалізації: " << e.what() << std::endl;
    }


    //tri->printInfo() та tri->getArea() звертаються до перевизначеної реалізації в похідному класі
    //завдяки віртуальним функціям та таблиці віртуальних функцій vtable;
    //vtable стврюється одна на клас при компіляціі,зберігає покажчики на конкретні реалізації віртуальних
    //функцій; порядок функцій (тобто адрес) у vtable строго фіксований і однаковий для всіх класів ієрархії;
    //при створенні будь-якого об'єкта до нього додається прихований віртуальний покажчик vptr, який завжди
    //вказує на першу адресу vtable свого типу(з яким створений);
    //при виклику віртуальна функція через покажчик базового типу (напр t->printInfo()) використовується 
    //vptr об'єкта, на який вказує t (тобто vtable класу RightTriangle чи vtable класу TriangleByVertices); 
    //цей vptr знаходить потрібну vtable і в ній адресу функції, тобто вибираєметоду під час виконання (динамічне зв'язування)

    int count = 1;
    //цикл по покажчиках базового класу Triangle*
    for (const auto* t : triangles)
    {
        std::cout << "\nоб'єкт " << count++ << " типу  " << (dynamic_cast<const RightTriangle*>(t) ? "RightTriangle" : (dynamic_cast<const TriangleByVertices*>(t) ? "TriangleByVertices" : "Triangle")) << std::endl;

        t->printInfo();

        //спільних методи
        try {
            std::cout << "   довжина медіани до сторони b =  " << t->calcMedian('b') << std::endl;
            std::cout << "   довжина середньої лінії, що паралельна стороні a = " << t->calculateMidline('a') << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << " !Помилка обчислення " << e.what() << std::endl;
        }


    }

    //очищення пам'ті - видалення об'єктів, створених через new
    //виклик коректного деструктора похідного класу (у  базовому класівіртуальнийдеструктор)
    std::cout << "\nОчищення пам'яті " << std::endl;
    for (Triangle* t : triangles) {
        delete t;
    }

    return 0;
}