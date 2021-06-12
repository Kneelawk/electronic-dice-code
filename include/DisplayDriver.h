///
/// Display Driver class - This class handles and drives a dual-7-segment
/// display. This class must have the segment it's currently displaying be
/// manually toggled via the update() method.
///
/// Author: Jed Pommert (Kneelawk)
///

#ifndef ATMEGADISPLAYDEMO2_DISPLAYDRIVER_H
#define ATMEGADISPLAYDEMO2_DISPLAYDRIVER_H

#include <Arduino.h>

class DisplayDriver {
public:
    /// The current value the display is showing
    int8_t value = -1;

    /// DisplayDriver constructor
    DisplayDriver(uint8_t dig1, uint8_t dig2, uint8_t segA, uint8_t segB,
                  uint8_t segC, uint8_t segD, uint8_t segE, uint8_t segF,
                  uint8_t segG);

    virtual ~DisplayDriver();

    /// Initialize the display
    void setup() const;

    /// Allows this display to alternate which digit it is currently displaying.
    /// This is how the display drives both digits.
    void update();

private:
    // digit pins
    uint8_t dig_1;
    uint8_t dig_2;

    // segment pins
    uint8_t seg_a;
    uint8_t seg_b;
    uint8_t seg_c;
    uint8_t seg_d;
    uint8_t seg_e;
    uint8_t seg_f;
    uint8_t seg_g;

    // This is used to determine which digit the display is currently displaying
    // or what step the display is in an animation
    uint8_t stage = 0;

    // The last time the display had an animation frame
    uint64_t last_frame = 0;

    /// Writes a digit to the segment outputs
    void writeDigit(uint8_t digit) const;

    // Turns off all display pins
    void clearDisplay() const;
};


#endif //ATMEGADISPLAYDEMO2_DISPLAYDRIVER_H
