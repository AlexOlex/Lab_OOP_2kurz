//Triangle.cpp
#include "Triangle.h"

 //функція для обчислення відстані між двома точками (э необхідна для конструктора TriangleByVertices)

double dist(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

//Клас Triangle

//дефолтний конструктор зі списком ініціалізаціі
Triangle::Triangle() : a(0.0), b(0.0), c(0.0) {}

//конструктор з трьома параметрами
Triangle::Triangle(double side_a, double side_b, double side_c)
    : a(side_a), b(side_b), c(side_c) //пряма ініціалізація списком
{
    //перевірка чи існує трикутник при створенні за сторонами
    if (!checkTriangleInequality()) {
        throw std::invalid_argument(" трикутника з такими сторонами не існує ");
    }
}

//конструктор зза основами трьох медіан (пункт 2 завдання)
Triangle::Triangle(double ma, double mb, double mc, InitByMedians) //InitByMedians - тег
{
    //перевірка на існування трикутника, утвореного медіанами:
    //медіани трикутника повинні задовольняти нерівності трикутника; якщо сума довжин двох медіан
    //не більша за довжину третьої, то трикутник не може існувати.
    // 
    //оскільки якщо при преевірці умови буде true, в такому випадку значення аргументів будут
    //знаходитись поза допустимим діапазоном з точки зору геометріії, і при цьому вони знаходяться 
    //в допустимому діапазоні типів(double>0) - тому обрано тип виключення std::invalid_argument

    if (ma + mb <= mc + EPSILON || ma + mc <= mb + EPSILON || mb + mc <= ma + EPSILON)
    {
        throw std::invalid_argument(" трикутника за такими медінами не існує ");
    }

    //знаходження сторін трикутника за медіанами по формуллі x = (2/3)*(sqrt(2*y^2 + 2*z^2 - x^2)):
    // Формула: x = 2/3 * sqrt(2*y^2 + 2*z^2 - x^2)
    a = (2.0 / 3.0) * std::sqrt(2.0 * mb * mb + 2.0 * mc * mc - ma * ma);
    b = (2.0 / 3.0) * std::sqrt(2.0 * ma * ma + 2.0 * mc * mc - mb * mb);
    c = (2.0 / 3.0) * std::sqrt(2.0 * ma * ma + 2.0 * mb * mb - mc * mc);

    if (!checkTriangleInequality())
    {
        throw std::invalid_argument("Три вершини лежать на одній прямій - трикутник вирождений");
    }
}

//перевірка нерівності трикутника (є в усіх конструкторах)
bool Triangle::checkTriangleInequality() const
{
    return (a > 0 && b > 0 && c > 0 &&
        a + b > c + EPSILON && a + c > b + EPSILON && b + c > a + EPSILON);
}


//додаткова функція для обчислення півперимтра для використання в getArea()
double Triangle::getPerimeter() const
{
    return a + b + c;
}

//базова реалізація для обчислення площі (по формулі Герона S = sqrt( p*(p-a)*(p-b)*(p-c) )
double Triangle::getArea() const
{
    double pp = getPerimeter() / 2.0; //півпериметр

    return std::sqrt(pp * (pp - a) * (pp - b) * (pp - c));
}



//обчислення довжини довільної медіани по формулі mx = 0.5 * sqrt(2*y^2 + 2*z^2 - x^2)
//side - сторона a, b, або c
double Triangle::calcMedian(char side) const
{

    //перевірка чи сторони задано недодатніми або =0 ;
    //if (a <= 0 || b <= 0 || c <= 0) {
    // throw std::domain_error("сторони трикутника повинні бути додатними");
    // 
    //можна додати як додатковий захист; дещо надлишковий, але в С++ можна обійти захист приватних полів через покажчик:
    //напр.при Triangle t(11.0, 13.0, 17.0); double* ptr_to_a = (double*)&t;  *ptr_to_a = -11.0;- відбуваєтся небезпечне
    //небезпечне приведення зі зміною поля a на від'ємне небезпечне, тобто відбувається приведння покажчика
    //на Triangle на покажчик double, ptr вказує на поле a, а оскольки компілятор часто розміщує об'явлені поля 
    //послідовно, всі три поля можжна змінити через *ptr, *(ptr+1), *(ptr+2)


    //використаємо конструкцію switch для вибору формули залежно від сторони;
    //tolower() - для забезпечення регістронезалежності символу сторони (щоб користувач міг задавати і малі, і великі символи)
    switch (std::tolower(side))
    {
        //для піднесення у квадрат використаєме перемноження змінної саму на себе x*x,
        //оскільки ії альернатива std::pow(x, 2.0) більш повільна 

    case 'a': {
        //ma = 0.5 * sqrt(2*b^2 + 2*c^2 - a^2)
        double exprUnderRoot = 2.0 * b * b + 2.0 * c * c - a * a;

        //перевірка чи підкореневий вираз від'ємний if (exprUnderRoot < 0);
        //std::domain_error - виняток буде викинуто якцо математична операція не може бути виконана тому що 
        //дані є поза областю її визначення(domain), як напр квадратний корень від'ємного числа

        if (exprUnderRoot < 0)
        {
            throw std::domain_error(" !Значення під коренем від'ємне, трикутник не існує ");
        }
        return 0.5 * std::sqrt(exprUnderRoot);
    }

    case 'b': {
        //mb = 0.5 * sqrt(2*a^2 + 2*c^2 - b^2)
        double exprUnderRoot = 2.0 * a * a + 2.0 * c * c - b * b;
        if (exprUnderRoot < 0) {
            throw std::domain_error(" !Значення під коренем від'ємне, трикутник не існує ");
        }
        return 0.5 * std::sqrt(exprUnderRoot);
    }

    case 'c': {
        //mc = 0.5 * sqrt(2*a^2 + 2*b^2 - c^2)
        double exprUnderRoot = 2.0 * a * a + 2.0 * b * b - c * c;
        if (exprUnderRoot < 0) {
            throw std::domain_error(" !Значення під коренем від'ємне, трикутник не існує ");
        }
        return 0.5 * std::sqrt(exprUnderRoot);
    }

    default:
        // Виняток std::invalid_argument залишається для некоректного ідентифікатора сторони.
        throw std::invalid_argument("передано невірну сторону, очікується a, b або c ");
    }
}

//функція для обчислення за довільною стороною трикутника паралельної їй середньої лінію
//середня лінія трикутника яка з'єднує середини двох сторін, || третій стороні та =1/2 цієї сторони (основи)

double Triangle::calculateMidline(char side) const
{
    switch (std::tolower(side)) //tolower() для забезпечення регістронезалежності
    {
    case 'a':
        return a / 2.0;
    case 'b':
        return b / 2.0;
    case 'c':
        return c / 2.0;
    default:
        throw std::invalid_argument(" передано невірну сторону, очікується a, b або c ");
    }
}

// Базове виведення інформації
void Triangle::printInfo() const {
    std::cout << "   Сторони  a = " << a << ", b = " << b << ", c = " << c << std::endl;
    std::cout << "   Периметр = " << getPerimeter() << std::endl;
    std::cout << "   Площа = " << getArea() << std::endl;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////


//обчислення сторін за вершинами
void TriangleByVertices::calcSides() {
    a = dist(v2, v3); // Сторона a протилежна v1
    b = dist(v1, v3); // Сторона b протилежна v2
    c = dist(v1, v2); // Сторона c протилежна v3

    if (!checkTriangleInequality()) {
        throw std::invalid_argument("вершини = 0, трикутник вироджений");
    }
}

TriangleByVertices::TriangleByVertices(const Point& p1, const Point& p2, const Point& p3)
    : v1(p1), v2(p2), v3(p3)
{
    calcSides(); //ініціалізація сторін базового класу
}

//обчислення площі за координатами (Формула Гаусса)
//перевизначення (демонстрація поліморфізму), похідний клас використовує специфічну для нього формулу
double TriangleByVertices::getArea() const
{
    //формула Гаусса: S = 0.5 * |x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)|
    return 0.5 * std::abs(v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y));
}

//для виведення інформацііпро дані класу
void TriangleByVertices::printInfo() const
{
    std::cout << "   Трикутник за тьома вершинами  : v1(" << v1.x << "," << v1.y << "), v2("
        << v2.x << "," << v2.y << "), v3(" << v3.x << "," << v3.y << ")" << std::endl;
    Triangle::printInfo(); //виклик базової реалізації для сторін, периметра
}



//////////////////////////////////////////////////////////////////////////////////////////




///виклик базового конструктора; трикутник бути створений лише якщо він прямокутний
RightTriangle::RightTriangle(double side_a, double side_b, double side_c)
    : Triangle(side_a, side_b, side_c)
{
    // перевірка, чи трикутник є прямокутним
    if (!isRight())
    {
        // Помилка генерується, оскільки трикутник не відповідає інваріанту RightTriangle (не є прямокутним).
        throw std::invalid_argument("невірно задані сторони, прямокутний трикутник побудувати неможливо");
    }
}

//перевірка прямокутності
bool RightTriangle::isRight() const
//з vector: sides[2] завжди - гіпотенуза, sides[0] і sides[1] — катети, перевірка за один раз
{
    std::vector<double> sides = { a, b, c };
    //після sort() елементи у векторі sides завжди будуть розташовані за зростанням
    std::sort(sides.begin(), sides.end());

    //теорема Піфагора: катет1^2 + катет2^2 = гіпотенуза^2
    //EPSILON для коректного порівняння чисел з плаваючою комою.
    return std::abs(sides[0] * sides[0] + sides[1] * sides[1] - sides[2] * sides[2]) < EPSILON;
}

//обчислення радіуса вписаного кола 
double RightTriangle::calcInRad() const
{
    std::vector<double> sides = { a, b, c };
    std::sort(sides.begin(), sides.end());
    return (sides[0] + sides[1] - sides[2]) / 2.0;  //r = (катет1 + катет2 - гіпотенуза)/2
}

//обчислення радіуса описаного кола (
double RightTriangle::calcCircumRad() const
{
    std::vector<double> sides = { a, b, c };
    std::sort(sides.begin(), sides.end());
    return sides[2] / 2.0;  //R = гіпотенуза/2
}

void RightTriangle::printInfo() const {
    std::cout << "   Прямокутний Трикутник " << std::endl;
    Triangle::printInfo(); //виклик базового методу

    std::cout << "   Радіус вписаного кола r = " << calcInRad() << std::endl;
    std::cout << "   Радіус описаного кола R= " << calcCircumRad() << std::endl;
}