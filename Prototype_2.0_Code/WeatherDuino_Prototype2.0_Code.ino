#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 7
#define LDRPIN A1
#define HALLPIN A0
#define BUTTON_PREV 52
#define BUTTON_NEXT 50

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int currentPage = 1;

float humidity, temperature, ldrValue, hallValue;

void setup() {
  lcd.begin(16, 2);

  dht.begin();

  pinMode(BUTTON_PREV, INPUT_PULLUP);
  pinMode(BUTTON_NEXT, INPUT_PULLUP);

  displayPage();
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  ldrValue = analogRead(LDRPIN);
  hallValue = analogRead(HALLPIN);

  if (digitalRead(BUTTON_PREV) == LOW) {
    currentPage--;
    if (currentPage < 1) currentPage = 1;
    displayPage();
    delay(200);
  }
  if (digitalRead(BUTTON_NEXT) == LOW) {
    currentPage++;
    if (currentPage > 2) currentPage = 2;
    displayPage();
    delay(200);
  }
}

void displayPage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (currentPage == 1) {
    lcd.clear();
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Temperature: ");
    lcd.print(temperature);
    lcd.print("C");
  } else if (currentPage == 2) {
    lcd.clear();
    lcd.print("LDR Value: ");
    lcd.print(ldrValue);
    lcd.setCursor(0, 1);
    lcd.print("Hall Value: ");
    lcd.print(hallValue);
  }
}
