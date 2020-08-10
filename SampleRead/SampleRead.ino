#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define HOUR 3
#define MINUTE 4
#define ALARM1 5
#define YEAR 6
#define MONTH 7
#define DAY 8
#define ALARM2 9
#define TOGGLE1 10
#define TOGGLE2 11
#define OFF 12

const long BUTTON_BOUNCE = 35;
LiquidCrystal_I2C lcd(0x27, 20, 4);

volatile int secondCount;
volatile int currentMinute;
volatile int currentHour;
volatile int currentDay;
volatile int currentMonth;
volatile int currentYear;
volatile bool alarm1On;
volatile bool alarm2On;
volatile bool isPM;
volatile int alarm1Hour;
volatile int alarm1Minute;
volatile int alarm2Hour;
volatile int alarm2Minute;
volatile int alarm2Year;
volatile int alarm2Month;
volatile int alarm2Day;
volatile long hourCounter = 0;
volatile long minuteCounter = 0;
volatile long yearCounter = 0;
volatile long monthCounter = 0;
volatile long dayCounter = 0;
volatile long alarm1Counter = 0;
volatile long alarm2Counter = 0;
volatile long toggle1Counter = 0;
volatile long toggle2Counter = 0;



void setup() {
    // Set up the pins:
    pinMode(13, INPUT_PULLUP);
    pinMode(2, INPUT_PULLUP);
    pinMode(HOUR, INPUT_PULLUP);
    pinMode(MINUTE, INPUT_PULLUP);
    pinMode(ALARM1, INPUT_PULLUP);
    pinMode(YEAR, INPUT_PULLUP);
    pinMode(MONTH, INPUT_PULLUP);
    pinMode(DAY, INPUT_PULLUP);
    pinMode(ALARM2, INPUT_PULLUP);
    pinMode(TOGGLE1, INPUT_PULLUP);
    pinMode(TOGGLE2, INPUT_PULLUP);
    pinMode(OFF, INPUT_PULLUP);

    // Set up the ISR:
    attachInterrupt(digitalPinToInterrupt(2), readTick, RISING);

    // Set up the time & date variables:
    secondCount = 0;
    currentMinute = 5;
    currentHour = 9;
    currentDay = 24;
    currentMonth = 1;
    currentYear = 2020;
    alarm1On = false;
    alarm2On = false;
    isPM = (currentHour >= 12) ? true : false;

    hourCounter = 0;
    minuteCounter = 0;
    yearCounter = 0;
    monthCounter = 0;
    dayCounter = 0;
    alarm1Counter = 0;
    alarm2Counter = 0;
    toggle1Counter = 0;
    toggle2Counter = 0;

    // Set up output:
    Serial.begin(19200);
    lcd.init();   
    lcd.backlight();
    lcd.setCursor(1, 0);
    lcd.print("Happy birthday, Vi!");
}


void loop() {
    // Poll buttons
    if(digitalRead(HOUR) == HIGH) {
        hourCounter++;
        if (hourCounter >= BUTTON_BOUNCE) {
            currentHour = (currentHour == 23) ? 0 : (currentHour + 1);
            hourCounter = 0;
        }
    }
    else {
        hourCounter = 0;
    }
    if (digitalRead(MINUTE) == HIGH) {
        minuteCounter++;
        if (minuteCounter >= BUTTON_BOUNCE) {
            currentMinute = (currentMinute == 59) ? 0 : (currentMinute + 1);
            minuteCounter = 0;
        }
    }
    else {
        minuteCounter = 0;
    }

    if (digitalRead(YEAR) == HIGH) {
        yearCounter++;
        if (yearCounter >= BUTTON_BOUNCE) {
            yearCounter = 0;
            currentYear++;
        }
    }
    else {
        yearCounter = 0;
    }
    if (digitalRead(MONTH) == HIGH) {
        yearCounter++;
        if (yearCounter >= BUTTON_BOUNCE) {
            yearCounter = 0;
            currentMonth = (currentMonth == 12) ? 1 : (currentMonth + 1);
            int maxDays = daysInMonth(currentMonth, currentYear);
            if (currentDay > maxDays)
                currentDay = maxDays;
        }
    }
    else {
        monthCounter = 0;
    }
    
    if (digitalRead(DAY) == HIGH) {
        dayCounter++;
        if (dayCounter >= BUTTON_BOUNCE) {
            dayCounter = 0;    
            int maxDays = daysInMonth(currentMonth, currentYear);
            currentDay = (currentDay == maxDays) ? 1 : (currentDay + 1);
        }
    }
    else {
        dayCounter = 0;
    }
    Serial.println(dayCounter);
    displayTime();
}


//--------------------------------------------------------------------------
//  Method:       readTick
//  Description:  Interrupt called every 1.0 seconds. Updates the second
//                  count and changes the time if needed.
//  Called by:    ISR
//  Calls:        changeTime
//--------------------------------------------------------------------------
void readTick() {
    secondCount++;
    if (secondCount == 60)
        changeTime();
}


//--------------------------------------------------------------------------
//  Method:       changeTime
//  Description:  Updates all time and date variables.
//  Called by:    readTick
//  Calls:        daysInMonth
//--------------------------------------------------------------------------
void changeTime() {
    secondCount = 0;
    currentMinute++;
    if (currentMinute == 60) {
        currentMinute = 0;
        currentHour++;
        if (currentHour == 24) {
            currentHour = 0;
            currentDay++;
            if (currentDay > daysInMonth(currentMonth, currentYear)) {
                currentDay = 1;
                currentMonth++;
                if (currentMonth > 12) {
                    currentMonth = 1;
                    currentYear++;
                }
            }
        }
    }
}


//--------------------------------------------------------------------------
//  Description:  Calculates the number of days in the given month.
//  Called by:    changeTime
//  Calls:        isLeapYear
//--------------------------------------------------------------------------
int daysInMonth(int month, int year) {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    if (month == 2) {
        if (isLeapYear(year))
            return 29;
        else
            return 28;
    }
    return 30;
}


//--------------------------------------------------------------------------
//  Method:       isLeapYear
//  Description:  Checks if the current year is a leap year
//  Called by:    daysInMonth
//--------------------------------------------------------------------------
bool isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    return false;
}


//--------------------------------------------------------------------------
//  Method:       displayTime
//  Description:  Displays the time and date to the LCD.
//  Called by:    loop
//--------------------------------------------------------------------------
void displayTime() {
    // Display the date:
    lcd.setCursor(0,1);
    if (currentMonth < 10)
        lcd.print("0");
    lcd.print(currentMonth);
    lcd.print("/");
    if (currentDay < 10)
        lcd.print("0");
    lcd.print(currentDay);
    lcd.print("/");
    lcd.print(currentYear);

    // Display the time:
    lcd.setCursor(0,2);
    
    // Hour:
    if (currentHour == 0)
    lcd.print("12");
    else if (currentHour > 0 && currentHour < 13) {
        if (currentHour < 10)
            lcd.print("0");
        lcd.print(currentHour);
    }
    else {
        if (currentHour - 12 < 10)
            lcd.print("0");
        lcd.print(currentHour - 12);
    }
    lcd.print(":");
    
    // Minute:
    if (currentMinute < 10)
        lcd.print("0");
    lcd.print(currentMinute);
    lcd.print(":");
    
    // Second:
    if (secondCount < 10)
        lcd.print("0");
    lcd.print(secondCount);
    lcd.print(" ");

    // AM/PM:
    if (currentHour >= 12)
        lcd.print("PM");
    else
        lcd.print("AM");
}
