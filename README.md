# Embedded Lift Overload Detector

An embedded lift overload detection system developed using the LPC2138 ARM7 microcontroller, ADC0804 analog-to-digital converter, LCD, buzzer, and motor control circuit.

The project is programmed in Embedded C using Keil µVision and simulated using Proteus.

## Project Overview

The system monitors a simulated lift load and compares the measured value against a predefined maximum load threshold of 600 kg.

The ADC0804 converts the analog output of the load-sensing input into an 8-bit digital value. The LPC2138 processes this value, displays the load status, and controls the motor and buzzer according to the configured overload condition.

When an overload is detected, the controller activates the buzzer and disables the motor command to demonstrate overload protection.

**Note:** The load input and protection behavior are demonstrated in simulation. This project is an educational prototype, not a certified lift safety system.

## Features

- Lift load monitoring using an analog input.
- ADC0804-based analog-to-digital conversion.
- LPC2138 ARM7 microcontroller control.
- LCD-based load and status indication.
- Motor control through a ULN2003A driver.
- Buzzer alert during overload conditions.
- UART serial monitoring at 9600 baud.
- Embedded C firmware developed in Keil µVision.
- Circuit simulation using Proteus.

## Components Used

| Component | Purpose |
|---|---|
| LPC2138 | Main controller |
| ADC0804 | Converts analog load signal to digital data |
| Load-sensing input | Represents the measured load in simulation |
| 16×2 LCD | Displays load information and status |
| ULN2003A | Motor-driver interface |
| DC motor | Represents lift motor operation |
| Buzzer | Overload alert |
| Virtual terminal | Serial monitoring |
| Supporting components | Power, interfacing, and signal conditioning |

## Software and Tools

- **Keil µVision:** Embedded C development and compilation.
- **Proteus:** Circuit design and simulation.
- **Embedded C:** Firmware programming.

## Pin Connections

The following connections are based on the project configuration discussed during development. Verify them against the final Proteus schematic and Keil source before publishing.

### 1. ADC0804 to LPC2138

| ADC0804 signal | LPC2138 pin |
|---|---|
| D0–D7 | P1.16–P1.23 |
| WR | As configured in the circuit |
| RD | As configured in the circuit |
| INTR | As configured in the circuit |
| VIN+ | Analog load-sensing signal |
| VIN− | Ground, according to the circuit configuration |

The ADC0804 converts the load-sensing voltage into a digital value for the microcontroller.

### 2. Motor Control

| Component signal | Connection |
|---|---|
| LPC2138 motor-control output | P0.7 |
| Driver | ULN2003A |
| Driver output | Motor connection |

The ULN2003A provides an interface between the controller's output and the motor circuit. The motor must use a suitable supply, with appropriate protection and common grounding where required.

### 3. Buzzer

| Signal | LPC2138 pin |
|---|---|
| Buzzer control | P0.10 |

The controller uses the buzzer to indicate an overload condition. The actual output polarity depends on the driver and buzzer circuit.

### 4. UART

| UART signal | LPC2138 pin |
|---|---|
| UART0 TXD | P0.0 |
| UART0 RXD | P0.1 |

UART0 is configured for serial communication at 9600 baud, if enabled in the firmware.

## Working Principle

1. The load-sensing input produces an analog voltage corresponding to the simulated load.
2. The ADC0804 converts the analog voltage into an 8-bit digital value.
3. The LPC2138 reads and processes the ADC output.
4. The firmware converts the reading into a load value using the configured calibration.
5. The LCD displays the load and the corresponding status.
6. The controller compares the measured load with the 600 kg threshold.
7. If the load exceeds the threshold, the buzzer activates and the motor command is disabled.
8. UART0 can transmit status information for monitoring.

## Overload Detection Logic

The configured maximum load threshold is **600 kg**.

| Load condition | System response |
|---|---|
| Below 600 kg | Normal operation, subject to the firmware logic |
| At or above 600 kg | Verify the exact comparison in the source code |
| Above the configured threshold | Overload protection response, if implemented by the firmware |

The precise boundary behavior at 600 kg depends on whether the code uses `>` or `>=`. Confirm this in the actual source before treating the table as a verified test result.

## Simulation and Verification

The project is intended to be evaluated using Proteus simulation.

Suggested verification tests:

1. Apply a simulated load below the configured threshold.
2. Observe the LCD load reading and status.
3. Increase the input until the overload threshold is reached.
4. Check the buzzer response.
5. Confirm that the motor command is disabled during overload.
6. Inspect UART output at 9600 baud, if available.

Add screenshots from the actual simulation to document the observed behavior. Do not report a test as successful unless you have verified it.

## Project Structure

```text
embedded-lift-overload-detector/
├── README.md
├── KEIL/
│   └── Keil project and source files
├── PROTEUS/
│   └── Proteus simulation files
├── Images/
│   ├── circuit.png
│   ├── keil.png
│   └── output.png
└── docs/
    └── project-report.pdf
```

Use the actual filenames in your repository and omit any folders you do not have.

## Limitations

- The system has been developed for software simulation.
- Physical hardware implementation and testing have not been claimed.
- Load measurement accuracy depends on sensor calibration and the analog input configuration.
- The 600 kg threshold is a demonstration setting, not a validated lift capacity.
- This prototype must not be used as the sole safety mechanism in a real lift.

## Future Improvements

- Interface a calibrated load cell with a suitable signal-conditioning circuit.
- Improve load calibration and measurement accuracy.
- Add overload history and fault logging.
- Implement a manual reset and fault indication.
- Validate the design on physical hardware under controlled conditions.

## Author

Jay Rana
