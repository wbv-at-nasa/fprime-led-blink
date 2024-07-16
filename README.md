led-blink
=========

_(baby's first F' project)_

From following: https://fprime-community.github.io/fprime-workshop-led-blinker/

# System Requirements

| Requirement     | Description
|-----------------|------------
| ELECTRONICS-001 | The system shall blink an LED in response to a command.
| ELECTRONICS-002 | The blink rate of the LED shall be changeable in-flight.

# Software Requirements

| Requirement     | Derives From    | Verification | Description
|-----------------|-----------------|--------------|------------
| LED-BLINKER-001 | ELECTRONICS-001 | Unit Test    | The software shall start LED blinking in response to a command.
| LED-BLINKER-002 | ELECTRONICS-001 | Unit Test    | The software shall stop LED blinking in response to a command.
| LED-BLINKER-003 | ELECTRONICS-001 | Unit Test    | The software shall telemeter the current LED blinking state.
| LED-BLINKER-004 | ELECTRONICS-001 | Unit Test    | The software shall emit events when the blinking state changes.
| LED-BLINKER-005 | ELECTRONICS-002 | Unit Test    | The software shall store the blink interval as a parameter to the start LED blinking command.
| LED-BLINKER-006 | Electrical ICD  | Unit Test    | The software shall blink the LED using GPIO pin 13
