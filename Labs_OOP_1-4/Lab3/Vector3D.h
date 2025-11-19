#pragma once
#include <string> //для std::string (цей тип повертається toString(), яка оголошена тут)

//оголошення класу Vector3D
class Vector3D
{
    //закриті поля (по дефолту приватні)
    double x;  
    double y;  
    double z;  

public:

    void Init(double x, double y, double z);
    void Read();
    void Display() const;

    std::string toString() const;


    //додавання векторів
    Vector3D addVec3D(const Vector3D& vec) const;

    //віднімання векторів
    Vector3D subVec3D(const Vector3D& vec) const;

    //множення вектора на скаляр
    Vector3D multVec3DScalar(double scalar) const;

    //довжина вектора
    double lengthVec3D() const;

    //перевантаження оператора < для порівняння довжини векторів
    bool operator<(const Vector3D& vec) const;

    //скалярний добуток векторів (eng dot product), поверне скаляр
    double dotProduct(const Vector3D& vec) const;

    //порівняння векторів на рівність 
    bool equalsVec3D(const Vector3D& vec) const;

   
    //КОНСТРУКТОРИ 

    // 1
    //дефолтний конструктор
    Vector3D(); 

    //конструктор (з трьома параметрами по замовчуванню)
    //Vector3D(double x = 0.0, double y = 0.0, double z = 0.0); 
    //НЕ використовуємо оскільки викличе конфлікт з Vector3D(double x, double y, double z); і  Vector3D(); 
    
    // 2
    //конструктор (три аргумента без дефолтних значень)
    Vector3D(double x, double y, double z);


    //конструктор для випадку з усіма однаковими координатами у вигляді Vector3D(double value)
    //НЕ будемо використовувати оскільки може викликати КОНФЛІКТ з конструктором  Vector3D(double z);,
    //який теж приймає один параметр
    
    // 3
    //конструктор з лише одніїєю координатою z не за замовчуванням,  x,y = 0
    //explicit дозволяє уникнути неявного перетворення, напр. при передачі числа туди, де очікується вектор
    //саме тому що explicit забороняє неявні виклики даний конструктор НЕ КОНФЛІКТУЄ з дефолтним (викликом Vector3D v;))
    explicit Vector3D(double z);

    // 4
    //конструктор копіювання (для ініціалізації вже існуючим об'єктом)
    Vector3D(const Vector3D& vec);

    // 5
    //конструктор для демонстрації пріоритету ініціалізації
    Vector3D(bool demo);         


    //натомість конструктора з одним параметром для всіх координат Vector3D(double value); який 
    //КОНФЛІКТУЄ  з  explicit Vector3D(double z) через неоднозначність при викликах з одним аргументом )
    //викотрстаємо СТАТИЧНИЙ МЕТОД (потребує перед викликом створення об'єкт)
     //щоб створити вектор з однаковими координатами
    static Vector3D Vec3DEqualCoords(double value);
  
};
