/*
BikeClass.cpp - Library for smart lighting in bikes

Created by David alias Dastmema(Candy), 2019
*/
#include "Arduino.h"
#include "BikeClass.h"
Bike::Bike(int lBrakePin, int rBrakePin, int controlPin, int frontLed[], int backLed[])
{

  int bounceTime = 250;
  
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
  _lastReadState = HIGH;
  _lastLeftState = HIGH;
  _lastRightState = HIGH;

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
    digitalWrite(light, HIGH);
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
        _leftLightState = HIGH;
        turnOn(frontLeftLight);
        turnOn(backLeftLight);
        Serial.println("Izquiera encendido");
      }
      else
      {
        _leftLightState = LOW;
        turnOff(frontLeftLight);
        turnOff(backLeftLight);
        Serial.println("Izquiera apagado");
      }
    }
    else
    {
      _leftLightState = LOW;
      turnOff(frontLeftLight);
      turnOff(backLeftLight);
      Serial.println("Izquiera apagado");      
    }

    if(rightCanBlink)
    {
      if(_rightLightState == LOW)
      {
        _rightLightState = HIGH;
        turnOn(frontRightLight);
        turnOn(backRightLight);
        Serial.println("Derecha encendido");
      }
      else
      {
        _rightLightState = LOW;
        turnOff(frontRightLight);
        turnOff(backRightLight);
        Serial.println("Derecha apagado");
      }
    }
    else
    {
      _rightLightState = LOW;
      turnOff(frontRightLight);
      turnOff(backRightLight);
      Serial.println("Derecha apagado");
    }
  }


}

bool Bike::getControlState()
{
  if(_lastControlState != _controlState)
  {
    Serial.print("Estado de control: ");
    Serial.println(String(_controlState));
    _lastControlState = _controlState;
  }
  return _controlState;
}

bool Bike::controlStateHasChanged()
{
  int _readState = digitalRead(_control);

  if (_readState == LOW && _lastReadState == HIGH && millis() - _previousMillis > bounceTime)
  {
    Serial.println("Boton de control presionado");
    _lastControlState = _controlState;
    
    if(_controlState == true)
    {
      _controlState = false;
    }
    else
    {
      _controlState = true;
    }

    _previousMillis = millis();
  }

  _lastReadState = _readState;

}

bool Bike::getLeftBrakeState()
{
  if(_lastLeftBrakeState != _leftBrakeState)
  {
    Serial.print("Estado de freno izquierdo: ");
    Serial.println(String(_leftBrakeState));
    _lastLeftBrakeState = _leftBrakeState;
  }
  return _leftBrakeState;
}

bool Bike::leftBrakeStateHasChanged()
{
  int _readState = digitalRead(_leftBrake);

  if (_readState == LOW && _lastLeftState == HIGH && millis() - _previousMillis > bounceTime)
  {
    Serial.println("Boton de control presionado");
    _lastLeftBrakeState = _leftBrakeState;
    
    if(_leftBrakeState == true)
    {
      _leftBrakeState = false;
    }
    else
    {
      _leftBrakeState = true;
    }

    _previousMillis = millis();
  }

  _lastLeftState = _readState;
  
}

bool Bike::getRightBrakeState()
{
  if(_lastRightBrakeState != _rightBrakeState)
  {
    Serial.print("Estado de freno derecho: ");
    Serial.println(String(_rightBrakeState));
    _lastRightBrakeState = _rightBrakeState;
  }
  return _rightBrakeState;
}

bool Bike::rightBrakeStateHasChanged()
{
  int _readState = digitalRead(_rightBrake);

  if (_readState == LOW && _lastRightState == HIGH && millis() - _previousMillis > bounceTime)
  {
    Serial.println("Boton de control presionado");
    _lastRightBrakeState = _rightBrakeState;
    
    if(_rightBrakeState == true)
    {
      _rightBrakeState = false;
    }
    else
    {
      _rightBrakeState = true;
    }

    _previousMillis = millis();
  }

  _lastRightState = _readState;
  
}
