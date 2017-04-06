## Computer Architecture Project 2: MSP430 Games

This project was created by Jose Perez (josegperez@mail.com). Special thanks to all the resources cited in the code and the template code provided by our TAs and professor.

This project was created for the TI MSP430 with a custom EduKit BoosterPack that contains 4 buttons, a buzzer, and an LCD screen.

This project contains the following files:
* project_main.c:

 Initializes all the components of the program such as timers and registers.

* state_machine.h:

 Allows the timer library to update states.

* state_machine.c:

 Manages the internal state of the program and allows the program to run like an automata. Contains the code for the games.

* buzzer.h:

 Allows other components to modify the internal state of the buzzer.

* buzzer.c:

 Implements the code required for the buzzer to play notes as well as songs. Manages the states of the buzzer.

* pitches.h:

 Contains definitions of notes for melody playback. Retrieved from Arduino's ToneMelody demo. It matches the table of frequencies for notes in a piano.

* switches.h:

 Allows other components to check the state of the buttons/switches. 

* switches.c:

 Contains the implementation needed to get the state of all the buttons in the top and bottom board.

* timer.h:

 Allows other components to change the state of the timer and access to the pseudo-random number generator.

* timer.c:

 Controls the timer used by the state machine of the program as well as an implementation of a pseudo-random number generator


When the program is first loaded it plays an intro medley and then proceeds to the game menu. The intro medley can be skipped by pressing any button. When in the game menu the LEDs flash back and forth. There are only 2 games implemented:

* Piano Game (Top Button S1):

 The top 4 keys are piano keys. Press them to play a note. They can be held as well. Only 1 note can be played at a time.

 You can go back to the game menu anytime by pressing the bottom button.

* LED Game (Top Button S2):

 When the game starts a random interval is chosen.

 When the interval passes the buzzer beeps and the lights turn on.

 You are given a small window to press the 2nd top button (S2) as soon as you hear the signal.

 If you succeed the green led turns on, otherwise the red led turns on.

 If you press the buttons too early you lose the game as well.

 Once the game is over you can go back to the game menu by pressing the bottom button or try again by pressing the 4th top button (S4)


To compile:
~~~
$ make
~~~

To install in the MSP430 (requires it to be connected to the computer):
~~~
$ make load
~~~

To delete binaries:
~~~
$ make clean
~~~