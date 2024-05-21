#include <Arduino.h>
#include <FastLED.h>

#define LED_COUNT 192
#define PIN_COLUMN1 13
#define COLUMN_HEIGHT 12
#define COLUMN_WIDTH 4

CRGB leds1[LED_COUNT];

void setLed(uint8_t x, uint8_t y, uint8_t z, CRGB color);
void setAllLEDs(CRGB color);
CHSV getRainbowColor(uint8_t position);

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    FastLED.addLeds<WS2812, PIN_COLUMN1, RGB>(leds1, LED_COUNT);
}

void loop() {
    static uint8_t offset = 0;
    
    // Clear all LEDs
    setAllLEDs(CRGB::Black);

    // Set LEDs with a rainbow wave
    for (uint8_t x = 0; x < COLUMN_WIDTH; x++) {
        for (uint8_t y = 0; y < COLUMN_WIDTH; y++) {
            for (uint8_t z = 0; z < COLUMN_HEIGHT; z++) {
                uint8_t colorPosition = (x + y + z + offset) % 256;
                setLed(x, y, z, getRainbowColor(colorPosition));
            }
        }
    }

    FastLED.show();
    offset++;
    delay(100); // Update rate
}

void setLed(uint8_t x, uint8_t y, uint8_t z, CRGB color) {
    x = x % COLUMN_WIDTH;
    y = y % COLUMN_WIDTH;
    z = z % COLUMN_HEIGHT;

    if (y % 2 == 1) {
        x = COLUMN_WIDTH - x - 1;
    }

    uint8_t ledIndex = y * COLUMN_HEIGHT * COLUMN_WIDTH + x * COLUMN_HEIGHT + z;
    if (((y * COLUMN_HEIGHT * COLUMN_WIDTH + x * COLUMN_HEIGHT) / COLUMN_HEIGHT) % 2 == 1) {
        z = COLUMN_HEIGHT - z - 1;
    }

    uint8_t diode = LED_COUNT - (y * COLUMN_HEIGHT * COLUMN_WIDTH + x * COLUMN_HEIGHT + z) - 1;
    leds1[diode] = color;
}

void setAllLEDs(CRGB color) {
    fill_solid(leds1, LED_COUNT, color);
}

CHSV getRainbowColor(uint8_t position) {
    return CHSV(position * 16, 255, 255);
}
