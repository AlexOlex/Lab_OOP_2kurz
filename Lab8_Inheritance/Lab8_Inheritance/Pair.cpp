//Pair.cpp
#include "Pair.h"
#include <sstream>
#include <stdexcept>
#include <typeinfo> //для typeid


Pair::Pair(int f, int s) : first(f), second(s) {}

//сеттери полів
void Pair::setFirst(int f)
{
    first = f;
}

void Pair::setSecond(int s)
{
    second = s;
}

//p1 > p2 - якщо (first.p1 > first.p2) або (first.p1 = first.p2 і second.p1 > second.p2)
bool Pair::operator>(const Pair& secObj) const
{
    if (first > secObj.first) {
        return true;
    }

    if (first == secObj.first && second > secObj.second) {
        return true;
    }
    return false;
}

bool Pair::operator<(const Pair& secObj) const
{
    //використовуємо визначений оператор >
    return secObj > *this;
}

bool Pair::operator==(const Pair& secObj) const
{
    return first == secObj.first && second == secObj.second;
}



std::string Pair::toString() const
{
    std::stringstream s;
    s << "(" << first << ", " << second << ")";
    return s.str();
}


///////////////////////////////////////////////////////////////////////////////////////////////
//похідний клас Fraction:

//конструктор Fraction встановлює прихований vptr об'єкта так, щоб він вказував
//на vtable класу Fraction (одна на весь клас), таким чином фіксується реальний тп об'єкта;
//!vptr завжди буде вказувати на Fraction::vtable;
//роль статичного (фіксованого) типу покажчика Pair* по суті використовується компілятором лише
//щоб дозволити доступ до методів, але він не впливає на vptr об'єкта

Fraction::Fraction(int numerator, int denominator) : Pair(numerator, denominator) {
    //встановлюємо знаменник, перевіряючи на 0
    setDenominator(denominator);
}

void Fraction::setDenominator(int den) {
    if (den == 0) {
        throw std::invalid_argument("!знаменник не повинен = 0 ");
    }
    second = den;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Перевизначення операторів порівняння для дробів:

//метод крос множення використаний в Fraction::operator>() та Fraction::operator==() (порівняння двох Fraction);
//1ий чисельник*2ий знаменник = 2ий чисельник*1ий знаменник: a/b > c/d => a*d > c*b ;
//в методі використовується виключно цілочисельна арифметика; 
//оскільки добуток двох int може перевищити макс значення int, для уникнення такого
//переповнення важливе використання приведення до long long перед множенням


bool Fraction::operator>(const Pair& secObj) const
{
    //безпечне приведення типу //безпечне приведення типу otherFraction через dynamic_cast
    const Fraction* secondFraction = dynamic_cast<const Fraction*>(&secObj);

    if (secondFraction) {
        //якщо знаменники > 0
        //(first/second) > (secondFraction->first)/(secondFraction->second)
        return (long long)first * secondFraction->second > (long long)secondFraction->first * second;
    }
    //при порівнянні Fraction з Pair, порівнюємо як Pair (логіка базового класу)
    return Pair::operator>(secObj);
}



bool Fraction::operator<(const Pair& secObj) const
{
    return !(*this > secObj) && !(*this == secObj);
}



//тут також метод крос множення (a*d == c*b => a/b == c/d)
bool Fraction::operator==(const Pair& secObj) const
{
    const Fraction* secondFraction = dynamic_cast<const Fraction*>(&secObj);

    if (secondFraction)
    {
        //a = first (чисельник 1)
        //b = this->second (знаменник 1)
        //c = secondFraction->first (чисельник 2)
        //d = secondFraction->second (знаменник 2)
        //(first/this->second) == (secondFraction->first) / (secondFraction->second)
        return (long long)first * secondFraction->second ==
            (long long)secondFraction->first * this->second;
    }

    //якщо порівнюємо з Pair, повертаємося до логіки базового класу
    return Pair::operator==(secObj);
}


bool Fraction::operator>=(const Pair& secObj) const
{
    return *this > secObj || *this == secObj;
}


bool Fraction::operator<=(const Pair& secObj) const {
    return *this < secObj || *this == secObj;
}


bool Fraction::operator!=(const Pair& secObj) const {
    return !(*this == secObj);
}


std::string Fraction::toString() const {
    std::stringstream s;
    s << first << "/" << second;
    return s.str();
}


////////////////////////////////////////////////////////////////////////////////////////////////

void demoPolymorphismByCompare(Pair* p1, Pair* p2)//приймає покажчики на базовий клас Pair*
{
    std::cout << " динамічне зв'язування об'єктів Fraction та Pair (через покажчик на Pair*)\n";

    //буде викликано Pair::toString() або Fraction::toString() залежно від реального типу об'єкта на який вказує p1/p2;
    //компілятор перевіре чи оголошений метод toString() у Pair (якщо ні і є тільки у Fraction -> помилка компіляції
    std::cout << "значення Об'єкта 1 (LHS): " << p1->toString() << "\n";
    std::cout << "значення Об'єкта 2 (RHS): " << p2->toString() << "\n";

    //Виклик віртуальних функцій (=підстановка, =поліморфний виклик, =динамчна диспетчиризація):
    //кожен об'єкт з віртуальними функціями має прихований віртуальний покажчик
    //vptr (встановлюється його конструктором на етапі виконання), який
    //вказує на vtable (таблицю віртуальних функцій), яка містить адреси функцій оголошених virtual, 
    //vtable єдина для всього класу, створюється при компіляції для всіх фуекцій з  virtual

    //ПІДСТАНОВКА:
    //при виклику *p1 > *p2 НЕ превіряється тип, а зчитуються перша комірка пам'ті об'єкта,
    //на який вказує p1, а саме там знаходиться vptr, ця адреса завжди вказує на vtable класу 
    //(тип, яким об'єкт був створений, у нас це Fraction) -> з vtable зчитується адреса
    //перевантаженого operator> (у нас оголошений virtual) за фіксованим індексом для виклику реальної функції

    if (*p1 > *p2) {
        std::cout << p1->toString() << " > " << p2->toString()
            << ", динамічний виклик operator> , " << "було викликано " << typeid(*p1).name() << "::operator>\n";
    }
    else if (*p1 < *p2) {
        std::cout << p1->toString() << " < " << p2->toString()
            << ", динамічний виклик operator< , " << "було викликано " << typeid(*p1).name() << "::operator<\n";
    }
    else {
        std::cout << p1->toString() << " = " << p2->toString()
            << ", динамічний виклик operator== , " << "було викликано " << typeid(*p1).name() << "::operator==\n";
    }
}
