// VectorexecDLLref.cpp 
//клієнтський додаток, який використовує динамічну бібліотеку Vector3DDLL.dll
#include "..\Vector3DDL\Vector3DDLL.h" //макрос визначить клас як __declspec(dllimport)
#include <iostream>
#include <Windows.h> //для SetConsoleOutputCP та SetConsoleCP

int main()
{
	//для відображення і роботи з українськими символами в консолі
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::cout << " Використання ДИНАМІЧНОЇ бібліотеки Vector3DDLL " << std::endl;

	//створення векторів (викликаних з DLL)
	Vector3D vA(10.5, 5.0, 2.0); //конструктор з 3-ма параметрами
	Vector3D vB(2.5);            //конструктор explicit (x=0, y=0, z=2.5)
	Vector3D vC(vA);             //конструктор копіювання

	std::cout << "Вектор vA: " << vA.toString() << std::endl;
	std::cout << "Вектор vB: " << vB.toString() << std::endl;

	//демонстрація перевантажених операторів (викликаних з DLL)
	std::cout << "\n Математичні операції над векторами " << std::endl;
	std::cout << "A + B = " << (vA + vB).toString() << std::endl;
	std::cout << "A - C = " << (vA - vC).toString() << std::endl;
	std::cout << "B * 4 = " << (vB * 4.0).toString() << std::endl;

	//порівняння на рівність
	std::cout << "\n--- Порівняння ---" << std::endl;
	if (vA == vC) {
		std::cout << "Порівняння vA == vC: Вектори рівні (true)" << std::endl;
	}
	else {
		std::cout << "Порівняння vA == vC: Вектори не рівні (false)" << std::endl;
	}

	std::cout << "\nСкалярний добуток vA . vB = " << vA.dotProduct(vB) << std::endl;

	return 0;
}