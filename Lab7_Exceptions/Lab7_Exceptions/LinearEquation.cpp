#include "LinearEquation.h"

//Реалізаця класів:

// 2
// ParamIndepenForExceptions
ParamIndepenForExceptions::ParamIndepenForExceptions(double a, double b)
    : a(a), b(b) {}

void ParamIndepenForExceptions::printInfoWithIndependent() const
{
    std::cout << "\t!Помилкові параметри a = " << a << ", b = " << b << std::endl;
}

// 3
//спадкоємець від стандартного std::runtime_error
DerivedForExceptions::DerivedForExceptions(double a, double b)
    : std::runtime_error("\t!Коефіцієнт a не може бути 0"), a(a), b(b) {} //пряма ініціалізація списком

void DerivedForExceptions::showParamsInfoWithDerived() const //виведе додаткову інформацію про помилкові параметри
{
    std::cout << "\tЗначення a = " << a << ", b = " << b << std::endl;
}



//////////////////////////////////////////////////////////////

//Реалізація функцій:

// 1
//без специфікації виключень
double LinearRoot(double a, double b) ////немає throw/noexcept в сигнатурі
{
    if (a == 0)
        // стандартне std::runtime_error (з бібліотеки <stdexcept>) - непередбачені помилки часу виконання; 
        // замість повернення результату кидає виключення (створює об'єкт runtime_error)
        throw std::runtime_error("\tLinearRoot: коефіцієнт a не може бути 0, оскільки немає кореня");
    return -b / a;
}

// 2
//з порожньою специфікацією throw()/noexcept
double LinearRootNoThrow(double a, double b) noexcept
{
    if (a == 0)
        throw EmptyForExceptions();
    return -b / a;
}

// 3
// з конкретною специфікацією стандартного виключення
double LinearRootStandartException(double a, double b) throw(std::invalid_argument)
{
    if (a == 0)
        throw std::invalid_argument("\ta == 0: неможливо знайти єдиний корінь.");
    return -b / a;
}

// 4
// специфікація із власним реалізованим виключенням
double LinearRootCustomException(double a, double b) throw(ParamIndepenForExceptions)
{
    if (a == 0)
        throw ParamIndepenForExceptions(a, b);
    return -b / a;
}

// 5
// специфікація із власним спадкоємцем від стандартного виключення std::runtime_error
double LinearRootDerived(double a, double b) throw(DerivedForExceptions)
{
    if (a == 0)
        throw DerivedForExceptions(a, b);
    return -b / a;
}
