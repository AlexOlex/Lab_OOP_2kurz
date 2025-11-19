#include "Vector3D.h" 
#include <iostream>
#include <sstream> //для std::stringstream (використовується в toString)
#include <limits>  //для std::numeric_limits
#include <cmath>   //для std::sqrt і std::pow (у lengthVec3D() ),  std::abs() (у equalsVec3D() ), 
//std::isnan() і std::isinf() (у Init() )
#include <iomanip> //для  для форматування чисел у потоку (для std::setprecision, який використовує stringstream)


//константа Епсілон (для безпечного порівняння double, потрібна через похибки округлень чисел з плаваючую точкою)
//= максимально допустима похибка між двома числами ( |A-B|<Епсілон - якщо true, числа вважаються рівними)
const double EPSILON = 1e-9;


void Vector3D::Init(double x, double y, double z)
{
    //перевірка на NaN або Inf  
    if (std::isnan(x) || std::isinf(x) ||
        std::isnan(y) || std::isinf(y) ||
        std::isnan(z) || std::isinf(z))
    {
        std::cerr << "Числа координат не можуть бути NaN або Inf. Встановлено по замовчуванню нулі." << std::endl;
        //присвоюємо дефолтні значення закритим полям класу
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
    }
    else
    {
        //присвоюємо значення закритим полям класу
        this->x = x;
        this->y = y;
        this->z = z;
    }
}

