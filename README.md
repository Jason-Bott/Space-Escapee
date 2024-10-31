# Space Escapee

## Introduction

This is my c++ game called Space Escapee.
It is a classic arcade style game in which the player is aiming to escape through a series of portals.
Each portal leads to the next level containing more and more enemies to evade or destroy.
The player is however on a time limit and should they run out of time they will have to restart from level 1.

### Repository Setup

The file titled COMP3016_CW1 contains my visual studio solution, the source code, for the game.
The file titled Space Escapee contains an executable and all needed assets/dependencies to run the game. (Download this if you wish to play)
The other files are for this document.

### Running The Executable

To run the executable and play the game you will first need to download the game folder titled Space Escapee.
Once downloaded if zipped make sure to extract all.
With the folder find the file named Space Escapee.exe and run it.
All assets and dependencies needed should be in the folder and the game should run.

## Video Link

Link Here

## Dependencies Used

### SDL2 (Simple DirectMedia Layer)

- Used for rendering graphics, handling inputs, managing game windows and outputting sound.
- Modules Used:
	- SDL.h
	- SDL_image.h
	- SDL_mixer.h

### C++ Standard Library

- Used for managing dynamic arrays, random number generation and debugging with console outputs.
- Modules Used:
	- <vector>
	- <cstdlib>
	- <ctime>
	- <iostream>

## Game Programming Patterns

### Component

The use of the component pattern can be seen in my enemy classes. I have a few classes of different enemy types 
(Spinner, Patroller, Roamer) where each class is a component that can be added to the enemy class to give each 
enemy type its own unique movement pattern all while sharing other attributes and functions with the base class.

## Game Mechanics

### Maze Generation

- This feature randomly generates the maze which the player navigates with a random selection of horizontal and vertical walls.
	- The Maze class on creation generates a boolean array for both horizontal and vertical walls.
	- Each wall in the array has a 30% chance to be made true apart from the outside walls which will always be assigned to true.
	- With these arrays the Render function then displays any wall set to true.

### Player Movement

- This feature allows the player to navigate through the maze and interact with walls and portals.
	- The Player class contains functions to rotate and move the player in 4 directions.
	- These functions are called from the main Game class which checks the user inputs.
	- During the function a check for wall collision is also check and movement is rejected if a wall is present.
	- The Player class also contains a function called Blink which allows the player to teleport a set distance instantaneously.
	- This blink ability has a cooldown and is meant as an extra movement ability to allow the player to access areas on other sides of walls or generally speed up travel.

### Shooting

- This feature allows the player and enemies to shoot lasers in the direction they are facing.
	- Both the Player class and Enemy class contain a Shoot function which upon being called creates a laser in their laser array.
	- The Player Shoot function is called when the Space key is pressed and the Enemy function is continuously called but only fires at the enemies fire rate.
	- The Laser class handles the lasers movement and collisions once fired.
	- Movement occurs in one direction based on the initial angle of the player/enemy and this doesn't change once fired.
	- The same collision detection for walls is used as the players wall detection however the laser is destroyed on collision.
	- Enemy lasers will also check for collision with the player and if this happens the game is over as the player has died.
	- Player lasers will also check for collision with any enemies and if this happens the enemy is destroyed and the score is increased.

### Timer

- This feature adds a countdown timer on the screen.
	- The Timer class constantly tracks the remaining time and updates every second.
	- The class contains two other functions AddTime and Render.
	- AddTime adds time to the timer when the player enters the portal to the next level.
	- Render renders the time in the top right corner of the window.

### Portal

- This feature adds a portal which once reached by the player loads the next level.
	- The Portal class randomly places the portal somewhere in the maze and a check is made to ensure the portal is not placed on top of the player.
	- There is a CheckExit function Game.cpp that checks the players position against the portal position with the LevelComplete function being called if the player has made it.

### Enemies

- This feature adds enemies for the player to either avoid or destroy.
	- The Enemy class has functions for Shooting and Rendering which is used by all types of enemies.
	- The Enemy class has a texture and fire rate which must be set when created which are used in the two functions.
	- Each type of enemy has a class, there are 3 in the game currently (Spinner, Roamer and Patroller).
	- Each enemy type has its own Move function allowing them to have unique movement patterns.
	- The enemy type classes are also where attributes in the Enemy class are set (texture, fire rate, move speed).

## Sample Screens

### Main Menu

![MainMenu](/SampleScreens/menu.png)

### Moving and Shooting

![MovingAndShooting](/SampleScreens/MoveAndShoot.gif)

### Blink Ability

![Blink](/SampleScreens/Blink.gif)

### Maze Generation / Portal Usage

![MazeAndPortal](/SampleScreens/MazePortal.gif)

### Enemies

![Enemies](/SampleScreens/Enemies.gif)

### Game Over

![Death](/SampleScreens/Death.gif)

## Exception Handling

The main example of exception handling in my game can be seen anywhere a texture, sound or piece of music is loaded.
Every time a file is called to be loaded the next statement checks if this has occurred correctly.
For example when the player is created and its texture loaded, if the texture doesn't load for whatever reason the game is exited and an error displayed.

![ExceptionExample](/SampleScreens/exceptionExample.png)

## Evaluation

### Achievements

I am beyond happy with the progress I have made with learning how to create a game in c++ without a game engine.
My c++ skills are much better now and I also have a good understanding of how to use dependencies like SDL much more.
I am pleased with the game as a whole and all the features implemented.

### What I Would Do Differently

Although I am very pleased with what I have produced I believe there are improvements that could be made.
Firstly I believe I could probably use more Game Programming Patterns to improve overall performance and gameplay.
I also believe that now that I have more knowledge with c++ and SDL I would be able to create 'tidier' code by using classes, functions and inheritance more appropriately.