#include <DHT11.h>
DHT11 dht11(2);
const float sensitivity = 2.5; // Example sensitivity in mV/G
const float zeroGaussVoltage = 2.5; // Example zero Gauss voltage
const int transmitInterval = 1000; 
const int ldrPin = A1;  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int temperature = 0;
    int humidity = 0;
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    int sensorValue = analogRead(A0);
    float voltage = sensorValue * (5.0 / 1023.0);
    float tesla = (voltage - zeroGaussVoltage) / sensitivity;
    int ldrValue = analogRead(ldrPin);  
  float value = (5.0 / 1023.0) * ldrValue;  
  int lux = (250.0 / value) - 50.0;
  Serial.print("Lux: ");
  Serial.println(lux);
  delay(transmitInterval);
    Serial.print("Magnetic field strength: ");
    Serial.print(tesla);
    Serial.println(" Tesla");
    delay(1000); // Delay for readability
    if (result == 0) {
      Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    } 
}