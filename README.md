# Red-Light-Green-Light

### This is a recreation of "Red Light, Green Light" from Netflix's hit show "Squid Game."

### The game was developed on an Arduino in C++.

#### -------------------------------------------------------------------------------------------------------------
#### main.cpp is located in "src".
#### "SegmentDisplay" contains the class I created for segment displays for this project.

#### -------------------------------------------------------------------------------------------------------------
### Description of setup:

#### Controller peripherals:
* start button
* mpu sensor

The controller controls the player and start game. To start the game, press the start game button. To move the player, tilt the controller forwards or backwards 45 degrees.

#### Game board peripherals:
* ultrasonic sensor
* two servos (distance sensor & batter)
* seven segment display
* step motor
* red + green LEDs
* buzzer

There is an ultrasonic sensor on top of a servo which tracks movement of the player; the sensor swivels the ultrasonic sensor depending on the game state. The player must move within 8cm distance to win the game. If movement is detected, the batter servo will hit the player and the game is over. The movement is done from the stepper motor which is controlled by the mpu sensor. A seven segment display counts down the time left to reach the winning zone. The red and green LEDs show which state the game is in along with a sound from the buzzer.

###### P.S. Comment formatting translated to GitHub weirdly.
