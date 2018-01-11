# Project Lights, Camera, Hue!

I recently installed a few Philips Hue Lightbulbs in my home and wanted to make an application that would allow me to control them with my WeMos D1 Mini. 

## Project Goals
* Make an input to turn on/off the four lights in my home => switch
* Make an input to control color => potentiometer(s)
    * hue and saturation OR
    * xy in the CIE color space OR
    * ct the Mired Color temperature
* Make an input to control brightness => potentiometer
* Setup some sensor based control (temperature, PIR, light, sound, etc)
* Output data to an LCD or OLED screen to monitor light values

## Files
#### hue_slide.ino
Current project development file.
* Opens a http connection to my hue hub on my local network.
* When a physical slide switch is moved from "on" to "off" or vice versa, it makes a PUT request to change my living room light.

#### hue_lights.ino
* Opens a http connection to my hue hub on my local network.
* Checks every 30 seconds to see if my living room light is on.
* If it is on, it turns it off. 

#### switch_led_test.ino
* Toggles a LED using a slide switch.


## Tips & Hints
* To get the Hub's local IP:
    1. Open the Hue app on your phone.
    2. Click the settings icon (top right on Android)
    3. Click 'Hue bridges' (should be first item on list)
    4. Assuming you have one router and didn't rename it, click the info icon to the right on the entry 'Philips hue'.
    5. The IP address will be listed along with a few other potentially useful value.
    
* Arduno to D1 pin mapping.
```
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

static const uint8_t LED_BUILTIN = 2;
static const uint8_t BUILTIN_LED = 2;

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t RX   = 3;
static const uint8_t TX = 1;
```