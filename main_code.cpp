#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// ── Pin & sensor config ──────────────────
#define DHTPIN    2
#define DHTTYPE   DHT11

// ── Change 0x27 to your address if needed ─
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // Start LCD
  lcd.init();
  lcd.backlight();

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print("  DHT11 Monitor ");
  lcd.setCursor(0, 1);
  lcd.print("  Starting...   ");
  delay(2000);
  lcd.clear();

  // Start DHT
  dht.begin();
}

void loop() {
  float humidity    = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius
                                             // use readTemperature(true) for Fahrenheit

  // Check if reading failed
  if (isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    lcd.setCursor(0, 1);
    lcd.print("Check wiring... ");
    Serial.println("Failed to read from DHT11!");
    delay(2000);
    return;
  }

  // ── Display on LCD ───────────────────────
  // Row 1: Temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp:  ");
  lcd.print(temperature, 1); // 1 decimal place
  lcd.print(" C      ");

  // Row 2: Humidity
  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(humidity, 1);
  lcd.print(" %      ");

  // ── Also print to Serial Monitor ────────
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.println("──────────────");

  delay(2000); // Read every 2 seconds
}