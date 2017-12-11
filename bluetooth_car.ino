/*********************************************************************
 * Машинка с управлением по Bluetooth
 * Платформа: Arduino UNO
 * Управляющее приложение: Arduino BT Joystick (Android)
 *                    
 * Подключенные модули: Bluetooth модуль HC-06 - пин: 1, 2
 *                      Сервопривод - пин: 11
 *                      Сервопривод - пин: 9                 
 *                      Драйвер моторов (IN4, IN3, ENB, IN2, IN1, ENA) - пин: 7, 8, 5, 3, 4, 6                   
 *                      
 * Управление (код кнопки): Ничего не нажато(0) - Стоит
 *                          Стрелка вверх(1)    - Едет вперед
 *                          Стрелка вниз(2)     - Едет назад
 *                          Стрелака влево(3)   - Поворачивает налево
 *                          Стрелка вправо(4)   - Поворачивает направо
 *                          Кнопка Select(5)    - Уменьшает скорость вращения моторов
 *                          Кнопка Start(6)     - Увеличивает скорость вращения моторов
 *                          Кнопка Треугольник(7) - Вращает севро вправо
 *                          Кнопка Квадрат(8)     - Вращает севро влево
 *                          Кнопка Крестик(9)     - Вращает севро вниз
 *                          Кнопка Кружок(А)      - Вращает севро вверх
 * 
 *********************************************************************/
#include "Car.h"
#include <Servo.h>

#define HORIZONTAL_SERVO   A1
#define VERTICAL_SERVO   A0

Car car(7, 8, 5, 3, 4, 6); // Объект класса Car (пины к которым подключен драйвер моторов (IN4, IN3, ENB, IN2, IN1, ENA)).
Servo horizontalServo;
Servo verticalServo; 


char btData; //Переменная для приема данных по bluetooth.
int horizontalServoValue = 70;
int verticalServoValue = 70;
int motorSpeed = 175;

void setup(){
  Serial.begin(115200);
  horizontalServo.attach(HORIZONTAL_SERVO);
  verticalServo.attach(VERTICAL_SERVO);

  horizontalServo.write(horizontalServoValue);
  verticalServo.write(verticalServoValue);

  car.setMotorsSpeed(motorSpeed, motorSpeed);
}

void loop(){
  if(Serial.available()){   
    delay(10);
    btData = Serial.read(); 
    
    //Сравниевает полученное значение
    switch(btData){
      case '0': //Ничего не нажато. Стоит.
        car.stand();
        break;
      case '1': //Стрелка вверх. Едет вперед.
        car.forward();
        break;
      case '2': //Стрелка вниз. Едет назад.
        car.backward();
        break;
      case '3': //Стрелка влево. Поворачивает налево.
        car.forwardLeft();
        break;
      case '4': //Стрелка вправо. Поворачивает направо.
        car.forwardRight();
        break;
      case '5': //Select. Уменьшает скорость вращения моторов.
        regulMotorSpeed('-');
        break;
      case '6': //Start. Увеличивает скорость вращения моторов.
        regulMotorSpeed('+');
        break;
      case '7': //Треугольник. Вращает севро вправо.
        horizontalServoSpin('+');
        break;
      case '8': //Квадрат. Вращает севро влево.
        horizontalServoSpin('-');
        break;
      case '9': //Крестик. Вращает севро вниз.
        verticalServoSpin('+');
        break;
      case 'A'://Кружок. Вращает севро вверх.
        verticalServoSpin('-');
        break;  
    }    
  }                                     
}

//************************ ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ ************************
// Вращает горизонтальный серво.
void horizontalServoSpin(char operation){
  if (operation == '+'){
    if (horizontalServoValue > 150){
      horizontalServoValue = 150;
    }
    else{
      horizontalServoValue += 5;
      horizontalServo.write(horizontalServoValue);
    }
  } 
  else if (operation == '-'){
    if (horizontalServoValue < 10){
      horizontalServoValue = 10;
    }
    else{
      horizontalServoValue -= 5;
      horizontalServo.write(horizontalServoValue); 
    }
  }
}

// Вращает вертикальный серво.
void verticalServoSpin(char operation){
  if (operation == '+'){
    if (verticalServoValue > 90){
      verticalServoValue = 90;
    }
    else{
      verticalServoValue += 5;
      verticalServo.write(verticalServoValue);
    }
  } 
  else if (operation == '-'){
    if (verticalServoValue < 30){
      verticalServoValue = 30;  
    }
    else{
      verticalServoValue -= 5;
      verticalServo.write(verticalServoValue); 
    }
  }
}

// Регулирует скорость вращения моторов.
void regulMotorSpeed(char operation){
  if (operation == '+'){
    if (motorSpeed > 250){
      motorSpeed = 250;
      car.setMotorsSpeed(motorSpeed, motorSpeed);  
    }
    else{
      motorSpeed += 25;
      car.setMotorsSpeed(motorSpeed, motorSpeed);
    }
  } 
  else if (operation == '-'){
    if (motorSpeed < 100){
      motorSpeed = 100;
      car.setMotorsSpeed(motorSpeed, motorSpeed);
    }
    else{
      motorSpeed -= 25;
      car.setMotorsSpeed(motorSpeed, motorSpeed); 
    }
  }
}
