#include "BikeClass.h"
/*
 * No olvides importar BikeClass.zip en el programa
 * 
 * Link al esquematico: https://easyeda.com/dastmema.0/Candy_LBC
 * Configurar pines
 * 2 pines son sensores de frenos
 * 1 pin es un boton
 * 6 pines son salidas digitales
 * 
 * Al presionar cualquiera de los frenos, un pin digital se activa
*/

int back_led[3] = {2, 3, 4};
int front_led[3] = {5, 6, 7};
int botonIzquierda = 8;
int botonDerecha = 9;
int botonCentro = 10;
Bike bike(botonIzquierda, botonDerecha, botonCentro, front_led, back_led);

int buttonState = 0;
int lastButtonState = 0;

void setup() {
  Serial.begin(9600);
  while(!Serial); //Linea añadida al usar un arduino Leonardo para pruebas
  bike.begin();

}

void loop() {
  bike.controlStateHasChanged();
  
  if (bike.getControlState() == HIGH)
  {
    bike.turnOn(bike.frontLight);
    bike.turnOn(bike.backLight);
  }
  else
  {
    bike.turnOff(bike.frontLight);
    bike.turnOff(bike.backLight);
  }

  bike.leftBrakeStateHasChanged();
  bike.rightBrakeStateHasChanged();

  if (bike.getLeftBrakeState() == HIGH)
  {
    bike.leftCanBlink = true;
  }
  else{
    bike.leftCanBlink = false;
  }

  if (bike.getRightBrakeState() == HIGH)
  {
    bike.rightCanBlink = true;
  }
  else
  {
    bike.rightCanBlink = false;
  }

  bike.tryToBlink(1000);

}
