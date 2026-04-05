# The Battle of Praxis Bay
Text-based choose-your-own-adventure game for Windows (it might compile for other operating systems, but I can't confirm that because I haven't tested it).

Developed as a submission for the B37VB Praxis Programming Course.

## Compilation Instructions
To compile using gcc, navigate to the game's directory and run the following command:
```
gcc main.c -o game.exe -I .\sdlbits\sdl3\include -I .\sdlbits\sdl3_ttf\include\ -L .\sdlbits\sdl3\lib -L .\sdlbits\sdl3_ttf\lib\ -l SDL3_ttf -l SDL3
```

Then to run the game, run the `game.exe` file.

Abdullah Bouteldja (ab4085@hw.ac.uk)
