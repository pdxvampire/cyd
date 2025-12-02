# cyd01 - set up a basic dev environment with a simple board test

## Setup
In Arduino IDE turn on Serial Monitor via Tools -> Serial Monitor.

## Expected Behavior
When you upload the sketch you should see the onboard LEDs blink 3 times, plus logging in the Serial Monitor.

## Sample Output From Serial Monitor
````
18:33:01.213 -> x�x�x�x��xxxx�x����x������x�x�        
18:33:01.575 ->         ####### Done initializing serial communication. ######################
18:33:01.608 ->     Exiting InitializeSerialCommunication
18:33:01.608 ->     Entering InitializeOnboardLEDs
18:33:01.608 ->     Exiting InitializeOnboardLEDs
18:33:01.608 -> Exiting setup
18:33:01.608 -> Entering BlinkOnboardLEDs
18:33:01.608 ->     Entering TurnOnOnboardLEDs
18:33:01.608 ->         Turning on GPIO 4
18:33:01.608 ->         Turning on GPIO 16
18:33:01.608 ->         Turning on GPIO 17
18:33:01.608 ->     Exiting TurnOnOnboardLEDs
18:33:01.909 ->     Entering TurnOffOnboardLEDs
18:33:01.909 ->         Turning off GPIO 4
18:33:01.909 ->         Turning off GPIO 16
18:33:01.909 ->         Turning off GPIO 17
18:33:01.942 ->     Exiting TurnOffOnboardLEDs
18:33:01.942 -> Exiting BlinkOnboardLEDs
18:33:02.205 -> Entering BlinkOnboardLEDs
18:33:02.205 ->     Entering TurnOnOnboardLEDs
18:33:02.238 ->         Turning on GPIO 4
18:33:02.238 ->         Turning on GPIO 16
18:33:02.238 ->         Turning on GPIO 17
18:33:02.238 ->     Exiting TurnOnOnboardLEDs
18:33:02.536 ->     Entering TurnOffOnboardLEDs
18:33:02.536 ->         Turning off GPIO 4
18:33:02.536 ->         Turning off GPIO 16
18:33:02.536 ->         Turning off GPIO 17
18:33:02.536 ->     Exiting TurnOffOnboardLEDs
18:33:02.536 -> Exiting BlinkOnboardLEDs
18:33:02.835 -> Entering BlinkOnboardLEDs
18:33:02.835 ->     Entering TurnOnOnboardLEDs
18:33:02.835 ->         Turning on GPIO 4
18:33:02.835 ->         Turning on GPIO 16
18:33:02.835 ->         Turning on GPIO 17
18:33:02.868 ->     Exiting TurnOnOnboardLEDs
18:33:03.165 ->     Entering TurnOffOnboardLEDs
18:33:03.165 ->         Turning off GPIO 4
18:33:03.165 ->         Turning off GPIO 16
18:33:03.165 ->         Turning off GPIO 17
18:33:03.165 ->     Exiting TurnOffOnboardLEDs
18:33:03.165 -> Exiting BlinkOnboardLEDs
````