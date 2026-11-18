# 4-LED-Scanner

An Arduino Uno project for ASL National Arena. Four LEDs scan from D4 to D7 and return continuously. The scan delay is adjustable through the Serial Monitor.

## Circuit overview

**Simulation:** [Open the Wokwi Project](https://wokwi.com/projects/481015589014784001)


## Hardware and Pin Mapping

| LED | Arduino pin | ATmega328P port bit |
|---|---:|---|
| LED 1 | D4 | PD4 |
| LED 2 | D5 | PD5 |
| LED 3 | D6 | PD6 |
| LED 4 | D7 | PD7 |

Each LED is connected through its own 220 Ω resistor to the assigned pin, with the LED cathode connected to GND.

## Scanner Sequence

`D4 → D5 → D6 → D7 → D6 → D5 → repeat`

Only one LED is intended to be ON at a time.

## Serial Speed Control

Open the Serial Monitor at **9600 baud**.

| Command | Action |
|---|---|
| `f` or `F` | Decrease delay by 50 ms (faster) |
| `s` or `S` | Increase delay by 50 ms (slower) |

Initial delay: **300 ms**. Minimum: **50 ms**. Maximum: **1000 ms**. After a recognized command, the firmware prints `New Speed: X ms`.

## AVR Register Implementation

The project uses `DDRD` to configure D4–D7 as outputs and `PORTD` to control the LEDs, instead of `pinMode()` and `digitalWrite()`.

```cpp
DDRD |= 0b11110000;   // Configure D4-D7 as outputs
PORTD &= ~0b11110000; // Turn D4-D7 LOW
PORTD |= (1 << pin);  // Turn on the selected LED
```

On the Arduino Uno (ATmega328P), D4–D7 correspond to PD4–PD7. Serial input is read using `Serial.read()` and speed feedback is printed using `Serial.println()`.

## Test Results

Verified in Wokwi:
- Forward and reverse LED scanning.
- `DDRD` output configuration.
- `PORTD` output control.
- Faster (`f`) and slower (`s`) commands.
- Serial speed feedback.

See [Test Results](docs/test-results.md) and `evidence/simulation/`.

## Repository Structure

```text
MSTI_Arena-ASL-04/
├── sketch.ino
├── diagram.json
├── wokwi.toml
├── README.md
├── docs/
│   ├── architecture.md
│   ├── pinout.md
│   └── test-results.md
└── evidence/
    └── simulation/
        ├── circuit-overview.png
        ├── scanner-operation.png
        ├── serial-speed-control.png
        └── simulation-results.md
```

## Challenge Requirement Alignment

| Requirement | Implementation |
|---|---|
| Arduino Uno | ATmega328P-based Uno |
| Four LEDs on D4–D7 | D4, D5, D6, D7 |
| Forward/reverse scanner | D4 → D5 → D6 → D7 → D6 → D5 |
| Pin direction register | `DDRD` |
| LED output register | `PORTD` |
| Serial command input | `Serial.read()` |
| Faster/slower commands | `f` / `s` |
| Speed feedback | `Serial.println()` |

No physical-hardware test is claimed.
