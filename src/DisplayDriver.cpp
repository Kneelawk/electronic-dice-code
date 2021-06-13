///
/// Display Driver class - This class handles and drives a dual-7-segment
/// display. This class must have the segment it's currently displaying be
/// manually toggled via the update() method.
///
/// Author: Jed Pommert (Kneelawk)
///

#include "DisplayDriver.h"

const uint64_t ANIMATION_FRAME_TIME = 500;

DisplayDriver::DisplayDriver(uint8_t dig1, uint8_t dig2, uint8_t segA,
                             uint8_t segB, uint8_t segC, uint8_t segD,
                             uint8_t segE, uint8_t segF, uint8_t segG)
        : dig_1(dig1), dig_2(dig2), seg_a(segA), seg_b(segB), seg_c(segC),
          seg_d(segD), seg_e(segE), seg_f(segF), seg_g(segG) {}

void DisplayDriver::setup() const {
    // Setup the digit pins
    pinMode(dig_1, OUTPUT);
    pinMode(dig_2, OUTPUT);

    // Setup the segment pins
    pinMode(seg_a, OUTPUT);
    pinMode(seg_b, OUTPUT);
    pinMode(seg_c, OUTPUT);
    pinMode(seg_d, OUTPUT);
    pinMode(seg_e, OUTPUT);
    pinMode(seg_f, OUTPUT);
    pinMode(seg_g, OUTPUT);
}

void DisplayDriver::update() {
    if (value >= 0) {
        // Make sure stage is valid
        if (stage > 1) {
            stage = 0;
        }

        if (stage == 0) {
            // Stage 0 means we're displaying the 1's digit
            uint8_t digit = value % 10;

            // Write the 1's digit
            digitalWrite(dig_2, LOW);
            writeDigit(digit);
            digitalWrite(dig_1, HIGH);
        } else {
            // Stage 1 means we're displaying the 10's digit
            uint8_t digit = value / 10 % 10;

            // Write the 10's digit
            digitalWrite(dig_1, LOW);
            writeDigit(digit);
            digitalWrite(dig_2, HIGH);
        }

        // We'll just increment stage here because that will cause it to
        // oscillate between 0 and 1
        stage++;
    } else {
        // Get the current time
        uint64_t now = millis();
        // Only update the animation frame if the current time is far enough
        // after the previous animation frame
        if (now - last_frame >= ANIMATION_FRAME_TIME) {
            // Update the last_frame to indicate this is now the last frame
            last_frame = now;

            // There are only 8 frames in this animation, 0 to 7. Reset the
            // stage if it's too large.
            if (stage >= 8) {
                stage = 0;
            }

            // We aren't sure what state the display is in so we just turn off
            // all pins
            clearDisplay();

            // Cause the light to spin around the display, determining the
            // current segment based on the current
            // animation frame
            switch (stage) {
                case 0:
                    digitalWrite(dig_1, HIGH);
                    digitalWrite(seg_a, HIGH);
                    break;
                case 1:
                    digitalWrite(dig_1, HIGH);
                    digitalWrite(seg_b, HIGH);
                    break;
                case 2:
                    digitalWrite(dig_1, HIGH);
                    digitalWrite(seg_c, HIGH);
                    break;
                case 3:
                    digitalWrite(dig_1, HIGH);
                    digitalWrite(seg_d, HIGH);
                    break;
                case 4:
                    digitalWrite(dig_2, HIGH);
                    digitalWrite(seg_d, HIGH);
                    break;
                case 5:
                    digitalWrite(dig_2, HIGH);
                    digitalWrite(seg_e, HIGH);
                    break;
                case 6:
                    digitalWrite(dig_2, HIGH);
                    digitalWrite(seg_f, HIGH);
                    break;
                case 7:
                    digitalWrite(dig_2, HIGH);
                    digitalWrite(seg_a, HIGH);
                    break;
            }

            // Increment the animation frame
            stage++;
        }
    }
}

void DisplayDriver::writeDigit(uint8_t digit) const {
    // Segment A
    if (digit == 0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 ||
        digit == 7 || digit == 8 || digit == 9) {
        digitalWrite(seg_a, HIGH);
    } else {
        digitalWrite(seg_a, LOW);
    }

    // Segment B
    if (digit == 0 || digit == 1 || digit == 2 || digit == 3 || digit == 4 ||
        digit == 7 || digit == 8 || digit == 9) {
        digitalWrite(seg_b, HIGH);
    } else {
        digitalWrite(seg_b, LOW);
    }

    // Segment C
    if (digit == 0 || digit == 1 || digit == 3 || digit == 4 || digit == 5 ||
        digit == 6 || digit == 7 || digit == 8 || digit == 9) {
        digitalWrite(seg_c, HIGH);
    } else {
        digitalWrite(seg_c, LOW);
    }

    // Segment D
    if (digit == 0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 ||
        digit == 8 || digit == 9) {
        digitalWrite(seg_d, HIGH);
    } else {
        digitalWrite(seg_d, LOW);
    }

    // Segment E
    if (digit == 0 || digit == 2 || digit == 6 || digit == 8) {
        digitalWrite(seg_e, HIGH);
    } else {
        digitalWrite(seg_e, LOW);
    }

    // Segment F
    if (digit == 0 || digit == 4 || digit == 5 || digit == 6 || digit == 8 ||
        digit == 9) {
        digitalWrite(seg_f, HIGH);
    } else {
        digitalWrite(seg_f, LOW);
    }

    // Segment G
    if (digit == 2 || digit == 3 || digit == 4 || digit == 5 || digit == 6 ||
        digit == 8 || digit == 9) {
        digitalWrite(seg_g, HIGH);
    } else {
        digitalWrite(seg_g, LOW);
    }
}

void DisplayDriver::clearDisplay() const {
    // Turn all the display pins off
    digitalWrite(dig_1, LOW);
    digitalWrite(dig_2, LOW);
    digitalWrite(seg_a, LOW);
    digitalWrite(seg_b, LOW);
    digitalWrite(seg_c, LOW);
    digitalWrite(seg_d, LOW);
    digitalWrite(seg_e, LOW);
    digitalWrite(seg_f, LOW);
    digitalWrite(seg_g, LOW);
}

DisplayDriver::~DisplayDriver() = default;
