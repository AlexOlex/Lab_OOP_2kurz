//Vector3DDLL.h
#pragma once
#include <string>

//макрос для керування експортом/імпортом:
//якщо визначено VECTOR3D_EXPORTS (у проекті DLL), клас експортується, 
//в іншому випадку (у клієнтському додатку), клас імортується
#ifdef VECTOR3D_EXPORTS
#define VECTOR3D_API __declspec(dllexport) //для експорту з DLL
#else
#define VECTOR3D_API __declspec(dllimport) //для імпорту клієнтським додатком
#endif

//оголошення класу Vector3D, який експортується
class VECTOR3D_API Vector3D
{
private:
	//закриті поля (координати)
	double x;
	double y;
	double z;

	//константа Епсілон для безпечного порівняння double
	static constexpr double EPSILON = 1e-9;

public:
	//конструктори
	Vector3D();
	Vector3D(double x, double y, double z);
	explicit Vector3D(double z);
	Vector3D(const Vector3D& vec);


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
	//додаткова функція для демонстрації виклику operator==
	bool equalsVec3D(const Vector3D& vec) const;
};
