#pragma once
#include <string> //дл€ std::string (цей тип повертаЇтьс€ toString(), €ка оголошена тут)

//оголошенн€ класу Vector3D
class Vector3D
{
    //закрит≥ пол€ (по дефолту приватн≥)
    double x;
    double y;
    double z;

public:
   
    void Init(double x, double y, double z);
    void Read();
    void Display() const;

    std::string toString() const;


    //додаванн€ вектор≥в
    Vector3D addVec3D(const Vector3D& vec) const;

    //в≥дн≥манн€ вектор≥в
    Vector3D subVec3D(const Vector3D& vec) const;

    //множенн€ вектора на скал€р
    Vector3D multVec3DScalar(double scalar) const;

    //довжина вектора
    double lengthVec3D() const;

    //перевантаженн€ оператора < дл€ пор≥вн€нн€ довжини вектор≥в
    bool operator<(const Vector3D& vec) const;

    //скал€рний добуток вектор≥в (eng dot product), поверне скал€р
    double dotProduct(const Vector3D& vec) const;

    //пор≥вн€нн€ вектор≥в на р≥вн≥сть 
    bool equalsVec3D(const Vector3D& vec) const;
}; 