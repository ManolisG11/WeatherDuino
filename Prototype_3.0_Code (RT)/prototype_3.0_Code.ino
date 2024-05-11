#include <LiquidCrystal.h>
#include <DHT11.h>

DHT11 dht11(7);

#define BUTTON_PREV 52
#define BUTTON_NEXT 50

int temperature = 0;
int humidity = 0;
int currentPage = 1;

const float zeroGaussVoltage = 2.5;
const float sensitivity = 2.5;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);

  pinMode(BUTTON_PREV, INPUT_PULLUP);
  pinMode(BUTTON_NEXT, INPUT_PULLUP);

  displayPage();
}

void loop() {
  if (digitalRead(BUTTON_PREV) == LOW) {
    currentPage--;
  }
  if (digitalRead(BUTTON_NEXT) == LOW) {
    currentPage++;
  }
  displayPage();
  delay(200);
}

void displayPage() {
  if (currentPage < 1) currentPage = 1;
  if (currentPage >2) currentPage = 2;
  if (currentPage == 1) {
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Temperature: ");
    lcd.print(temperature);
    lcd.print("C");
    
  } else if (currentPage == 2) {
    int hallValue = analogRead(A0);
    float voltage = hallValue * (5.0 / 1023.0);
    float tesla = (voltage - zeroGaussVoltage) / sensitivity;
    int ldrValue = analogRead(A1);
    float value = (5.0 / 1023.0) * ldrValue;
    int lux = (250.0 / value) - 50.0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tesla: ");
    lcd.print(tesla);
    lcd.setCursor(0, 1);
    lcd.print("Lux: ");
    lcd.print(lux);
  }
}
