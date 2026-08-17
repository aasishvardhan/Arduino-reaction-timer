# Arduino Reaction Timer

An Arduino-based reaction timer game that measures how quickly a user can respond to a button press after a countdown.

The project uses a potentiometer to set the countdown duration, a 4-digit 7-segment display to show the timer and reaction time, LEDs to indicate the countdown stage, and a buzzer to provide audible feedback.

## Features

* Adjustable countdown duration
* 4-digit 7-segment display
* Reaction time measurement in milliseconds
* Three reaction-time attempts
* Displays the best reaction time
* Red, yellow, and green countdown indicators
* Buzzer feedback

## Components

* Arduino board
* 4-digit 7-segment display
* Potentiometer
* Push button
* Red LED
* Yellow LED
* Green LED
* Buzzer
* Current-limiting resistors
* Jumper wires
* Breadboard

## Pin Configuration

| Component               | Arduino Pin                   |
| ----------------------- | ----------------------------- |
| 7-segment segments      | D3, D7, D10, D12, D13, D4, D9 |
| 7-segment digit control | D2, D5, D6, D8                |
| Decimal point           | D11                           |
| Red LED                 | A2                            |
| Yellow LED              | A3                            |
| Green LED               | A4                            |
| Buzzer                  | A0                            |
| Potentiometer           | A1                            |
| Push button             | A5                            |

## How It Works

### 1. Set the Countdown

The potentiometer is used to select the countdown duration.

The available countdown time is approximately 3–10 seconds.

The selected value is displayed on the 4-digit 7-segment display.

Pressing the button starts the countdown.

### 2. Countdown

The countdown progresses through three stages:

* **Red LED:** first stage
* **Yellow LED:** second stage
* **Green LED:** final stage

The buzzer provides an audible indication between stages and when the countdown finishes.

### 3. Reaction Test

After the countdown finishes, the Arduino starts measuring the time until the user presses the button.

The reaction time is measured using `millis()` and displayed on the 7-segment display in milliseconds.

### 4. Best of Three

The reaction test is performed three times.

After all three attempts, the program compares the recorded reaction times and displays the fastest result.

## Timing

The reaction time is calculated using the Arduino's `millis()` function.

This allows the program to measure the elapsed time between the end of the countdown and the user's button press without using a separate timer module.

## Project Structure

```text
Arduino-reaction-timer/
├── reaction_timer.ino
├── README.md
└── demo/
    └── Project_Reaction_timer.mp4
```

## Demo

A demonstration video is included in the `demo` folder.

## Possible Improvements

* Add a random delay before the reaction test starts
* Add a false-start detection system
* Keep a high-score record
* Add more reaction-time rounds
* Display the average reaction time
* Add a reset button
* Improve the 7-segment display multiplexing
# Arduino-reaction-timer
Arduino-based reaction timer game with adjustable countdown, 7-segment display, LEDs, and buzzer.
