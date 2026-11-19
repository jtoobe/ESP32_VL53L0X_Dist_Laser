// No esta probado !!!! */



#include <Wire.h>
#include "Adafruit_VL53L0X.h"

// Nuevas direcciones I2C para los sensores
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32

// Pines XSHUT conectados al ESP32
#define SHT_LOX1 25
#define SHT_LOX2 26
#define SHT_LOX3 27

// Objetos para cada sensor
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

// Estructuras para guardar las mediciones
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

void setID() {
  // 1. Apagar todos los sensores
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  delay(10);

  // 2. Encender todos brevemente para resetearlos
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  // 3. Activar Sensor 1 y mantener apagados 2 y 3
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Fallo al iniciar VL53L0X #1"));
    while(1);
  }
  delay(10);

  // 4. Activar Sensor 2 (el 1 ya tiene su nueva dirección)
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Fallo al iniciar VL53L0X #2"));
    while(1);
  }
  delay(10);

  // 5. Activar Sensor 3
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Fallo al iniciar VL53L0X #3"));
    while(1);
  }
}

void read_three_sensors() {
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);
  lox3.rangingTest(&measure3, false);

  // Imprimir Sensor 1
  Serial.print(F("S1: "));
  if(measure1.RangeStatus != 4) { Serial.print(measure1.RangeMilliMeter); Serial.print("mm "); } 
  else { Serial.print("Fuera de rango "); }

  // Imprimir Sensor 2
  Serial.print(F(" | S2: "));
  if(measure2.RangeStatus != 4) { Serial.print(measure2.RangeMilliMeter); Serial.print("mm "); } 
  else { Serial.print("Fuera de rango "); }

  // Imprimir Sensor 3
  Serial.print(F(" | S3: "));
  if(measure3.RangeStatus != 4) { Serial.println(measure3.RangeMilliMeter); } 
  else { Serial.println("Fuera de rango"); }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Inicia I2C en GPIO 21 (SDA) y GPIO 22 (SCL)

  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);

  Serial.println(F("Iniciando sensores..."));
  setID();
  Serial.println(F("Sensores listos!"));
}

void loop() {
  read_three_sensors();
  delay(100);
}
