![C/C++ CI](https://github.com/tobias-wilfert/SpaceInvaders/workflows/C/C++%20CI/badge.svg)

# SpaceInvaders
Programming Project 2019 - 2020 by Tobias Wifert

## Installation
The project comes with a run.sh file that will build the project in a build directory and subsequently will run SpaceInvaders with 3 xml files (representing levels) as input the levels are sorted in increasing difficulty.

## Game Play
Starting the game will display the start screen reading SPACE INVADERS. **Upon any keyboard input the first level will start.**

The space gun is controlled with the **left and right arrow keys** to move the space gun left and right respectively. The space gun is fired using **the space bar** but be aware there is a cool-down so that the player can not spam fire. When the player is hit it will put the space gun into a broken state and reduce the health counter, in this state the space gun cannot move! To repair the space gun simply press **the space bar**.

The objective of the game is to kill all the enemies before they reach Earth (the bottom of the screen) if the player succeeds in doing this the next level will launch till all the levels provided as parameters to the game have been mastered. In this event the player will see the victory screen displaying his score.

### Technicalities
1. Bullets are not indestructible, that is, bullets colliding mid air will damage both bullets. In the sample levels the health points of all bullets are equal to the attack points this has the effect that an enemy bullet and player bullet when collide destroy each other

2. Shields will take and deal damage just like bullets when aliens collide with them.

3. Player bullets do not pass through shields, rather they damage the shield just like enemy bullets would i.e. friendly fire is enabled.

4. When the space gun is in a broken state bullets can not damage it anymore so it may sometimes be wise to not immediately repair but rather wait till a follow up bullet passed through the space gun.

5. When an enemy hits the player both take damage.

6. Different aliens are worth different points the exact values are left for the player to discover.
