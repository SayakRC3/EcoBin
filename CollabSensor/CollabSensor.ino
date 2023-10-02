#include <dht11.h>

#define SensorPin 8          // pH sensor analog pin
#define DHT11PIN 4           // DHT11 sensor digital pin
#define smokeA0 A0           // Gas sensor analog pin
#define buzzer 13            // Buzzer pin

unsigned long int avgValue;  // Store the average value of the pH sensor feedback
float b;
int buf[10], temp;
dht11 DHT11;

void setup()
{
  pinMode(13, OUTPUT);  
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);  
  Serial.println("Ready");    // Test the serial monitor
  Serial.println("Gas sensor warming up!");
  delay(20000); // Allow the MQ-6 to warm up
}

void loop()
{
  // pH Sensor Reading
  for(int i = 0; i < 10; i++) {
    buf[i] = analogRead(SensorPin);
    delay(10);
  }

  for(int i = 0; i < 9; i++) {
    for(int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }

  avgValue = 0;
  for(int i = 2; i < 8; i++) {
    avgValue += buf[i];
  }

  float phValue = (float)avgValue * 5.0 / 1024 / 6; // Convert the analog into millivolt
  phValue = 3.5 * phValue;                      // Convert the millivolt into pH value

  // Temperature and Humidity Sensor Reading
  int chk = DHT11.read(DHT11PIN);

  // Gas Sensor Reading
  float sensorValue = analogRead(smokeA0);

  // Print Sensor Readings
  Serial.print("pH: ");  
  Serial.print(phValue, 2);
  Serial.println(" ");

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (C): ");
  Serial.println((float)DHT11.temperature, 2);

  Serial.print("Gas Concentration: ");
  Serial.println(sensorValue);

  // Buzzer Control Based on Gas Concentration
  if (sensorValue > 140) {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(2000); // Wait for 2 seconds for the next reading
}
