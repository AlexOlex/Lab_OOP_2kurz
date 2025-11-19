#pragma once
#include <iostream>
#include <stdexcept>


// Власні виключення реалізоване в трьох варіантах
// (три способи оголошення власного типу виключення)

// 1
//порожній клас (для демонстрації throw()/noexcept)
class EmptyForExceptions
{
   
};

// 2
//незалежний клас (не наслідує std::exception)
//це власний тип виключення, що може зберігати додаткову інформацію про помилку (про параметри)
class ParamIndepenForExceptions
{
private:
    double a; // параметр a рівняння
    double b; // параметр b рівняння

public:
    ParamIndepenForExceptions(double a, double b); //конструктор оголошення з параметрами
    void printInfoWithIndependent() const;         //метод що виведе додаткову інформацію про помилкові параметри
};

// 3
//спадкоємець DerivedForExceptions від std::runtime_error
class DerivedForExceptions : public std::runtime_error
{
private:
    double a; // параметр a
    double b; // параметр b

public:
    DerivedForExceptions(double a, double b); // конструктор оголошення
    void showParamsInfoWithDerived() const;   // метод оголошення
};


//////////////////////////////////////////////////////////////
// Оголошення функцій, які перевіряють передані параметри і
// генерують виключення у випадку помилкових (4 варіанти + 1 для похідного класу)

// 1
// без специфікації виключень
// може кидати будь-які типи виключень
double LinearRoot(double a, double b);

// 2
// з порожньою специфікацією throw()/noexcept
// якщо буде кинуто виключення -> std::terminate()
double LinearRootNoThrow(double a, double b) noexcept;

// 3
// з конкретною специфікацією стандартного виключення
double LinearRootStandartException(double a, double b) throw(std::invalid_argument);

// 4
// специфікація із власним реалізованим виключенням
double LinearRootCustomException(double a, double b) throw(ParamIndepenForExceptions);

// 5
// специфікація із власним спадкоємцем від стандартного виключення std::runtime_error
// має власні поля a, b і метод для друку параметрів
double LinearRootDerived(double a, double b) throw(DerivedForExceptions);
