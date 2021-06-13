#include <Arduino.h>

#include "DisplayDriver.h"

/* Constants */

// Display common cathode control pins
const uint8_t DIG_1 = 9;
const uint8_t DIG_2 = 10;

// Display anode control pins. Note that the analog pins can also function as
// digital IO pins.
const uint8_t SEG_A = A3;
const uint8_t SEG_B = A2;
const uint8_t SEG_C = 11;
const uint8_t SEG_D = 12;
const uint8_t SEG_E = 13;
const uint8_t SEG_F = A5;
const uint8_t SEG_G = A4;

// Button pins
const uint8_t BUTTON_D4 = 2;
const uint8_t BUTTON_D6 = 3;
const uint8_t BUTTON_D8 = 4;
const uint8_t BUTTON_D10 = 5;
const uint8_t BUTTON_D12 = 6;
const uint8_t BUTTON_D20 = 7;
const uint8_t BUTTON_D100 = 8;

/* Program State */

// Display driver object for driving the dual 7-segment display
DisplayDriver display(DIG_1, DIG_2, SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F,
                      SEG_G);

/* Entrypoint Functions */

void setup() {
    // Initialize the display, e.g. setting pin modes and such
    display.setup();

    // Setup the button pins as pull-up inputs
    pinMode(BUTTON_D4, INPUT_PULLUP);
    pinMode(BUTTON_D6, INPUT_PULLUP);
    pinMode(BUTTON_D8, INPUT_PULLUP);
    pinMode(BUTTON_D10, INPUT_PULLUP);
    pinMode(BUTTON_D12, INPUT_PULLUP);
    pinMode(BUTTON_D20, INPUT_PULLUP);
    pinMode(BUTTON_D100, INPUT_PULLUP);

    // Set the display's initial value to the idle animation
    display.value = -1;

    // Read a floating analog pin to get a fairly-random seed for our dice
    randomSeed(analogRead(A0));
}

void loop() {
    // Roll the dice depending on which dice button has been pressed
    if (digitalRead(BUTTON_D4) == LOW) {
        // Roll a D4. Note that we're picking a random number between 1 and 5
        // because the lower end is inclusive but the upper end is exclusive,
        // meaning that the minimum resulting number would be 1 and the maximum
        // resulting number would be 4.
        display.value = (int8_t) random(1, 4 + 1);
    } else if (digitalRead(BUTTON_D6) == LOW) {
        // Roll a D6
        display.value = (int8_t) random(1, 6 + 1);
    } else if (digitalRead(BUTTON_D8) == LOW) {
        // Roll a D8
        display.value = (int8_t) random(1, 8 + 1);
    } else if (digitalRead(BUTTON_D10) == LOW) {
        // Roll a D10
        display.value = (int8_t) random(1, 10 + 1);
    } else if (digitalRead(BUTTON_D12) == LOW) {
        // Roll a D12
        display.value = (int8_t) random(1, 12 + 1);
    } else if (digitalRead(BUTTON_D20) == LOW) {
        // Roll a D20
        display.value = (int8_t) random(1, 20 + 1);
    } else if (digitalRead(BUTTON_D100) == LOW) {
        // Roll a D100. Note that we roll between 0 (inclusive) and 100
        // (exclusive) here instead of 1 (inclusive) and 101 (exclusive) because
        // we can just use '0' to mean 100.
        display.value = (int8_t) random(0, 100);
    }

    // Update the display
    display.update();

    // Wait for a millisecond between each display update so as to not waste
    // battery power
    delay(2);
}
