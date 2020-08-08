/*
BikeClass.cpp - Library for smart lighting in bikes

Created by David alias Dastmema(Candy), 2019
*/
#include "Arduino.h"
#include "BikeClass.h"
#include "SoftwareSerial.h"
Bike::Bike(int lBrakePin, int rBrakePin, int controlPin, int frontLed[], int backLed[])
{
  Serial.println("Iniciando sistema de bicicleta...");
  
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

  _controlState = false;
  _leftBrakeState = false;
  _rightBrakeState = false;
  _lastControlState = false;
  _lastLeftBrakeState = false;
  _lastRightBrakeState = false;

  Serial.println("Sistema iniciado :D");
  Serial.println("-------[ Info ]--------");
  Serial.print("Frenos ->\n");
  Serial.print("    Derecho: " + String(_leftBrakeState) + "Pin " + String(_rightBrake) + "\n");
  Serial.print("    Izquierdo: " + String(_rightBrakeState) + "Pin " + String(_leftBrake) + "\n");
  Serial.print("Sistema Central ->\n");
  Serial.print("    Control: " + String(_controlState) + "Pin " + String(_control) +"\n");
}


void Bike::begin()
{
  pinMode(_leftBrake, INPUT);
  pinMode(_rightBrake, INPUT);
  pinMode(_control, INPUT);
  
  for(int i=0;i<3;i++){
    pinMode(_front[i], OUTPUT);
    pinMode(_back[i], OUTPUT);
  }
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
  return _lastControlState;
}

bool Bike::controlStateHasChanged()
{
  _controlState = digitalRead(_control) == HIGH;

  if (_controlState != _lastControlState)
  {
    _lastControlState = _controlState;
    return true;
  }
  else
  {
    _lastControlState = _controlState;
    return false;
  }
  
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
