#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
float Tobj=26.0;
LiquidCrystal_I2C lcd(0x27,16,2);  //
void setup() {
  // Inicializar el LCD
  pinMode(5,INPUT_PULLUP); //boton rojo
  pinMode(6,INPUT_PULLUP); //boton azul
  pinMode(2,OUTPUT); //Led Rojo
  pinMode(3,OUTPUT); //Led blanco
  pinMode(4,OUTPUT); //Led Verde
  pinMode(9,OUTPUT); //Bloque calentador
  Wire.begin();
  lcd.init();
  lcd.begin(16,2);
  //Encender la luz de fondo.
  lcd.backlight();
  lcd.setCursor(0, 0);
  // Escribimos el Mensaje en el LCD.
  lcd.print("TObjetivo: ");
  lcd.setCursor(11, 0);
  lcd.print(Tobj);
  delay(20);
  // Escribimos el Mensaje en el LCD.
  lcd.setCursor(0, 1);
  lcd.print("Tactual:   ");
  digitalWrite(4,HIGH);
}

void loop() {
  if(digitalRead(5)==LOW){ 
    //Disminuir Tobjetivo con boton rojo
    Tobj=Tobj-0.1;
    lcd.setCursor(11, 0);
    lcd.print(Tobj);
    delay(20);
    }
  if(digitalRead(6)==LOW){
    //Aumentar Tobjetivo con boton rojo
    Tobj=Tobj+0.1;
    lcd.setCursor(11, 0);
    lcd.print(Tobj);
    delay(20);
    }
  //Calculo de Temperatura Actual
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15; //Tactual
  lcd.setCursor(11, 1);
  lcd.print(T);
  delay(50);
  if(Tobj<T){
    //Si esta mas helado que Tobjetivo, calentar
    digitalWrite(9,HIGH);
    digitalWrite(2,LOW);
    delay(200);
    }
  else{
    //Si esta mas caliente que Tobjetivo, dejar de calentar
    digitalWrite(9,LOW);
    digitalWrite(2,HIGH);
    delay(200);
    }
}
