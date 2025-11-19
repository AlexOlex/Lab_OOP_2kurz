#include "LinearEquation.h"
//#include <thread> // для std::this_thread::sleep_for() (щоб додати паузу при виведенні)
//#include <chrono> // для std::chrono::milliseconds (задання часу паузи)
#include <Windows.h> //для функцій SetConsoleOutputCP та SetConsoleCP

int main()  // Головна функція, тут обробка всіх виключень
{
    //для відображення і роботи з українськими символами в консолі
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    double a = 0;
    double b = 42.0;

    std::cout << "ЗАВДАННЯ 7 Варіант 2: Механізм обробки виключень у C++ \n";

    // 1️ Без специфікації виключень
    try
    {
        std::cout << "\n\tLinearRoot: " << "x = " << LinearRoot(a, b) << std::endl;
    }
    catch (std::runtime_error& e)
    {
        std::cout << "\n\tперехоплено std::runtime_error: "
            // what() функція базового класу std::exception що виведе рядок переданий std::runtime_error
            << e.what()
            << std::endl;
    }


    // 2 - перенесено в самий кінець main для демонстрації порушення з аварійним завершенням 
     
     
     
    // 3️
    // з конкретною специфікацією стандартного виключення:
    try
    {
        std::cout << "\n\tLinearRootStandartException: " << "x = "
            << LinearRootStandartException(a, b) << std::endl;
    }
    catch (std::invalid_argument& e)
    {
        std::cout << "\n\tперехоплено std::invalid_argument: " << e.what() << std::endl;
    }

    // 4️
     // з власним типом виключення з параметрами
    try
    {
        std::cout << "\n\tLinearRootCustomException: " << "x = "
            << LinearRootCustomException(a, b) << std::endl;
    }
    catch (ParamIndepenForExceptions& e)
    {
        std::cout << "\n\tперехоплено клас ParamIndepenForExceptions: ";
        e.printInfoWithIndependent();
    }

    // 5️
    // спадкоємець від std::runtime_error з власними полями
    try
    {
        std::cout << "\n\tLinearRootDerived: " << "x = "
            << LinearRootDerived(a, b) << std::endl;
    }
    catch (DerivedForExceptions& e)
    {
        std::cout << "\n\tперехоплено DerivedForExceptions: "
            << e.what() << std::endl;
        e.showParamsInfoWithDerived();
    }



    //std::cerr одразу виводить повідомлення на екран повз буфер 
    //для додаткової гарантії що рядок виведеться перед аварійним завершенням при виклику LinearRootNoThrow(a, b)
   //std::cerr << "\n\tдалі буде LinearRootNoThrow : порушення стандарту throw()/noexcept" << std::endl;
    //примусово виводить буфер (ще додаткова гарантія виведення)
    //std::cerr.flush(); 



    // 2️
     //порожньою специфікацією throw():
     //catch НЕ буде досягнуто через порушення контракту про те, що не буде кидати виключень
    try
    {
        std::cout << "\n\tLinearRootNoThrow: порушення стандарту throw()/noexcept, буде викликано std::terminate() " << LinearRootNoThrow(a, b) << std::endl;
    }

    //сюди програма не дійде
    catch (EmptyForExceptions&) 
    {
        std::cout << "\n\tперехоплено порожній клас власного виключення EmptyForExceptions :" << std::endl;
    }

    return 0;
}
