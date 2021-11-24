# door-alarm
Using an arduino to create a simple door alarm system
A simple alarm system for a door, using an Arduino Uno. This is a proof of concept and not a fully fledged product.

## Introduction
This project uses an Arduino UNO for reading the magnetic sensor at the door, and responds accordingly with both audio and visuals.

This could be used in a further project, since it's quite small and responsive. It uses the Serial Monitor in the terminal to monitor the state of the door and the alarm, and uses a buzzor and LEDs for outside the terminal.

The components used are:
- Arduino UNO
- 2 Resistors
- Button *(Pin 2)*
- Buzzor *(Pin 3)*
- Magnetic sensor *(Pin 4)*
- Green LED *(Pin 12)*
- Red LED *(Pin 13)*

## Customization

The code is written in `src/main.cpp`, where as the rest is from the [PlatformIO extension](https://platformio.org/) on VS Code, which was used to code and execute the Arduino code.

#### 1. Pin assignation

The pins responding to the different components, can be changed if need be under `// Pins`. Here's the current setup:
```
(Pin  2) - Button
(Pin  3) - Buzzor 
(Pin  4) - Magnetic sensor
(Pin 12) - Green LED
(Pin 13) - Red LED
```

#### 2. Time constants.

The different constants responsible for sounds, blinking lights and sensor responsiveness. Can be tricky to modify.
```
blink_time = 375ms
check_time = 100ms
alarm_time = blink_time / 1.3
alarm_wait = 30s
```
Note: `alarm_time` should always be longer than `blink_time`, since the the first determines how long each note is played, and the latter how long there is to the next note.
`check_time` is how long the wait between checking the status of the inputs.
`alarm_wait` is how long to wait before initiating the alarm, letting the user deactivate the alarm before prompting. This, unlike the others, is in seconds rather than milliseconds.

#### 3. Music notes

The `tone` functions are coded one-by-one, so to modify sound and length one need to do so in the function itself.
The structure is `tone(output, frequenzy, duration) // Type of note`, and can be found in the functions:
- openingTune()
- closingTune()
- alarmTune()
- alarmPrompt()
