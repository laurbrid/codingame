#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/
int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    scanf("%d%d%d%d", &lightX, &lightY, &initialTX, &initialTY);

    // game loop
    int tx = initialTX, ty = initialTY;    
    while (1) {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        scanf("%d", &remainingTurns);

        // Write an action using printf(). DON'T FORGET THE TRAILING \n
        // To debug: fprintf(stderr, "Debug messages...\n");
        char dir[3] = "";
        if (ty < lightY)
        {
            ty++;    
            strcat(dir, "S");
        }
        else if (ty > lightY)
        {
            ty--;            
            strcat(dir, "N");
        }

        if (tx < lightX)
        {
            tx++;            
            strcat(dir, "E");
        }
        else if (tx > lightX)
        {
            tx--;            
            strcat(dir, "W");
        }

        printf("%s\n", dir); // A single line providing the move to be made: N NE E SE S SW W or NW
    }

    return 0;
}