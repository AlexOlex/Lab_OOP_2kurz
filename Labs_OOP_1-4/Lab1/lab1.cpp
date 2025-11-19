#include "StructOfTwoFields.h" //включаємо оголошення структури
#include <iostream> 
#include <Windows.h> //для функцій SetConsoleOutputCP та SetConsoleCP

int main()
{
    //для відображення і роботи з українськими символами в консолі
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    StructOfTwoFields s;

    std::cout << "ЗАВДАННЯ варіант_2: Підведення дробового числа у дробовий степінь \n" << std::endl;

    s.Read();
    s.Display();

    //виклик власної реалізації з простіру імен MyMath
    double customRes = MyMath::power(s.first, s.second);
    std::cout << "Результат (MyMath::power з реалізацію через exp-log): " << s.first << " у степені " << s.second << " = " << customRes << std::endl;

    //виклик реалізації методу з std::pow
    double standRes = s.power();
    std::cout << "Результат (power з реалізацію через std::pow): " << s.first << " у степені " << s.second << " = " << standRes << std::endl;

    return 0;
}
