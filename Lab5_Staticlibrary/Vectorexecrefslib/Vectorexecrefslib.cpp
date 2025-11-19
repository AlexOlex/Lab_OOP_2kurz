// Vectorexecrefslib.cpp 
//клієнтський додаток, який використовує статичну бібліотеку Vector3DLib.lib
#include "Vector3DLib.h"
#include <iostream>
#include <Windows.h> // для SetConsoleOutputCP та SetConsoleCP

int main()
{
	//для відображення і роботи з українськими символами в консолі
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::cout << " використання СТАТИЧНОЇ бібліотеки Vector3D " << std::endl;

	//створення векторів за допомогою конструкторів (викликаних з бібліотеки)
	Vector3D vA(10.5, 5.0, 2.0); //конструктор з 3-ма параметрами
	Vector3D vB(2.5);            //конструктор explicit (x=0, y=0, z=2.5)
	Vector3D vC(vA);             //конструктор копіювання
	Vector3D vD;                 //дефолтний конструктор (0, 0, 0)

	std::cout << "Вектор vA: " << vA.toString() << std::endl;
	std::cout << "Вектор vB: " << vB.toString() << std::endl;

	//демонстрація перевантажених операторів (викликаних з бібліотеки)
	std::cout << "\n Математичні операції над векторами " << std::endl;
	std::cout << "vA + vB = " << (vA + vB).toString() << std::endl;
	std::cout << "vA - vC = " << (vA - vC).toString() << std::endl;
	std::cout << "vB * 17 = " << (vB * 17.0).toString() << std::endl;

	//порівняння довжин
	std::cout << "\n Порівняння " << std::endl;
	if (vA < vB) {
		std::cout << "порівняння довжин: |A| < |B| (Хиба)" << std::endl;
	}
	else {
		std::cout << "порівняння довжин: |A| >= |B| (Істина)" << std::endl;
	}

	//порівняння на рівність за допомогою оператора
	if (vA == vC) {
		std::cout << "порівняння A == C: Вектори рівні (Істина)" << std::endl;
	}
	else {
		std::cout << "порівняння A == C: Вектори не рівні (Хиба)" << std::endl;
	}

	//використання equalsVec3D, що викликає оператор==
	if (vA.equalsVec3D(vC)) {
		std::cout << "виклик equalsVec3D(vC) з оператор==:  вектори є рівні" << std::endl;
	}

	std::cout << "\nскалярний добуток vA . vB = " << vA.dotProduct(vB) << std::endl;

	return 0;
}