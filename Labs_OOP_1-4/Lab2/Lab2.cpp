#include "Vector3D.h"
#include <iostream>
#include <Windows.h> //для SetConsoleOutputCP та SetConsoleCP

int main()
{
    //для відображення і роботи з українськими символами в консолі
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::cout << "ЗАВДАННЯ 2 Варіант 2: Клас Vector3D" << std::endl;
   
    Vector3D v1;
    v1.Init(1.0, 2.0, 3.0);

    Vector3D v2;
    std::cout << "Введення координат для вектора V2:" << std::endl;
    v2.Read();

    std::cout << "\nВектор v1: " << v1.toString() << std::endl;
    std::cout << "Вектор v2: ";
    v2.Display(); 

   
    double len1 = v1.lengthVec3D();
    double len2 = v2.lengthVec3D();

    std::cout << "Довжина v1: " << len1 << std::endl;
    std::cout << "Довжина v2: " << len2 << std::endl;

    //порівняняння векторів з перевантаженим оператором порівняння
    if (v1 < v2) {
        std::cout << "При порівнянні довжин отримали |v1| < |v2| " << std::endl;
    }
    else {
        std::cout << "При порівняння довжин отримали  |v1| >= |v2| " << std::endl;
    }

  
    Vector3D v_sum = v1.addVec3D(v2);
    std::cout << "V1 + V2 = " << v_sum.toString() << std::endl;

    Vector3D v_diff = v1.subVec3D(v2);
    std::cout << "V1 - V2 = " << v_diff.toString() << std::endl;

   
    double scalar = 5.0;
    Vector3D v_mult = v2.multVec3DScalar(scalar);
    std::cout << "V2 * " << scalar << " = " << v_mult.toString() << std::endl;

    double dot = v1.dotProduct(v2);
    std::cout << "Скалярний добуток V1 . V2 = " << dot << std::endl;

   
    if (v1.equalsVec3D(v2)) {
        std::cout << "Порівняння векторів: V1 == V2 (true)" << std::endl;
    }
    else {
        std::cout << "Порівняння векторів: V1 == V2 (false)" << std::endl;
    }


    return 0;
}