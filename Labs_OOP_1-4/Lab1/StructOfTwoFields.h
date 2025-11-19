#pragma once

//оголошення структури StructOfTwoFields
struct StructOfTwoFields
{   
    //публічні поля по дефолту
    double first;  //основа
    double second; //показник ступеня

    //методи структури
    void Init(double a, double b);
    void Read();
    void Display() const;

  //оголошення фунції яка буде реалізована через std::pow()
    double power() const;
};


//оголошення власного простіру імен для альтернативної power
namespace MyMath
{
    //оголошення фунції яка буде реалізована через std::exp() и std::log()
    double power(double base, double exp);
}