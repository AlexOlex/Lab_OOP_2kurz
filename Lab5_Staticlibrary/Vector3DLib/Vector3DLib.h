//Vector3DLib.h
#pragma once
#include <string>

//оголошення класу Vector3D
class Vector3D
{
private:
	//закриті поля (координати)
	double x;
	double y;
	double z;

	//константа Епсілон для безпечного порівняння double
	static constexpr double EPSILON = 1e-9;

public:
	// 1
	//дефолтний конструктор
	Vector3D();
	// 2
	//конструктор з трьома параметрами
	Vector3D(double x, double y, double z);
	// 3
	//конструктор з однією координатою Z (explicit)
	explicit Vector3D(double z);
	// 4
	//конструктор копіювання
	Vector3D(const Vector3D& vec);

	//службові методи
	void Init(double x, double y, double z);
	void Read();
	void Display() const;
	std::string toString() const;

	
	double lengthVec3D() const;
	double dotProduct(const Vector3D& vec) const;

	//перевантаження операторів
	bool operator<(const Vector3D& vec) const;
	bool operator==(const Vector3D& vec) const;
	Vector3D operator+(const Vector3D& vec) const;
	Vector3D operator-(const Vector3D& vec) const;
	Vector3D operator*(double scalar) const;

	//додаткова функція для демонстрації використання оператора
	bool equalsVec3D(const Vector3D& vec) const;
};