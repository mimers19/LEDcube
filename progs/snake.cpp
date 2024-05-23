#include <Arduino.h>
#include <FastLED.h>
#include "BluetoothSerial.h"

#define LED_COUNT 192
#define PIN_COLUMN1 13
#define COLUMN_HEIGHT 12
#define COLUMN_WIDTH 4

#define MAX_SNAKE_LENGTH 18

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

CRGB leds1[LED_COUNT];

struct Position {
    uint8_t x;
    uint8_t y;
    uint8_t z;
};

Position snake[MAX_SNAKE_LENGTH] = {{2, 2, 6}};
uint8_t snake_length = 1;

Position food = {3, 3, 3};

void getDirection();
void init();
void setLed(uint8_t x, uint8_t y, uint8_t z, CRGB color);
void setLed(Position pos, CRGB color);
void setAllLEDs(CRGB color);
void blink();
void generateFood();
char ReadBT();
void Init();

uint8_t dir = 0; 
// 0 - UP
// 5 - DOWN
// 1 - LEFT
// 4 - RIGHT
// 2 - FORWARDS
// 3 - BACKWARDS

CRGB snake_color;
CRGB food_color;
CRGB background_color;

void setup() {
    Serial.begin(9600);
    SerialBT.begin("LEDcube");
    pinMode(LED_BUILTIN, OUTPUT);
    Init();
}

void loop() {
    if (SerialBT.available()>0) {
        char x = ReadBT();
        Serial.println(x);
        
        Position new_head = snake[0];
        switch (x) {
            case 'w':
                new_head.y++;
                break;
            case 'a':
                new_head.x--;
                break;
            case 's':
                new_head.y--;
                break;
            case 'd':
                new_head.x++;
                break;
            case 'e':
                new_head.z++;
                break;
            case 'q':
                new_head.z--;
                break;
        }
        
        // Check for collision with walls
        if (new_head.x >= COLUMN_WIDTH || new_head.y >= COLUMN_WIDTH || new_head.z >= COLUMN_HEIGHT || new_head.x < 0 || new_head.y < 0 || new_head.z < 0) {
            setAllLEDs(food_color);
            FastLED.show();
            delay(1000);
            Init();
            return;
        }
        
        // Check for collision with self
        for (uint8_t i = 0; i < snake_length; i++) {
            if (new_head.x == snake[i].x && new_head.y == snake[i].y && new_head.z == snake[i].z) {
                setAllLEDs(food_color);
                FastLED.show();
                delay(1000);
                Init();
                return;
            }
        }
        
        // Move the snake
        for (uint8_t i = snake_length; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
        snake[0] = new_head;
        
        // Check if food is eaten
        if (new_head.x == food.x && new_head.y == food.y && new_head.z == food.z) {
            if (snake_length < MAX_SNAKE_LENGTH) {
                snake_length++;
            }
            generateFood();
        }
        
        setAllLEDs(background_color);
        for (uint8_t i = 0; i < snake_length; i++) {
            // Generate a gradient from dark green (head) to lighter green (tail)
            uint8_t green_intensity = (i * (255 / MAX_SNAKE_LENGTH));
            CRGB current_color = CRGB(green_intensity, 255, green_intensity);
            setLed(snake[i], current_color);
        }
        setLed(food, food_color);
        FastLED.show();
    }
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
    for(int i = 0; i < LED_COUNT; i++) {
        leds1[i] = color;
    }
}

void blink() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
}

void generateFood() {
    food.x = random(0, COLUMN_WIDTH);
    food.y = random(0, COLUMN_WIDTH);
    food.z = random(0, COLUMN_HEIGHT);
    setLed(food, food_color);
}

char ReadBT() {
    if (SerialBT.available()>0) {
        for(;;) {
            char x = SerialBT.read();
            if (x == 'w' || x == 'a' || x == 's' || x == 'd' || x == 'e' || x == 'q') {
                return x;
            }
        }
    }
    return ' ';
}

void Init() {
    snake_length = 1;
    digitalWrite(LED_BUILTIN, LOW);
    FastLED.addLeds<WS2812, PIN_COLUMN1, RGB>(leds1, LED_COUNT);
    background_color = CRGB(0x00, 0x00, 0x00);
    snake_color = CRGB(0x00, 0xFF, 0x00);
    food_color = CRGB(0xFF, 0x00, 0x00);
    setAllLEDs(background_color);
    setLed(snake[0], snake_color);
    setLed(food, food_color);
    FastLED.show();
}