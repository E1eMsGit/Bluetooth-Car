#include "Car.h"

Car::Car(int IN4,int IN3, int ENB, int IN2, int IN1, int ENA)
{
  // Заносим в переменные номера контактов для левых и правых моторов.
  motorL1_ = IN4;  motorL2_ = IN3;  inputL_ = ENB;
  motorR1_ = IN2;  motorR2_ = IN1;  inputR_ = ENA;
  // Переводим указанные порты в состояние вывода данных.
  pinMode (inputL_, OUTPUT);
  pinMode (motorL1_, OUTPUT);
  pinMode (motorL2_, OUTPUT);
  
  pinMode (inputR_, OUTPUT);
  pinMode (motorR1_, OUTPUT);
  pinMode (motorR2_, OUTPUT); 
}

void Car::setMotorsSpeed(int leftMotorSpeed, int rightMotorSpeed)
{
  // Задает ширину положительного фронта от 1 до 255.
  // Чем больше тем интенсивнее работает мотор.
  analogWrite(inputL_, leftMotorSpeed);
  analogWrite(inputR_, rightMotorSpeed);
}

// Движение вперед.
void Car::forward()
{
  digitalWrite (motorL1_, HIGH);
  digitalWrite (motorL2_, LOW);
  digitalWrite (motorR1_, HIGH);
  digitalWrite (motorR2_, LOW);
}

// Поворот налево с блокировкой левых колес.
void Car::forwardLeft()
{
  // Блокируем вращение левых колес.
  digitalWrite (motorL1_, LOW);
  digitalWrite (motorL2_, LOW);
  // Правые колеса вращаются.
  digitalWrite (motorR1_, HIGH);
  digitalWrite (motorR2_, LOW);
}

// Поворот направо с блокировкой правых колес.
void Car::forwardRight()
{
  // Левые колеса вращаются.
  digitalWrite (motorL1_, HIGH);
  digitalWrite (motorL2_, LOW);
  // Блокируем вращение правых колес.
  digitalWrite (motorR1_, LOW);
  digitalWrite (motorR2_, LOW);
}

// Поворот налево.
void Car::left()
{
  // Левые колеса вращаются назад.
  digitalWrite (motorL1_, LOW);
  digitalWrite (motorL2_, HIGH);
  // Правые колеса вращаются.
  digitalWrite (motorR1_, HIGH);
  digitalWrite (motorR2_, LOW);
}

// Поворот направо.
void Car::right()
{
  // Левые колеса вращаются.
  digitalWrite (motorL1_, HIGH);
  digitalWrite (motorL2_, LOW);
  // Правые колеса вращаются назад.
  digitalWrite (motorR1_, LOW);
  digitalWrite (motorR2_, HIGH);
}

// Движение назад.
void Car::backward()
{
  digitalWrite (motorL1_, LOW);
  digitalWrite (motorL2_, HIGH);
  digitalWrite (motorR1_, LOW);
  digitalWrite (motorR2_, HIGH);
}

// Движение назад с поворотом налево.
void Car::backwardLeft()
{
  digitalWrite (motorL1_, LOW);
  digitalWrite (motorL2_, LOW);
  digitalWrite (motorR1_, LOW);
  digitalWrite (motorR2_, HIGH);
}

// Движение назад с поворотом направо.
void Car::backwardRight()
{
  digitalWrite (motorL1_, LOW);
  digitalWrite (motorL2_, HIGH);
  digitalWrite (motorR1_, LOW);
  digitalWrite (motorR2_, LOW);
}

// Стоп.
void Car::stand()
{
  digitalWrite (motorL1_, LOW);
  digitalWrite (motorL2_, LOW);
  digitalWrite (motorR1_, LOW);
  digitalWrite (motorR2_, LOW);
}
