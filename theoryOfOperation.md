# Theory of Operation for the Schematic of the Alarm Clock

**ICs**

The alarm clock is controlled by IC2, the ATMEGA 4809 microcontroller.

IC1, a TLC555 timer IC, delivers a signal to the IC2's pin 25 (PF2) every second. This initiates an interrupt that updates the second timer; checks if minute, hour, day, month, or year need to be updated; checks if the current time matches one of the alarms; and refreshes the LCD screen, if needed.

The beeper circuit is centered around IC3 and IC4, which are two more 555 timers. If pin 40 of IC2 (PA7, an output port) is driven high (i.e., if current time equals one of the alarm times), the beeper circuit's reset is driven high, thus turning it on. The ICs are connected to a speaker, which will emit a tone.


**Interface**

The clock interface consists of 10 buttons and a 20x4 character LCD screen. The two alarm buttons work as a toggle. When held down, alarm time and/or date will display on the LCD. Changing the time or date via the hour, minute, year, month, or day buttons will change the respective values for the alarm whose button is held down. Alarm1 (repeating alarm) is connected to pin 11 (PD2) and Alarm2 (date-specific alarm) is connected to pin 15 (PD6).

Hour, minute, year, month, and day are the buttons used to change the time and date of the clock. They are connected to IC2's GPIO pins and they all trigger interrupts:

|Function|Pin|Pin Name|
|--------|---|--------|
|Hour    |9  |PD0     |
|Minute  |10 |PD1     |
|Year    |12 |PD3     |
|Month   |13 |PD4     |
|Day     |14 |PD5     |

They each check if pin 11 or pin 15 is triggered. If not, the time will be adjusted. If so, the alarm's time will be adjusted.

Alarm1 and Alarm2 may be turned on or off via the two toggle alarm buttons (toggle1 and toggle2). They are connected to IC2's pins 1 and 2 (PC0 and PC1) respectively. They are interrupt driven and simply toggle the alarm1 or alarm2 boolean.

The stop alarm button is connected to IC2's pin 16 and is also interrupt driven. It drives pin 40 (PA7) low, turning off the beeper circuit.
