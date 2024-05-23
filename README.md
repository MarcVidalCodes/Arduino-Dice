# Arduino-Dice

Dice Roll with Music
This is an Arduino project that simulates a dice roll with LEDs and plays a melody on a buzzer. The dice roll is triggered by an IR sensor.

Code Explanation
The code is divided into three main parts:

Melody Setup: This part of the code defines the notes of the melody that will be played on the buzzer. The melody and tempo are defined in the melody[] and tempo variables respectively.

Setup Function: This function runs once when the program starts. It sets the pin modes for the LEDs, IR sensor, and buzzer. It also plays a startup LED pattern and the melody on the buzzer.

Loop Function: This function runs repeatedly after the setup function. It checks if the IR sensor has been triggered. If it has, it simulates a dice roll by randomly turning on and off the LEDs and playing a tone on the buzzer. After the dice roll, it turns off all the LEDs and the buzzer.

Hardware Setup
Connect the LEDs to digital pins 2, 3, 4, and 5 on the Arduino.
Connect the IR sensor to digital pin 11.
Connect the buzzer to digital pin 12.
Usage
Power on the Arduino.
Wave your hand over the IR sensor to trigger a dice roll. The LEDs will light up to represent the number rolled, and a tone will play on the buzzer.
Note
The rollDice(int randomNum) function determines which LEDs should be turned on based on the number rolled. The number rolled is represented by the number of LEDs that are turned on.
 
![Screenshot 2024-05-23 at 5 28 27 PM](https://github.com/MarcVidalCodes/Arduino-Dice/assets/139398395/0b1c43a5-069c-4fa5-a5be-d7cca33ac3dd)

![IMG_7202](https://github.com/MarcVidalCodes/Arduino-Dice/assets/139398395/33c29599-dbc1-4758-9a60-01d4652430cc)
