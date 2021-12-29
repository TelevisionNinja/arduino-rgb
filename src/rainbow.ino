/*
 * for smooth no blink
 *    wait = 10
 *    fade = 5
 *    
 * for blink
 *    wait = 150
 *    fade = 25
 */

int wait = 10, //this is how long the current color will be displayed
    fadeAmount = 5, //this is how much the brightness of the leds fade each interval
    maxBrightness = 255, //this is the max brightness of the leds
    minBrightness = 0, //this is the min brightness of the leds

    // set up these vars

    R = 1, //this is the pin number of red
    G = 2, //this is the pin number of green
    B = 3, //this is the pin number of blue

    // private vars

    brightness = minBrightness, //this is the starting brightness of the led to be manipulated
    manipulatedLED = 0, //this is the led to be manipulated
    staticLED = 0; //this is the led to be static

//this line of code dictates whether the led blinks or not
bool blinkBool = false;

void setup() {
  //these 3 lines of code sets the pins R, G, and B as outputs
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  //these 3 lines of code makes the color start off as red
  analogWrite(R, maxBrightness);
  analogWrite(G, minBrightness);
  analogWrite(B, minBrightness);
}

void loop() {
  //this loop iterates 3 times for the 3 colors, RGB
  for (int x = 0; x < 3; x++) {
    if (x == 0) { //this first iteration changes the brightness values for red and green
      staticLED = R;
      manipulatedLED = G;
    }
    else if (x == 1) { //the second iteration changes the brightness values for green and blue
      staticLED = G;
      manipulatedLED = B;
    }
    else { //the third iteration changes the brightness values for blue and red
      staticLED = B;
      manipulatedLED = R;
    }

    //--------------------------------------------------------------

    // the static color is at max brightness
    analogWrite(staticLED, maxBrightness);

    // loop until the manipulated color reaches max brightness
    while (brightness < maxBrightness) {
      // the manipulated color is faded to max brightness to produce a blend of the first and second color
      analogWrite(manipulatedLED, brightness);

      // this if statement turns the leds off to make it blink
      if (blinkBool) {
        delay(wait);
        digitalWrite(manipulatedLED, LOW);
        digitalWrite(staticLED, LOW);
      }

      // wait to display the color
      delay(wait);

      // changes the brightness for next iteration through the loop
      brightness += fadeAmount;
    }

    // makes sure the brightness doesn't go over the max value
    brightness = maxBrightness;

    /*
     * this block of code swaps the manipulatedLED and staticLED variables with each other
     * to make the previous static led fade out to change colors
     */
    int tempSwap = manipulatedLED;
    manipulatedLED = staticLED;
    staticLED = tempSwap;

    // the static color is at max brightness
    analogWrite(staticLED, maxBrightness);

    // loop until the manipulated color reaches min brightness
    while (brightness > minBrightness) {
      // the manipulated color is faded to max brightness to produce a blend of the first and second color
      analogWrite(manipulatedLED, brightness);

      // this if statement turns the leds off to make it blink
      if (blinkBool) {
        delay(wait);
        digitalWrite(manipulatedLED, LOW);
        digitalWrite(staticLED, LOW);
      }

      // wait to display the color
      delay(wait);

      // changes the brightness for next iteration through the loop
      brightness -= fadeAmount;
    }

    // resets brightness to minBrightness
    brightness = minBrightness;

    // makes sure the manipulated color is on the minimum brightness
    analogWrite(manipulatedLED, minBrightness);
  }
}
