/*
  RgbLED.h - Contains object for simple RGBLED
  LED can pulse, and cycle through colors
  Mike Barbee 2014 GPL v2
*/

#ifndef RGBLED_H
#define RGBLED_H
#include "Arduino.h"

class RgbLED
{
    public:
        RgbLED(int redPin, int greenPin, int bluePin, int cspeed, int maxBrightness);
        void setCSpeed(int cspeed);
        void setColor(int red, int green, int blue);
        void updateLED();
        void setWhite();
        void setLowerThresholds(int redThreshold, int greenThreshold, int blueThreshold);
        int getCSpeed();
        void setBrightness(int brightness);
        void setPulseSpeed(int pspeed);
    protected:
    private:
        float stepColor(float in, int speed);
        float getSineOut(float in, int phase);
        void writeColors();
        int applyModifiers(float intensity);
        float writeColorSanityCheck(float intensity);

        float _red;
        int _redPin;
        float _redSineIn;
        int _redThreshold;
        float _green;
        int _greenPin;
        float _greenSineIn;
        int _greenThreshold;
        float _blue;
        int _bluePin;
        float _blueSineIn;
        int _blueThreshold;
        int _cspeed;
        float _cstep;
        int _ledBrightness;
        int _pspeed;
        float _pulseSineIn;
        float _pulse;
        int _maxLedBrightness;
};

#endif // RGBLED_H
