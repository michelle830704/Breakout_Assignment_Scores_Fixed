BREAKOUT ASSIGNMENT

Open HelloWorld.slnx from THIS folder in Visual Studio.
Choose Build > Rebuild Solution, then press F5.
The game opens at 640 x 360 pixels (display scale 2).

The Play build on your machine displays the drawing buffer vertically inverted.
The drawing calls in this version flip the y coordinates so the visible result is:
- Brick rows start at y=25 and extend downward to about y=119.
- The blue paddle is centered at y=335, near the BOTTOM.
- The ball starts above the paddle and moves toward the bricks.
- Current score appears bottom left; high scores appear bottom right.

Move the paddle with LEFT and RIGHT arrows. Press ESCAPE to exit.
When the ball goes below the screen, the score is inserted in the
high score array and a new round begins. On exit, scores are saved
to highscores.txt in Visual Studio's working directory.

Score labels are inset from both bottom corners so they remain visible.

HighScores owns an unsigned int* array. It starts with capacity 5,
resizes on loading if the file contains more than 5 numbers, and
releases the array in its destructor.

The Data/Sprites and Data/Audio folders must stay in this folder.
