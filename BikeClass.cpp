/*
BikeClass.cpp - Library for smart lighting in bikes

Created by David alias Dastmema(Candy), 2019
*/
#include "Arduino.h"
#include "BikeClass.h"
Bike::Bike(int lBrakePin, int rBrakePin, int controlPin, int frontLed[], int backLed[])
{
  
  
  _leftBrake = lBrakePin;
  _rightBrake = rBrakePin;
  _control = controlPin;

  for(int i=0;i<3;i++){
    _front[i] = frontLed[i];
  }

  frontLight = frontLed[1];
  frontLeftLight = frontLed[0];
  frontRightLight = frontLed[2];

  for(int i=0;i<3;i++){
    _back[i] = backLed[i];
  }

  backLight = backLed[1];
  backLeftLight = backLed[0];
  backRightLight = backLed[2];

  rightCanBlink = false;
  leftCanBlink = false;

  _leftLightState = LOW;
  _rightLightState = LOW;
  _lastReadState = LOW;

  _controlState = false;
  _leftBrakeState = false;
  _rightBrakeState = false;
  _lastControlState = false;
  _lastLeftBrakeState = false;
  _lastRightBrakeState = false;

  
}


void Bike::begin()
{
  Serial.println("Iniciando sistema de luces...");
  
  pinMode(_leftBrake, INPUT_PULLUP);
  pinMode(_rightBrake, INPUT_PULLUP);
  pinMode(_control, INPUT_PULLUP);
  
  for(int i=0;i<3;i++){
    pinMode(_front[i], OUTPUT);
    pinMode(_back[i], OUTPUT);
  }

  Serial.println("Sistema iniciado");
  Serial.println("-------[ Info ]--------");
  Serial.print("Frenos ->\n");
  Serial.print("    Derecho:\t" + String(_leftBrakeState) + " Pin " + String(_rightBrake) + "\n");
  Serial.print("    Izquierdo:\t" + String(_rightBrakeState) + " Pin " + String(_leftBrake) + "\n");
  Serial.print("Sistema Central ->\n");
  Serial.print("    Control:\t" + String(_controlState) + " Pin " + String(_control) +"\n");
}

void Bike::turnOn(int light)
{
  if (getControlState() == HIGH)
  {
    digitalWrite(light, HIGH);
  }
}

void Bike::turnOff(int light)
{
  digitalWrite(light, LOW);
}

void Bike::tryToBlink(long interval)
{
  unsigned long currentMillis = millis();
  
  if(currentMillis - _previousMillis >= interval)
  {
    _previousMillis = currentMillis;

    if(leftCanBlink)
    {
      if(_leftLightState == LOW)
      {
        _leftLightState == HIGH;
        turnOn(frontLeftLight);
        turnOn(backLeftLight);
      }
      else
      {
        _leftLightState == LOW;
        turnOff(frontLeftLight);
        turnOff(backLeftLight);
      }
    }

    if(rightCanBlink)
    {
      if(_rightLightState == LOW)
      {
        _rightLightState == HIGH;
        turnOn(frontRightLight);
        turnOn(backRightLight);
      }
      else
      {
        _rightLightState == LOW;
        turnOff(frontRightLight);
        turnOff(backRightLight);
      }
    }
  }


}

bool Bike::getControlState()
{
  Serial.println("Estado de control: " + String(_controlState));
  return _controlState;
}

bool Bike::controlStateHasChanged()
{
  int _readState = digitalRead(_control);

  if (_readState == LOW && _lastReadState == HIGH && millis() - _previousMillis > 200)
  {
    Serial.println("Boton de control presionado");
    
    if(_controlState == HIGH)
    {
      _controlState == LOW;
    }
    else
    {
      _controlState == HIGH;
    }

    _previousMillis = millis();
  }

  _lastReadState == _readState;

}

bool Bike::getLeftBrakeState()
{
  return _lastLeftBrakeState;
}

bool Bike::leftBrakeStateHasChanged()
{
  _leftBrakeState = digitalRead(_leftBrake) == HIGH;

  if (_leftBrakeState != _lastLeftBrakeState)
  {
    _lastLeftBrakeState = _leftBrakeState;
    return true;
  }
  else
  {
    _lastRightBrakeState = _leftBrakeState;
    return false;
  }
}

bool Bike::getRightBrakeState()
{
  return _lastRightBrakeState;
}

bool Bike::rightBrakeStateHasChanged()
{
  _rightBrakeState = digitalRead(_rightBrake) == HIGH;

  if (_rightBrakeState != _lastRightBrakeState)
  {
    _lastRightBrakeState = _rightBrakeState;
    return true;
  }
  else
  {
    _lastRightBrakeState = _rightBrakeState;
    return false;
  }
}
