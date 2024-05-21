#include <Arduino.h>
#include <FastLED.h>
#include <math.h>

#define LED_COUNT 192
#define PIN_COLUMN1 13
#define COLUMN_HEIGHT 12
#define COLUMN_WIDTH 4

CRGB leds1[LED_COUNT];

struct Position {
    uint8_t x;
    uint8_t y;
    uint8_t z;
};

void setLed(uint8_t x, uint8_t y, uint8_t z, CRGB color);
void setLed(Position pos, CRGB color);
void setAllLEDs(CRGB color);
void drawWave(float time);

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    FastLED.addLeds<WS2812, PIN_COLUMN1, RGB>(leds1, LED_COUNT);
    setAllLEDs(CRGB::Black); // Initialize all LEDs to off
}

void loop() {
    static float time = 0;
    drawWave(time);
    FastLED.show();
    delay(10); // Update rate
    time += 0.15; // Increment time for wave animation
}

void setLed(uint8_t x, uint8_t y, uint8_t z, CRGB color) {
    Position pos = {x, y, z};
    setLed(pos, color);
}

void setLed(Position pos, CRGB color) {
    uint8_t var;
    uint8_t var2;

    pos.x = pos.x % COLUMN_WIDTH;
    pos.y = pos.y % COLUMN_WIDTH;
    pos.z = pos.z % COLUMN_HEIGHT + 1;

    var2 = pos.y % 2;
    if (var2 == 1) {
        pos.x = COLUMN_WIDTH - pos.x - 1;
    }

    var = pos.y * COLUMN_HEIGHT * COLUMN_WIDTH + pos.x * COLUMN_HEIGHT;
    var2 = (var / COLUMN_HEIGHT) % 2;
    if (var2 == 1) {
        pos.z = COLUMN_HEIGHT - pos.z + 1;
    }

    uint8_t diode = LED_COUNT - (pos.y * COLUMN_HEIGHT * COLUMN_WIDTH + pos.x * COLUMN_HEIGHT + pos.z);
    leds1[diode] = color;
}

void setAllLEDs(CRGB color) {
    for (int i = 0; i < LED_COUNT; i++) {
        leds1[i] = color;
    }
}

void drawWave(float time) {
    setAllLEDs(CRGB::Black); // Clear all LEDs before drawing the wave

    for (uint8_t x = 0; x < COLUMN_WIDTH; x++) {
        for (uint8_t y = 0; y < COLUMN_WIDTH; y++) {
            for (uint8_t z = 0; z < COLUMN_HEIGHT; z++) {
                // Calculate the wave position and color
                float wave = (sin((x + time) * 0.5) + sin((y + time) * 0.5));
                uint8_t waveHeight = (wave + 2) * 3; // Adjust wave height for better visibility
                if (waveHeight == z) {
                    // Set color based on position for a gradient effect
                    CRGB color = CHSV((x * 10 + y * 10 + z * 10 + int(time * 10)) % 255, 255, 255);
                    setLed(x, y, z, color);
                }
            }
        }
    }
}
