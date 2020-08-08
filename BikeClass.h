/*
BikeClass.h - Library for smart lighting in bikes

Created by David alias Dastmema(Candy), 2019
*/

#ifndef BikeClass_h
#define BikeClass_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class Bike{
  public:
    Bike(int lBrakePin, int rBrakePin, int controlPin, int frontLed[], int backLed[]);

    void begin();
    void turnOn(int light);
    void turnOff(int light);
    void tryToBlink(long interval);

    bool controlStateHasChanged();
    bool getControlState();

    bool leftBrakeStateHasChanged();
    bool getLeftBrakeState();

    bool rightBrakeStateHasChanged();
    bool getRightBrakeState();

    bool leftCanBlink;
    bool rightCanBlink;

    int frontLight;
    int frontRightLight;
    int frontLeftLight;
    
    int backLight;
    int backLeftLight;
    int backRightLight;

  private:
    long _previousMillis;

    int _leftBrake;
    int _rightBrake;
    int _control;
    int _leftLightState;
    int _rightLightState;

    bool _controlState;
    bool _leftBrakeState;
    bool _rightBrakeState;

    bool _lastControlState;
    bool _lastLeftBrakeState;
    bool _lastRightBrakeState;

    /*
     * 0 -> Left
     * 1 -> Center
     * 2 -> Right
    */
    int _front[3];
    int _back[3];
};

#endif