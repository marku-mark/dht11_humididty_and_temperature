#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN    2
#define DHTTYPE   DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("  DHT11 Monitor ");
  lcd.setCursor(0, 1);
  lcd.print("  Starting...   ");
  delay(2000);
  lcd.clear();

  dht.begin();
}

void loop() {
  float humidity    = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    lcd.setCursor(0, 1);
    lcd.print("Check wiring... ");
    Serial.println("Failed to read from DHT11!");
    delay(2000);
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp:  ");
  lcd.print(temperature, 1);
  lcd.print(" C      ");

  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(humidity, 1);
  lcd.print(" %      ");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.println("──────────────");

  delay(2000);
}