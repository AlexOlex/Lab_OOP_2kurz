#include "Vector3D.h" 
#include <iostream>
#include <sstream> //для std::stringstream (використовується в toString)
#include <limits>  //для std::numeric_limits
#include <cmath>   //для std::sqrt і std::pow (у lengthVec3D() ),  std::abs() (у equalsVec3D() ), 
                   //std::isnan() і std::isinf() (у Init() )

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

//перетворення вектора у рядок у вигляді "(x, y, z)"
std::string Vector3D::toString() const
{
    //використовуємо stringstream для формування рядка
    //дозволяє формувати рядок поетапно як у потоці, а результат поміщається у string
    //з stringstream НЕ потрібна конкатенація з to_string() для кожної координати
    std::stringstream ss;
    ss << "(" << x << ", " << y << ", " << z << ")";
    return ss.str();
}


Vector3D Vector3D::addVec3D(const Vector3D& secondVec) const
{
    //додавання res = v3 = v1 + v2
    Vector3D res;
    //Init для коректної ініціалізації
    res.Init(x + secondVec.x, y + secondVec.y, z + secondVec.z);
    return res;
}

Vector3D Vector3D::subVec3D(const Vector3D& secondVec) const
{
    //віднімання res = v3 = v1 - v2
    Vector3D res;
    res.Init(x - secondVec.x, y - secondVec.y, z - secondVec.z);
    return res;
}

Vector3D Vector3D::multVec3DScalar(double scalar) const
{
    //множення на скаляр v2 = v1*s
    Vector3D res;
    res.Init(x*scalar, y*scalar, z*scalar);
    return res;
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
    return (x*secondVec.x) + (y*secondVec.y) + (z*secondVec.z);
}

bool Vector3D::equalsVec3D(const Vector3D& secondVec) const
{
    //порівняння векторів на рівність (умова рівності |A-B| < Епсілон )
    bool x_equal = std::abs(x - secondVec.x) < EPSILON;
    bool y_equal = std::abs(y - secondVec.y) < EPSILON;
    bool z_equal = std::abs(z - secondVec.z) < EPSILON;

    return x_equal && y_equal && z_equal;
}