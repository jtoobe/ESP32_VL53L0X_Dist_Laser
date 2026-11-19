/*
Ejemplo modificado de la libreria Adafruit VL53L0X
*/



#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  // while (! Serial) {
  //   delay(1);
  // }

  Serial.println("Iniciando Sensor");

  // en lox.begin() se puede indicar la direccion hexa de cada sensor conectado, en este ejemplo 0x30 
  // se debera crear una instancia para cada sensor con su direccion

  if (!lox.begin(0x30)) {
    Serial.println(F("Fallo al iniciar VL53L0X (conexiones?)"));
    while(1);
  }

  // start continuous ranging
  lox.startRangeContinuous();
}

void loop() {
  if (lox.isRangeComplete()) {
    Serial.print("Distancia in mm: ");
    Serial.println(lox.readRange());
  }
}
