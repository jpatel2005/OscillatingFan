# Oscillating Fan

Script and circuit for a simple oscillating fan that I built.

## Tinkercad
![Alt text](https://raw.githubusercontent.com/jpatel2005/OscillatingFan/refs/heads/main/circuit.png)

### Schematic

![PDF](https://github.com/jpatel2005/OscillatingFan/blob/main/schematic.pdf)

---

### Notes

The code using a basic polling style to listen for inputs from the IR remote. The controls are:
- Power button (on/off)
- FUNC/STOP button (enabling/disabling oscillation)

Two arduino boards were used since I didn't have a sufficient power source for safely providing enough current to the DC (fan) motor and servo motor without any stuttering occurring.
