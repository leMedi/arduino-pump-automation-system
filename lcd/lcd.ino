#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
void setup()
{
  // Setup LCD to 16x2 characters
  lcd.begin(20, 4);

  lcd.setCursor(0, 0);
  lcd.print("Counter: ");
  lcd.setCursor(0, 2);
  lcd.print("Progress: ");
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

int i = 0;
void loop()
{
  lcd.setCursor(4, 1);
  lcd.print(i);
  LCD_progress_bar(3, i, 0, 30);
      
  i = i + 1;
  if (i > 30)
    i = 0;
  // Wait one second before repeating :)
  delay (1000);
}