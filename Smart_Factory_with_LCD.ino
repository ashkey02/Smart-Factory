//Integrated Control CODE
//Control Fan Motor
//Control Water Level
//This sketch turns the Fan Motor ON and OFF based on measured temperature and set UCL and LCL
//It also prints the analog read value from the thermistor
//This sketch monitors and controls the water level in the Chemical Bath and Reservoir

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int tempval = 0;  // variable to store temperature value read at analog pin 2
int waterval = 100; // variable to store analog water level value
float temp = 0;   //leftover from previous Test sketch
int FanOn = HIGH;
int FanOff = LOW;
int LedOn = HIGH;
int LedOff = LOW;
int PumpOn = HIGH;
int PumpOff = LOW;

//Setup of setpoint, UCL, and LCL
int setpoint = 520;
//int setpoint = analogRead(5);
int UCL = setpoint + 3;
int LCL = setpoint - 3;

void setup() {
  pinMode(8, OUTPUT); //digital pin 8 controls Fan Motor
  pinMode(7, OUTPUT); //digital pin 7 controls LED Heater
  pinMode(6, OUTPUT); //digital pin 6 controls Mini-Pump
  Serial.begin(9600); //set up to print out text to monitor
 
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
   
  
  lcd.setCursor ( 0, 0 );            // go to the top left corner
  lcd.print("Team 02"); // write this string on the top row // team number
}

void loop() {
  delay(4000);
  //  Serial.print("Setpoint = ");
  //  Serial.print(setpoint);
  Serial.print("UCL = "); Serial.print(UCL);
  Serial.print("  LCL = "); Serial.println(LCL);
  tempval = analogRead(0);  // read thermister analog input pin 0
  Serial.print("Current Temp = ");
  Serial.println(tempval);    // print thermister value to serial monitor
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("T=");
  lcd.print(tempval); // pad with spaces for centering  Air Temp 
  lcd.print(" ");
  lcd.print("U=");
  lcd.print(UCL);
  lcd.print(" ");
  lcd.print("L=");
  lcd.print(LCL);
  
  //IF-THEN-ELSE for Temperature
  if (tempval < LCL)
  {
    Serial.println("***tempval < LCL -- Turn ON LED");
    lcd.setCursor ( 0, 1 );
    lcd.print("Fan=0");
    FanOff = Serial.println("Fan=0");
    lcd.setCursor ( 6, 1 );
    lcd.print("Led=1");
    LedOn = Serial.println("Led=1");
    LEDON();
  }
  else if (tempval > UCL)
  {
    Serial.println("***tempval > UCL -- Turn OFF LED, Turn ON Fan");
    FanOn = Serial.println("Fan=1");
    delay(5000);
    FanOff = Serial.println("Fan=0");
    lcd.setCursor ( 6, 1 );
    lcd.print("Led=0");
    LedOff = Serial.println("Led=0");
    LEDOFF();
  }
  else {
    lcd.setCursor ( 0, 1 );
    lcd.print("Fan=0");
    FanOff = Serial.println("Fan=0");
    lcd.setCursor ( 6, 1 );
    lcd.print("Led=0");
    LedOff = Serial.println("Led=0");
    }

  //IF-THEN-ELSE for Water Level
  waterval = analogRead(1);  // read water sensor analog input pin 4
  Serial.print("H2O level = "); 
  Serial.println(waterval);
  Serial.println("H2O upper limit = 500");
  Serial.println("H2O lower limit = 390");
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print("W=");
  lcd.print(waterval); // pad with spaces for centering // H2O level

  if (waterval < 390)
  {
    PumpOn = Serial.println("Pump=1"); 
    PumpOff = Serial.println("Pump=0");
    PUMPON();
  }
  else {
    lcd.setCursor ( 12, 1 );
    lcd.print("Pump=0");
    PumpOff = Serial.println("Pump=0");
    }
  Serial.println();
}

void LEDON() {
  //  Serial.println("In LCL Function");
  digitalWrite(7, HIGH); //LED ON
}

void LEDOFF() {
  //  Serial.println("In UCL Function");
  digitalWrite(7, LOW);  //LED OFF
  lcd.setCursor ( 0, 1 );
  lcd.print("Fan=1");
  digitalWrite(8, HIGH); //Fan ON
  delay(5000);
  lcd.setCursor ( 0, 1 );
  lcd.print("Fan=0");
  digitalWrite(8, LOW);  //Fan OFF
}

void PUMPON() {
  lcd.setCursor ( 12, 1 );
  lcd.print("Pump=1");
  Serial.println("In PUMP Function");
  digitalWrite(6, HIGH);  //Mini-pump ON
  delay(10000);  //time to operate mini-pump
  lcd.setCursor ( 12, 1 );
  lcd.print("Pump=0");
  digitalWrite(6, LOW);   //Turn OFF mini-pump
}

//digitalWrite(8, HIGH); //Fan ON
//delay(2000);
//digitalWrite(8, LOW);  //Fan OFF
//delay(2000);

//digitalWrite(7, HIGH); //LED ON
//delay(2000);
//digitalWrite(7, LOW);  //LED OFF
//delay(2000);
