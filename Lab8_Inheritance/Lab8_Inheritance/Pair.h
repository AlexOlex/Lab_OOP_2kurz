//Pair.h
#pragma once
#include <iostream>
#include <string> //для  toString()

//базовий клас Pair
class Pair
{
protected: //поля будуть доступні спадкоємцям
    int first;
    int second;

public:
    Pair(int f = 0, int s = 0);

    //віртуальний деструктор !завжди потрібен у базових класах для видалення
    virtual ~Pair() = default;

    //методи зміни полів
    void setFirst(int f);
    void setSecond(int s);
    int getFirst() const { return first; }
    int getSecond() const { return second; }

    //віртуальні методи порівняння для демонстрації поліморфізму
    virtual bool operator>(const Pair& other) const;
    virtual bool operator<(const Pair& other) const;
    virtual bool operator==(const Pair& other) const;

    //віртуальний метод для виведення об'єкта
    virtual std::string toString() const;
};


//клас спадкоємець Fraction(Дріб)
class Fraction : public Pair
{
private:
    //успадковує first та second

public:
    //конструктор
    Fraction(int numerator = 0, int denominator = 1);

    //методи порівняння (перевизначення віртуальних)
    bool operator>(const Pair& other) const override;
    bool operator<(const Pair& other) const override;
    bool operator==(const Pair& other) const override;

    //не поліморфні методи перевизначення 
    bool operator>=(const Pair& other) const;
    bool operator<=(const Pair& other) const;
    bool operator!=(const Pair& other) const;

    //перевизначення методу виведення (поліморфний)
    std::string toString() const override;

    //специфічні методи для Fraction
    void setNumerator(int num) { setFirst(num); }
    void setDenominator(int den);

    int getNumerator() const { return getFirst(); }
    int getDenominator() const { return getSecond(); }
};



//допоміжна функція 
void demoPolymorphismByCompare(Pair* p1, Pair* p2);