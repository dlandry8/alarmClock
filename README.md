# alarmClock
This is a custom alarm clock powered by a Microchip/Atmel microcontroller. This is a personal project meant to teach me some fundamentals of embedded programming:

    - How to use a uC programmer (Atmel ICE)
    - How to program using an IDE focused on embedded hardware (Atmel Studio)
    - How to integrate a uC that's NOT a development board.
    
I absolutely loved my engineering classes and my embedded systems class at UW! However, I only ever used Arduinos/RPIs/TIs for all of my projects. Thus, I never learned how to use a programmer to program a microcontroller. The aim of this project is:

    - Meet my above learning goals
    - Have a fully functional alarm clock for my room
    - Have a unique artistic outlet
    
The alarm clock will be encased in a wooden box. It will have the capability to set both time and date. The buttons to adjust
hour, minute, alarm time, day, month, and year will all be located on top. The side panels will feature hand-painted murals. One
of the side panels will be hinged, allowing a user to open it up and peek at the internal circuitry.

Tentative parts list:

    - PCB
    - ATMEGA4809 Microcontroller
    - 7 buttons: hour, minute, alarm, day, month, year, alarm stop.
    - 1 20x4 LED display
    - 1 speaker and/or alarm IC
    - 1 32k crystal oscillator
    - 2 thin wood panels (for front display and top button array)
    - 4 thick wood surfaces (2x4?) (for side panels, back, and bottom)
    - 4 rubber feet
    - 2 metal hinges
    - 1 small metal door knob
    - leads to connect the buttons to the PCB
    
    
Tentative tool list:

    - Atmel ICE uC programmer
    - Atmel Studio IDE
    - Large breadboard for testing, prototyping, and programming
    - Express PCB/SCH for schematic and PCB design
    - Logic probe to test high/low signals on the uC
    - LEDs to test program functions
