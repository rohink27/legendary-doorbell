/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/
int button =8;

// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>
Servo door;
boolean door_open=false;
 int i=0;
 int j=0;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  door.attach(6);
  door.write(45);
  door_open=false;
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("door locked");
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
 
  analogWrite(9,255);
  analogWrite(10,0);

  // Print a message to the LCD.
  
  pinMode(button,INPUT);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  
  // print the number of seconds since reset:
  if(digitalRead(button)&& !door_open){
    door.write(90);
    door_open=true;
    lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Door unlocked");
  analogWrite(9,0);
  analogWrite(10,0);
  delay(100);
  while(digitalRead(button));
  
  }
  
  else if( digitalRead(button)){
    door.write(45);
    door_open=false;
    lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("door locked");
  analogWrite(9,255);
  analogWrite(10,0);
  delay(100);
  while(digitalRead(button));
  
  }
  /*analogWrite(9,i);
  analogWrite(10,j);
  j=j+1;
  if(j==255)
  {
    i=i+1;
    j=0;
    if(i==255)
    i=0;
  }
  delay(100);*/
  
  

  
}
