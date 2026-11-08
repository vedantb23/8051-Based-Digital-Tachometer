# 8051-Based Digital Tachometer for RPM Measurement

## Overview

A digital tachometer system based on the AT89C51 (8051) microcontroller.
It measures rotational speed by counting input pulses over a fixed time
interval and displays the calculated RPM on a 16×2 LCD.

The firmware is written in Embedded C using Keil µVision, and the
circuit is demonstrated through Proteus simulation.

## Features

-   AT89C51 (8051) microcontroller-based design
-   External interrupt (INT0) for pulse counting
-   Timer0 for fixed measurement interval
-   16×2 LCD interfacing in 8-bit mode
-   RPM calculation and display
-   Proteus-based circuit simulation

## Working Principle

1.  **Pulse Generation:** A CLOCK source in Proteus generates pulses
    representing rotational movement.

2.  **Pulse Counting:** The pulses are supplied to the 8051's INT0 pin
    and counted using the external interrupt mechanism.

3.  **Time Measurement:** Timer0 maintains a fixed measurement interval
    (gate time).

4.  **RPM Calculation:** At the end of the measurement interval, the
    microcontroller calculates rotational speed.

    `RPM = (Pulse Count × 60) / Gate Time (seconds)`

    This formula assumes one input pulse per revolution. If the sensor
    produces multiple pulses per revolution, the calculation must
    account for the pulses-per-revolution (PPR) value.

5.  **Display:** The calculated RPM value is displayed on the 16×2 LCD.

## Tools and Technologies

-   **Microcontroller:** AT89C51 (8051)
-   **Programming Language:** Embedded C
-   **Firmware Development:** Keil µVision
-   **Circuit Simulation:** Proteus Design Suite

## Project Structure

``` text
├── firmware/
│   ├── tachometer.c
│   └── tachometer.hex
├── simulation/
│   └── Digital_Tachometer.pdsprj
├── images/
│   ├── block_diagram.png
│   ├── circuit_diagram.png
│   └── lcd_output.png
└── README.md
```

*The directory and file names above are illustrative. Update them to
match the actual files in the repository.*

## Running the Simulation

1.  Open the Proteus project in the `simulation/` directory.
2.  Load the compiled HEX file into the AT89C51 microcontroller.
3.  Start the Proteus simulation.
4.  Adjust the CLOCK input frequency to generate different pulse rates.
5.  Observe the corresponding RPM readings on the LCD.
