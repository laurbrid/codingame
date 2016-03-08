import java.util.*;
import java.io.*;
import java.math.*;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/
class Player {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int lightX = in.nextInt(); // the X position of the light of power
        int lightY = in.nextInt(); // the Y position of the light of power
        int initialTX = in.nextInt(); // Thor's starting X position
        int initialTY = in.nextInt(); // Thor's starting Y position

        // game loop
        int tx = initialTX, ty = initialTY;
        while (true) {
            int remainingTurns = in.nextInt(); // The remaining amount of turns Thor can move. Do not remove this line.

            // Write an action using System.out.println()
            // To debug: System.err.println("Debug messages...");
            String dir = "";
            if (ty < lightY)
            {
                ty++;
                dir = dir.concat("S");
            }
            else if (ty > lightY)
            {
                ty--;
                dir = dir.concat("N");
            }
            
            if (tx < lightX)
            {
                tx++;
                dir = dir.concat("E");
            }
            else if (tx > lightX)
            {
                tx--;
                dir = dir.concat("W");
            }

            System.out.println(dir); // A single line providing the move to be made: N NE E SE S SW W or NW
        }
    }
}