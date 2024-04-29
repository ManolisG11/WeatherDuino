#include <LiquidCrystal.h>

LiquidCrystal lcd(34,32,28,26,24,22);

#include <DHT11.h>

DHT11 dht11(2);
const float sensitivity = 2.5; // Example sensitivity in mV/G
const float zeroGaussVoltage = 2.5; // Example zero Gauss voltage

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
  int temperature = 0;
    int humidity = 0;
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    int sensorValue = analogRead(A0);
    float voltage = sensorValue * (5.0 / 1023.0);
    float tesla = (voltage - zeroGaussVoltage) / sensitivity;
    lcd.setCursor(0,0);
    Serial.print("Magnetic field strength: ");
    Serial.print(tesla);
    Serial.println(" Tesla");
    lcd.print(tesla);
    delay(1000); // Delay for readability
    if (result == 0) {
      lcd.setCursor(0,1);
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.print(" °C\tHumidity: ");
      Serial.print(humidity);
      Serial.println(" %");
      lcd.print("HT:");
      lcd.setCursor(1,4);
      lcd.print(humidity);
      lcd.setCursor(1,8);
      lcd.print(temperature)
    } 
}
