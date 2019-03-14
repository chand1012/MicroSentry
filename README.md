# MicroSentry
Tiny Simple Arduino Sentry.

## to do

- revert back to the old style of motion where the servo moves in increments of 1 when the key is pressed down until a stop signal is sent to the arduino. This means all of the logic will be done on the board rather than on the javascript side meaning it will be faster because network latency is a thing. Copy it from the wifi jeep project. Do the same for the trigger because it will only shoot once anyway.