/*
 * weatherClock
 * Based on temperature_sensor.pde by spacetinkerer@gmail.com
 * -----------------
 * Takes the sensor (LM335) input and converts it
 * to Kelvin degrees, then celsius.
 * Subtract 2.5 celsius degrees that seem
 * to be the sensor error perhaps due to the heat
 * generating by the current running through it.
 * 2.5 degrees were calculated by using a mercury
 * thermometer next to the sensor.
 *
 * And PCD8544 - Interface with Philips PCD8544 (or compatible) LCDs.
 * Copyright (c) 2010 Carlos Rodrigues <cefrodrigues@gmail.com>
 * 
 */

#include <PCD8544.h>

float temp_in_celsius = 0, temp_in_kelvin=0, temp_in_fahrenheit=0;

static const byte ledPin = 13;

// The dimensions of the LCD (in pixels)...
static const byte LCD_WIDTH = 84;
static const byte LCD_HEIGHT = 48;

// A custom "degrees" symbol...
static const byte DEGREES_CHAR = 1;
static const byte degrees_glyph[] = { 
  0x00, 0x07, 0x05, 0x07, 0x00 };

static PCD8544 lcd;



void setup()
{
  Serial.begin(9600);
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);

  // Register the custom symbol...
  lcd.createChar(DEGREES_CHAR, degrees_glyph);
  
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // Start beyond the edge of the screen...
  static byte xChart = LCD_WIDTH;

  digitalWrite(ledPin, HIGH);

  //Reads the input and converts it to Kelvin degrees
  temp_in_kelvin = analogRead(0) * 0.004882812 * 100;

  //Converts Kelvin to Celsius minus 2.5 degrees error
  temp_in_celsius = temp_in_kelvin - 2.5 - 272.15;

  temp_in_fahrenheit = ((temp_in_kelvin - 2.5) * 9 / 5) - 459.67;

  // Print the temperature (using the custom "degrees" symbol)...
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp_in_celsius, 1);
  lcd.print("\001C "); 

  lcd.setCursor(0, 2);
  lcd.print("Temp: ");
  lcd.print(temp_in_fahrenheit, 1);
  lcd.print("\001F "); 
  
  lcd.setCursor(0, 4);
  lcd.print("Temp: ");
  lcd.print(temp_in_kelvin, 1);
  lcd.print("\001K ");              
  
  
  digitalWrite(ledPin, LOW);  
  delay(3000);
}

