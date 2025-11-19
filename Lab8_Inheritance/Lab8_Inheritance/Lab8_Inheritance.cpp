#include "Pair.h"
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <Windows.h> //для функцій SetConsoleOutputCP та SetConsoleCP


//Функція, що повертає об'єкт базового класу (може повертати об'єкт похідного)
//повертаємо unique_ptr для безпечного управління пам'яттю
std::unique_ptr<Pair> createPair(int type, int val1, int val2) {
	if (type == 2) {
		return std::make_unique<Pair>(val1, val2);
	}
	else {
		//повертаємо об'єкт Fraction, але як Pair*
		return std::make_unique<Fraction>(val1, val2);
	}
}


int main() {
	//для відображення і роботи з українськими символами в консолі
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	//об'єкти базового класу
	Pair p1(5, 7);
	Pair p2(11, 13);

	//об'єкти похідного класу
	Fraction f1(17, 19);
	Fraction f2(23, 29);
	Fraction f3(31, 29);


	//приймає та повертає об'єкти базового класу
	//принципу підстановки - передамо похідні класи як базові
	demoPolymorphismByCompare(&f1, &f2);


	std::cout << "Початкові пари: " << p1.toString() << ", " << p2.toString() << "\n";
	std::cout << "Початкові дроби: " << f1.toString() << ", " << f2.toString() << ", " << f3.toString() << "\n";


	//Демонстрація принципу підстановки (LSP)
	std::cout << "\n Демонстрація LSP \n";

	//порівняння двох об'єктів Pair
	std::cout << "Порівняння Pair (5, 7) і Pair (11, 13): \n";
	demoPolymorphismByCompare(&p1, &p2);

	//порівняння двох об'єктів Fraction (використовуючи Pair*)
	std::cout << "Порівняння Fraction (17/19) і Fraction (23/29): \n";
	demoPolymorphismByCompare(&f1, &f2);

	//порівняння двох рівних Fraction
	std::cout << "Порівняння Fraction (17/19) і Fraction (31/29): \n";
	demoPolymorphismByCompare(&f1, &f3);

	//порівняння Pair і Fraction
	std::cout << "Порівняння Pair (5, 7) і Fraction (17/19): \n";
	demoPolymorphismByCompare(&p1, &f1);



	//демонстрація функції, що повертає базовий клас
	std::unique_ptr<Pair> resultPair = createPair(2, 37, 41);
	std::unique_ptr<Pair> resultFraction = createPair(3, 5, 7); // Повертає Fraction як Pair*

	std::cout << "\n Демонстрація повернення базового класу \n";
	std::cout << "створено Pair  " << resultPair->toString() << "\n";
	std::cout << "створено Fraction (як Pair*)  " << resultFraction->toString() << "\n"; // Викликається Fraction::toString


	//демонстрація інших операторів Fraction
	std::cout << "\n Додаткові оператори Fraction \n";
	std::cout << f1.toString() << " >= " << f3.toString() << ": " << (f1 >= f3 ? "True" : "False") << "\n";
	std::cout << f1.toString() << " != " << f2.toString() << ": " << (f1 != f2 ? "True" : "False") << "\n";


	//демонстрація обробки винятків (запобігання діленню на нуль)
	std::cout << "\n Демонстрація Обробки Винятків \n";
	try {
		Fraction f_test(43, 47); // Прості числа, наступні
		std::cout << "спроба встановити знаменник 0 для дробу " << f_test.toString() << "\n";
		f_test.setDenominator(0); // Цей виклик має викинути виняток
		std::cout << "Цей рядок не має бути виведений.\n";
	}
	catch (const std::invalid_argument& e) {
		std::cout << "перехоплено виняток: " << e.what() << "\n";
	}
	catch (...) {
		std::cout << "перехоплено невідомий виняток.\n";
	}

	return 0;
}