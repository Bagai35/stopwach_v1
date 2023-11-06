#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Ширина OLED-дисплея
#define SCREEN_HEIGHT 64 // Высота OLED-дисплея

#define OLED_RESET -1    // Не используется reset дисплея
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int startStopButtonPin = 7; // Пин для кнопки запуска/остановки секундомера
const int resetButtonPin = 8;      // Пин для кнопки сброса секундомера
const int powerButtonPin = 6;      // Пин для кнопки выключения секундомера

unsigned long startTime = 0;       // Время запуска секундомера
unsigned long elapsedTime = 0;     // Прошедшее время
bool isRunning = false;             // Флаг состояния секундомера (запущен/остановлен)

void setup() {
  pinMode(startStopButtonPin, INPUT);
  pinMode(resetButtonPin, INPUT);
  pinMode(powerButtonPin, INPUT);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.display();
}

void loop() {
  int startStopButtonState = digitalRead(startStopButtonPin);
  int resetButtonState = digitalRead(resetButtonPin);
  int powerButtonState = digitalRead(powerButtonPin);

  if (powerButtonState == HIGH) {
    display.clearDisplay();
    display.display();
    isRunning = false;
    delay(1000);
  } else {
    if (startStopButtonState == HIGH) {
      if (!isRunning) {
        startTime = millis() - elapsedTime;
        isRunning = true;
      } else {
        isRunning = false;
      }
      delay(500);
    }

    if (resetButtonState == HIGH) {
      startTime = millis();
      elapsedTime = 0;
      isRunning = false;
      delay(500);
    }

    if (isRunning) {
      elapsedTime = millis() - startTime;
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Time: ");
    display.print(elapsedTime / 1000); // Выводим время в секундах
    display.display();
  }
}
