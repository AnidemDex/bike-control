#include <BikeClass.h>
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

const int back_led[3] = {1, 2, 3};
const int front_led[3] = {4, 5, 6};
const int botonIzquierda = 7
const int botonDerecha = 8
const int botonCentro = 9
Bike bike(botonIzquierda, botonDerecha, botonCentro, front_led, back_led);

int buttonState = 0;
int lastButtonState = 0;

void setup() {
  bike.begin();

}

void loop() {
  if (bike.controlPinHasChanged())
  {
    if (bike.getControlState() == HIGH)
    {
      bike.turnOn(bike.frontLight);
      bike.turnOn(bike.backLight);
    }
    else
    {
      bike.turnOff(bike.frontLight);
      bike.turnOff(bike.frontRightLight);
      bike.turnOff(bike.frontLeftLight);

      bike.turnOff(bike.backLight);
      bike.turnOff(bike.backRightLight);
      bike.turnOff(bike.backLeftLight);
    }
  }

}
