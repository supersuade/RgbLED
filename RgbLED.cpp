#include "RgbLED.h"

//PUBLIC
RgbLED::RgbLED(int redPin, int greenPin, int bluePin, int cspeed, int maxBrightness)
{
    //set up private variables
    _redPin = redPin;
    _greenPin = greenPin;
    _bluePin = bluePin;
    _cspeed = cspeed;
    _cstep = .001;
    _pspeed = 150;
    _ledBrightness = 255;
    _maxLedBrightness = maxBrightness;
}
void RgbLED::setCSpeed(int cspeed){
    _cspeed = cspeed;
}
void RgbLED::setColor(int red, int green, int blue){
    _red = red;
    _green = green;
    _blue = blue;
}
void RgbLED::updateLED(){
    //run updater here
    _pulseSineIn = stepColor(_pulseSineIn, _pspeed);
    _ledBrightness = getSineOut(_pulseSineIn,0);
    _redSineIn = stepColor(_redSineIn, _cspeed);
    _red = getSineOut(_redSineIn,0);
    _greenSineIn = stepColor(_greenSineIn, _cspeed);
    _green = getSineOut(_greenSineIn,2);
    _blueSineIn = stepColor(_blueSineIn, _cspeed);
    _blue = getSineOut(_blueSineIn,4);
    writeColors();
}
void RgbLED::setWhite(){
    setColor(255,255,255);
}
void RgbLED::setLowerThresholds(int redThreshold, int greenThreshold, int blueThreshold){
    _redThreshold = redThreshold;
    _greenThreshold = greenThreshold;
    _blueThreshold = blueThreshold;
}
int RgbLED::getCSpeed(){
    return _cspeed;
}
void RgbLED::setBrightness(int brightness){
    if(brightness>255){
        brightness = 255;
    }else if(brightness<0){
        brightness = 0;
    }
    _ledBrightness = brightness;
}
void RgbLED::setPulseSpeed(int pspeed){
    if(pspeed>255){
        pspeed = 255;
    }else if(pspeed<0){
        pspeed = 0;
    }
    _pspeed = pspeed;
}
//private
float RgbLED::stepColor(float in, int speed){
    in += speed/100000.0;
    if(in > (0.5*PI + 2.0*PI)){ //an entire waveform after full intensity
        in = 0.5*PI; //back to "beginning
    }
    return in;
}
float RgbLED::getSineOut(float in, int phase){
    //eventually, make thresholds apply here.
    //but for now,
    float range = 255.0/2;
    float offset = 255.0/2;
    float out = sin(in + phase) * range + offset;
    return out;
}
void RgbLED::writeColors(){
    int red = applyModifiers(_red);
    int green = applyModifiers(_green);
    int blue = applyModifiers(_blue);
    analogWrite(_redPin, red);
    //Serial.print("writing ");Serial.print(red);Serial.println(" as Red");
    analogWrite(_greenPin, green);
    //Serial.print("writing ");Serial.print(green);Serial.println(" as Green");
    analogWrite(_bluePin, blue);
    //Serial.print("writing ");Serial.print(blue);Serial.println(" as Blue");
}
int RgbLED::applyModifiers(float intensity){
    //Serial.print("Adjusting ");Serial.print(intensity);
    intensity = writeColorSanityCheck(intensity);
    intensity = intensity * (_ledBrightness / 255.0);
    //map intensity over scale ove max brightness
    intensity = intensity * (_maxLedBrightness / 255.0);
    //Serial.print(" to ");Serial.println(intensity);
    //Serial.print("_ledBrightness = ");Serial.println(_ledBrightness);
    return int(intensity);
}
float RgbLED::writeColorSanityCheck(float intensity){
    if(intensity > 255){
        return 255;
    }
    if(intensity<0){
        return 0;
    }
    return intensity;
}
