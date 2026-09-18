#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define SERVO_PIN A0
#define BOTON 6
#define BUZZER 5
#define LED_VERDE 2
#define LED_AZUL 4
#define LED_ROJO 3
#define POT A1
#define TEMPERATURA A2

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define Gb3 208
#define C4 262
#define F3 175
#define A3 220

const int midi1[10][3] = {
  {Gb3, 115, 0},
  {C4, 115, 0},
  {Gb3, 115, 0},
  {F3, 115, 0},
  {A3, 115, 115},
  {Gb3, 115, 0},
  {C4, 115, 0},
  {Gb3, 115, 0},
  {F3, 115, 0},
  {A3, 115, 0}
};

void playMidi(int pin, const int notes[][3], int len) {

  for (int i = 0; i < len; i++) {

    tone(pin, notes[i][0]);

    delay(notes[i][1]);

    noTone(pin);

    delay(notes[i][2]);
  }
}

void setup() {

  servo.attach(SERVO_PIN);

  pinMode(BOTON, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);

  lcd.init();
  lcd.backlight();

  servo.write(0);

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_ROJO, LOW);

  pantallaInicial();
}

void loop() {

  int valorTemp = analogRead(TEMPERATURA);

  float voltaje = valorTemp * (5.0 / 1023.0);

  float temperatura = (voltaje - 0.5) * 100.0;

  if (temperatura > 40) {

    digitalWrite(LED_ROJO, HIGH);
    digitalWrite(LED_AZUL, LOW);

  } else {

    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_AZUL, HIGH);
  }

  if (digitalRead(BOTON) == LOW) {

    delay(50);

    if (digitalRead(BOTON) == LOW) {

      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_AZUL, LOW);

      for (int vuelta = 0; vuelta < 10; vuelta++) {

        int valorPot = analogRead(POT);

        int porcentaje = map(
          valorPot,
          0,
          1023,
          0,
          100
        );

        int espera;

        if (porcentaje < 25) {

          espera = 2000;

        } else if (porcentaje <= 50) {

          espera = 5000;

        } else {

          espera = 8000;
        }
      }
    }
  }
}

