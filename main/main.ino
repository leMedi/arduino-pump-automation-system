#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <NewPing.h>

#define TRIGGER_PIN 12   // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 11      // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pin and maximum distance.

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
    lcd.begin(20, 4);

    lcd.setCursor(0, 0);
    lcd.print("Distance test: ");
    lcd.setCursor(0, 2);
    lcd.print("Level: ");
}

void LCD_progress_bar(int row, int var, int minVal, int maxVal)
{
    int block = map(var, minVal, maxVal, 0, 16); // Block represent the current LCD space (modify the map setting to fit your LCD)
    int line = map(var, minVal, maxVal, 0, 80);  // Line represent the theoretical lines that should be printed
    int bar = (line - (block * 5));              // Bar represent the actual lines that will be printed

    /* LCD Progress Bar Characters, create your custom bars */

    byte bar1[8] = {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
    byte bar2[8] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
    byte bar3[8] = {0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C};
    byte bar4[8] = {0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E};
    byte bar5[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
    lcd.createChar(1, bar1);
    lcd.createChar(2, bar2);
    lcd.createChar(3, bar3);
    lcd.createChar(4, bar4);
    lcd.createChar(5, bar5);

    for (int x = 0; x < block; x++) // Print all the filled blocks
    {
        lcd.setCursor(x, row);
        lcd.write(1023);
    }

    lcd.setCursor(block, row); // Set the cursor at the current block and print the numbers of line needed
    if (bar != 0)
        lcd.write(bar);
    if (block == 0 && line == 0)
        lcd.write(1022); // Unless there is nothing to print, in this case show blank

    for (int x = 16; x > block; x--) // Print all the blank blocks
    {
        lcd.setCursor(x, row);
        lcd.write(1022);
    }
}

void loop()
{
    delay(500); // Wait 500ms between pings 
    Serial.print("Ping: ");
    // int val = sonar.ping_cm();

    int echoTime = sonar.ping_median(10);
    int val = sonar.convert_cm(echoTime);

    LCD_progress_bar(2, val, 0, MAX_DISTANCE);
    lcd.setCursor(0, 1);
    lcd.print(val); // Send ping, get distance in cm and print result (0 = outside set distance range)
    lcd.print(" cm");
}
