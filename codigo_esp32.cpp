#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//sensor DS18B20
#define ONE_WIRE_BUS 4

//LCD I2C
#define SDA_PIN 19
#define SCL_PIN 22

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 20, 4);  //LCD I2C e tamanho 20x4

void setup() {
  Serial.begin(9600);
  
  //inicialização do LCD
  lcd.init();
  lcd.backlight();

  //inicialização do sensor DS18B20
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();  //solicita temperatura
  
  float tempC = sensors.getTempCByIndex(0);  //le temperatura em graus Celsius

  if (tempC != DEVICE_DISCONNECTED_C) {  //verifica leitura
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura:");
    lcd.setCursor(0, 1);
    lcd.print(tempC, 1);  //imprime a temp uma casa decimal
    lcd.print(" C");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro ao ler");
    lcd.setCursor(0, 1);
    lcd.print("o sensor");
  }

  delay(1000);  //delay 1 segundo
  
}
