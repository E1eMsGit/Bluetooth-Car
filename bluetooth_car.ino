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

char rcvData;
int horizontalServoValue = 70;
int verticalServoValue = 70;
int motorSpeed = 175;

void setup() {
    Serial.begin(115200);
    horizontalServo.attach(HORIZONTAL_SERVO);
    verticalServo.attach(VERTICAL_SERVO);
    
    horizontalServo.write(horizontalServoValue);
    verticalServo.write(verticalServoValue);
    car.setMotorsSpeed(motorSpeed, motorSpeed);
}

void loop() {
    if(Serial.available()) {
        delay(10);
        rcvData = Serial.read(); 
        
        //Сравниевает полученное значение
        switch (rcvData) {
            //Ничего не нажато. Стоит.
            case '0': car.stand(); break;
            //Стрелка вверх. Едет вперед.
            case '1': car.forward(); break;
             //Стрелка вниз. Едет назад.
            case '2': car.backward(); break;
            //Стрелка влево. Поворачивает налево.
            case '3': car.forwardLeft(); break;
            //Стрелка вправо. Поворачивает направо.
            case '4': car.forwardRight(); break;
            //Select. Уменьшает скорость вращения моторов.
            case '5': regulMotorSpeed(-25); break;
            //Start. Увеличивает скорость вращения моторов.
            case '6': regulMotorSpeed(25); break;
            //Треугольник. Вращает севро вправо.
            case '7': horizontalServoSpin(5); break;
            //Квадрат. Вращает севро влево.
            case '8': horizontalServoSpin(-5); break;
            //Крестик. Вращает севро вниз.
            case '9': verticalServoSpin(5); break;
            //Кружок. Вращает севро вверх.
            case 'A': verticalServoSpin(-5); break;  
        }    
    }                                     
}

//************************ ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ ************************
// Вращает горизонтальный серво.
void horizontalServoSpin(int value) {
    horizontalServoValue += value;
    if (horizontalServoValue > 150) horizontalServoValue = 150;
    else if (horizontalServoValue < 10) horizontalServoValue = 10;
    horizontalServo.write(horizontalServoValue);
}

// Вращает вертикальный серво.
void verticalServoSpin(int value) {
    verticalServoValue += value;
    if (verticalServoValue > 90) verticalServoValue = 90;
    else if (verticalServoValue < 30) verticalServoValue = 30;  
    verticalServo.write(verticalServoValue);
}

// Регулирует скорость вращения моторов.
void regulMotorSpeed(int value) {
    motorSpeed += value;
    if (motorSpeed > 250) motorSpeed = 250; 
    else if (motorSpeed < 100) motorSpeed = 100;
    car.setMotorsSpeed(motorSpeed, motorSpeed); 
}
