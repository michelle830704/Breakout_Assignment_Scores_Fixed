# Breakout_Assignment_Scores_Fixed


A C++ Breakout game made with the Play library. Move the paddle with the left and right arrow keys to bounce the ball and break bricks. Each broken brick adds one point.

When the ball leaves the bottom of the screen, the score is added to the high scores and a new round begins. High scores are stored in a dynamically allocated array, loaded from `highscores.txt` when the game starts, and saved when it exits. The allocated memory is released before exit.

