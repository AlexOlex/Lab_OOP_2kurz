#include "Vector3D.h"
#include <iostream>
#include <Windows.h> //для SetConsoleOutputCP та SetConsoleCP

int main()
{
    //для відображення і роботи з українськими символами в консолі
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::cout << "ЗАВДАННЯ 3 Варіант 2: Конструктори" << std::endl;

    //виклики КОНСТРУКТОРІВ 
    std::cout << "Демонстрація конструкторів: " << std::endl;

    //виклик дефолтного конструктора без аргумента
    //поля x, y, z не мають DMI (полям в хедері нічого не присвоєно), тому значення 
    //спочатку неініціалізовані (містять сміття)
    //Init() задає початкові значення після створення
    Vector3D v1;
    v1.Init(8.04, 1.5, 14.2); // для перевірки Init
    std::cout << "v1 (дефолтний + Init): " << v1.toString() << std::endl;

    //виклик конструктора з одним параметром z (explicit)
    //x і y за замовчуванням встановлюються у 0.0 у конструкторі, а  z явно в = 11.5
    Vector3D v2(11.5);
    std::cout << "v2 (explicit конструктор з х і у за замовченням = 0,  z задано): " << v2.toString() << std::endl;


    //виклик статичного методу для вектора з однаковими координатами
    //створюється тимчасовий (живе лише в тілі метода) Vector3D з заданим значенням (одне для кожноої координати) і присвоюється v3
    Vector3D v3 = Vector3D::Vec3DEqualCoords(4.0);
    std::cout << "v3 (однакові координати через статичний метод): " << v3.toString() << std::endl;


    //виклик конструктора з трьома аргументами (список ініціалізації у конструкторі) 
    //у конструктор передаються значення x, y, z, і вони встановлюються через Init()
    Vector3D v4(1.7, 12.7, 25.27);
    std::cout << "v4 (конструктор з трьома параметрами): " << v4.toString() << std::endl;

   
    //демонстраціяпріоритету ініціалізації (виклик Vector3D(bool demo) ):
    //виклик дефолтного конструктора Vector3D(): x(2.0), y(5.0) і присвоєнням в тілі  z = 10.0;
    //доданий параметр true дозволить компілятору відрізнити виклик від Vector3D v1;  v1.Init(8.04, 1.5, 14.2);
    Vector3D demoVec(true); //у консолі повинен вивести координати  x=2 y=5 z=10
  



 
  
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