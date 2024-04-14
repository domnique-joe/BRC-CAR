#include <AFMotor.h>

#define lightsPin  A2
#define lightPin   A3
#define light_BL   A4
#define horn_Buzz  A5

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int command;
int speedCar = 255;
boolean lightState = false;
boolean horn = false;
boolean l = false;

void setup() {
    pinMode(lightPin, OUTPUT);
    pinMode(lightsPin, OUTPUT);
    pinMode(light_BL, OUTPUT);
    pinMode(horn_Buzz, OUTPUT);

    Serial.begin(9600);
}

void forward() {
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
    motor1.setSpeed(speedCar);
    motor2.setSpeed(speedCar);
    motor3.setSpeed(speedCar);
    motor4.setSpeed(speedCar);
}

void backward() {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    motor1.setSpeed(speedCar);
    motor2.setSpeed(speedCar);
    motor3.setSpeed(speedCar);
    motor4.setSpeed(speedCar);
}

void left() {
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    motor1.setSpeed(speedCar);
    motor4.setSpeed(speedCar);
}

void right() {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
    motor2.setSpeed(speedCar);
    motor3.setSpeed(speedCar);
}
void Dleft() {
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    motor1.setSpeed(speedCar);
    motor4.setSpeed(speedCar);
}
void Dright() {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
    motor2.setSpeed(speedCar);
    motor3.setSpeed(speedCar);
}    
void Stop() {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}

void loop() {
    if (Serial.available() > 0) {
        char receivedChar = Serial.read();
        
        // Check if the received character is not a newline or carriage return
        if (receivedChar != '\n' && receivedChar != '\r') {
            command = receivedChar;
            Stop();       

            if (l) {
                digitalWrite(lightPin, HIGH);
                digitalWrite(lightsPin, HIGH);
            }
            if (!l) {
                digitalWrite(lightPin, LOW);
                digitalWrite(lightsPin, LOW);
            }
            if (horn) {
                digitalWrite(horn_Buzz, HIGH);
            }
            if (!horn) {
                digitalWrite(horn_Buzz, LOW);
            }

            switch (command) {
                case 'F': forward(); break;
                case 'B': backward(); break;
                case 'L': left(); break;
                case 'R': right(); break;
                case 'I': Dright(); break;
                case 'G': Dleft(); break;
                case 'S': Stop(); break;
                case '0': speedCar = 0; break;
                case '1': speedCar = 75; break;
                case '2': speedCar = 100; break;
                case '3': speedCar = 110; break;
                case '4': speedCar = 125; break;
                case '5': speedCar = 140; break;
                case '6': speedCar = 150; break;
                case '7': speedCar = 175; break;
                case '8': speedCar = 200; break;
                case '9': speedCar = 225; break;
                case 'q': speedCar = 255; break;
                case 'W': l = true; break;
                case 'w': l = false; break;
                case 'V': horn = true; break;
                case 'v': horn = false; break;
            }
        }
    }
}
