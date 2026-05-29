#define PinPotenciometro A0
#define PinTemperatura A1
#define PinPIR A2
#define PinR 8
#define PinG 4
#define PinB 7

void setup()
  
{
  pinMode(PinR, OUTPUT);
  pinMode(PinG, OUTPUT);
  pinMode(PinB, OUTPUT);
}

void loop()
  
{
  int LecturaTemperatura = analogRead(PinTemperatura);
  float Voltaje = LecturaTemperatura * (5.0 / 1023.0);
  float Temperatura = (Voltaje - 0.5) * 100.0;
  
  int Potenciometro = map(analogRead(PinPotenciometro),0,1023,0,255);
  
  analogWrite(PinR,0);
  analogWrite(PinG,0);
  analogWrite(PinB,0);
  
  if(Potenciometro > 50 && Temperatura > 20)
  {
    if(digitalRead(PinPIR) == HIGH)
    {
     analogWrite(PinG,150);
     analogWrite(PinB,255);
    }
  }
}