void Vector3D::Read()
{
    double x, y, z;

    //введеняя координат з контролем невірного введення

    std::cout << "Введіть координату X: ";
    while (!(std::cin >> x))
    {
        std::cerr << "Невірно. Введіть дійсне число." << std::endl;

        //скидання у cin прапорів при помилках введення, які блокують подальші введення
        std::cin.clear();

        //очищення буфера до кінця рядка (логічне видалення-пропускає у cin макс можливу кількость символів
        //поки не зустрінеться символ нового рядка \n)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введіть координату Y: ";
    while (!(std::cin >> y))
    {
        std::cerr << "Невірно. Введіть дійсне число." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введіть координату Z: ";
    while (!(std::cin >> z))
    {
        std::cerr << "Невірно. Введіть дійсне число." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    //фінальна перевірка і встановлення значень 
    Init(x, y, z);
}


void Vector3D::Display() const
{
    //виводимо використовуючи toString
    std::cout << toString() << std::endl;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////

//перетворення вектора у рядок у вигляді "(x, y, z)"
std::string Vector3D::toString() const
{
    //використовуємо stringstream для формування рядка
    //дозволяє формувати рядок поетапно як у потоці, а результат поміщається у string
    //з stringstream НЕ потрібна конкатенація з to_string() для кожної координати
    //також при необхідності буде легко додати форматування, наприклад встановити кількість цифр 
    //після коми через ss.precision(2) або std::setprecision(n),
    //вирівнять числа у колонках через std::setw() фбо std::setfill()тощо (наприклад  ss << std::setprecision(4);)
    
 
    std::stringstream ss;
   
    ss << std::fixed << std::setprecision(4); // встановлюємо фіксовану точність до 4 знаків після коми
    ss << "(" << x << ", " << y << ", " << z << ")";
    return ss.str(); //з ss.str() отримуємо весь вміст потоку як об’єкт string
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

// КОНСТРУКТОРИ

//Vector3D() { } - якщо дефолтний конструктор визначити так, при створенні
//значення полів x, y, z будуть неініціалізовані (міститимуть "сміття" )
 
// 1
//дефолтний конструктор з ініціалізацією через список ініціалізаці :
//всі поля будуть відразу ініціалізовані нулями при створенні об’єкта
Vector3D::Vector3D() : x(0.0), y(0.0), z(0.0) //пряма ініціалізація полів нулями через список ініцалізації
{
    //можна було викликати Init(0,0,0), але так швидше ( без подвійного присвоєння спочатку
    //через список ініціалізації, потім через Init() );
    //також немає сенсу проводити перевірку, оскільки константні значення 0.0 завжди коректні 
}

// 2
//конструктор з трьома параметрами (за замовчуванням):
Vector3D::Vector3D(double x, double y, double z) //: x(x), y(y), z(z) - без списку ініціалізації, яка тут через Init()
{
    //перевірка на коректність вводу (але тут буде подвійне присвоєння спочатку через список ініціалізації, потім у Init())
    Init(x, y, z);

}

// 3
//конструктор для лише z (explicit заборонить неявне перетворення double->Vector3D):
//НЕ КОНФЛІКТУЄ з дефолтним конструктором;
//ініціалізація без перевірки коректності вводу
Vector3D::Vector3D(double z) : x(0.0), y(0.0), z(z) //пряма ініціалізація полів через список ініціалізації 

{
    
}

// 4
//конструктор копіювання:
Vector3D::Vector3D(const Vector3D& vec)
{
    Init(vec.x, vec.y, vec.z);
}

// 5
//конструктор для демонстрації пріоритету ініціалізації:
//це дефолтний Vector3D() 

//C2084: function 'Vector3D::Vector3D(void)' already has a body при Vector3D::Vector3D(): x(2.0), y(5.0)  -
//КОНФЛІКТУЄ  з дефолтним Vector3D::Vector3D(): помилка C2084 означає, що 
//не можна мати ще одне тіло з таким самим сигнатурним записом

//порядок ініціалізації полів при створенні об'єкта буде таким:
//  1 - DMI (Default Member Initialization), це внутрішнє початкове присвоєння членам класу;
//якщо в Vector3D.h для полів задано початкові значення, вони будуть присвоєні першими;
//у нашому випадку поля не ініціалізовані, таким чином DMI для x, y, z відсутні,
//тому спочатку вони містять "сміття"
//  2 - список ініціалізації конструктора: присвоює значень x = 2.0, y = 5.0
//до тіла конструктора ще не дішли;
//z ще не змінене списком ініціалізації, тому в ньому  залишається "сміття" 
//  3 - тіло конструктора: тут присвоюємо z = 10.0 (це значення стане остаточним для z)

//якщо б у Vector3D.h було присвоєння значень (наприклад, double z = 0;), то z спочатку б ініціалізувалась нулем 0, 
//а потім у тілі конструктора було б присвоєно на 10 (перезапис = подвійна ініціалізація)

Vector3D::Vector3D(bool demo) : x(2.0), y(5.0) //додали параметр bool demo щоб сигнатура стала відмінна від Vector3D::Vector3D(): x(2.0), y(5.0) 
{
    //поля x і y на цьому етапі ініціалізовані списоком ініціалізації ( : x(2.0), y(5.0) )
    //поле z отримало значення DMI (0.0) якщо було вказано у Vector3D.h ( якщо там поле double z =0;)
    
    //тепер нові значення присвоюються безпосередньо вручну
    z = 10.0;

    std::cout << "Демонстрація пріоритету ініціалізації x = " << x << " y = " << y << " z = " << z << std::endl;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////


// Статичний метод для створення вектора з однаковими координатами
Vector3D Vector3D::Vec3DEqualCoords(double value)
{
    //повертає новий вектор зі значеннями (value, value, value)
    return Vector3D(value, value, value);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////


Vector3D Vector3D::addVec3D(const Vector3D& secondVec) const
{
    //додавання  v3 = v1 + v2
    //Vector3D res;
    //res.Init(x + secondVec.x, y + secondVec.y, z + secondVec.z); 
    //return res;
    //АЛЕ теперь спрацює коротший запис оскільки є конструктор Vector3D(double x, double y, double z) 
    //який також викликає Init() для перевірки координат
    return Vector3D(x + secondVec.x, y + secondVec.y, z + secondVec.z);
}

Vector3D Vector3D::subVec3D(const Vector3D& secondVec) const
{
    //віднімання v3 = v1 - v2
    //Vector3D res;
    //res.Init(x - secondVec.x, y - secondVec.y, z - secondVec.z);
    //return res;
    //АЛЕ теперь спрацює коротший запис оскільки є конструктор Vector3D(double x, double y, double z) 
    //який також викликає Init() для перевірки координат
    return Vector3D(x - secondVec.x, y - secondVec.y, z - secondVec.z);
}

Vector3D Vector3D::multVec3DScalar(double scalar) const
{
    //множення на скаляр v2 = v1*s
    // Vector3D res;
    //res.Init(x * scalar, y * scalar, z * scalar);
    //return res;
    //АЛЕ теперь спрацює коротший запис оскільки є конструктор Vector3D(double x, double y, double z) 
    //який також викликає Init() для перевірки координат
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

//довжина вектора |v| = sqrt(x^2 + y^2 + z^2)
double Vector3D::lengthVec3D() const
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

//порівняння довжини поточного векторів
bool Vector3D::operator<(const Vector3D& secondVec) const
{

    return this->lengthVec3D() < secondVec.lengthVec3D(); //поверне true при виконанны умови
}


//скалярний добуток (eng dot product): v1.v2 = x1*x2 + y1*y2 + z1*z2
double Vector3D::dotProduct(const Vector3D& secondVec) const
{
    return (x * secondVec.x) + (y * secondVec.y) + (z * secondVec.z);
}

bool Vector3D::equalsVec3D(const Vector3D& secondVec) const
{
    //порівняння векторів на рівність (умова рівності |A-B| < Епсілон )
    bool x_equal = std::abs(x - secondVec.x) < EPSILON;
    bool y_equal = std::abs(y - secondVec.y) < EPSILON;
    bool z_equal = std::abs(z - secondVec.z) < EPSILON;

    return x_equal && y_equal && z_equal;
}
