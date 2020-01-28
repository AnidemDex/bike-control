
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
int led[6] = {1, 2, 3, 4, 5, 6};
Bike bike(7, 8, 9, led);
void setup() {
  bike.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

}
