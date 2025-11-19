//Vector3DDLL.cpp
//реалізація динамічної бібліотеки. У властивостях проекту має бути визначено: VECTOR3D_EXPORTS
#include "Vector3DDLL.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>
#include <iomanip>

// КОНСТРУКТОРИ
Vector3D::Vector3D() : x(0.0), y(0.0), z(0.0) {}

Vector3D::Vector3D(double x, double y, double z)
{
	// Викликаємо Init для перевірки даних
	Init(x, y, z);
}

Vector3D::Vector3D(double z) : x(0.0), y(0.0), z(z) {}

Vector3D::Vector3D(const Vector3D& vec)
{
	Init(vec.x, vec.y, vec.z);
}

// СЛУЖБОВІ МЕТОДИ
void Vector3D::Init(double x, double y, double z)
{
	// Перевірка на NaN або Inf
	if (std::isnan(x) || std::isinf(x) || std::isnan(y) || std::isinf(y) || std::isnan(z) || std::isinf(z))
	{
		std::cerr << "! Числа координат не можуть бути NaN або Inf. Встановлено нулі." << std::endl;
		this->x = 0.0;
		this->y = 0.0;
		this->z = 0.0;
	}
	else
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
}

void Vector3D::Read()
{
	double x_in, y_in, z_in;
	std::cout << "Введіть координату X: ";
	while (!(std::cin >> x_in))
	{
		std::cerr << "Невірно. Введіть дійсне число." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cout << "Введіть координату Y: ";
	while (!(std::cin >> y_in))
	{
		std::cerr << "Невірно. Введіть дійсне число." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cout << "Введіть координату Z: ";
	while (!(std::cin >> z_in))
	{
		std::cerr << "Невірно. Введіть дійсне число." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	Init(x_in, y_in, z_in);
}

void Vector3D::Display() const
{
	std::cout << toString() << std::endl;
}

std::string Vector3D::toString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(4); // Форматування виводу
	ss << "(" << x << ", " << y << ", " << z << ")";
	return ss.str();
}



double Vector3D::lengthVec3D() const
{
	return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

double Vector3D::dotProduct(const Vector3D& secondVec) const
{
	return (x * secondVec.x) + (y * secondVec.y) + (z * secondVec.z);
}


//перевантаження операторів
bool Vector3D::operator<(const Vector3D& secondVec) const
{
	return this->lengthVec3D() < secondVec.lengthVec3D();
}

bool Vector3D::operator==(const Vector3D& secondVec) const
{
	//порівняння з Епсілон для уникнення похибок double
	bool x_equal = std::abs(x - secondVec.x) < EPSILON;
	bool y_equal = std::abs(y - secondVec.y) < EPSILON;
	bool z_equal = std::abs(z - secondVec.z) < EPSILON;
	return x_equal && y_equal && z_equal;
}

Vector3D Vector3D::operator+(const Vector3D& secondVec) const
{
	//використовуємо конструктор для створення результату
	return Vector3D(x + secondVec.x, y + secondVec.y, z + secondVec.z);
}

Vector3D Vector3D::operator-(const Vector3D& secondVec) const
{
	//використовуємо конструктор для створення результату
	return Vector3D(x - secondVec.x, y - secondVec.y, z - secondVec.z);
}

Vector3D Vector3D::operator*(double scalar) const
{
	//використовуємо конструктор для створення результату
	return Vector3D(x * scalar, y * scalar, z * scalar);
}

//додаткова функція, що викликає operator==
bool Vector3D::equalsVec3D(const Vector3D& secondVec) const
{
	return *this == secondVec;
}