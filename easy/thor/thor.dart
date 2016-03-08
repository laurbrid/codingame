import 'dart:io';
import 'dart:math';

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/
void main() {
    List inputs;
    inputs = stdin.readLineSync().split(' ');
    int lightX = int.parse(inputs[0]); // the X position of the light of power
    int lightY = int.parse(inputs[1]); // the Y position of the light of power
    int initialTX = int.parse(inputs[2]); // Thor's starting X position
    int initialTY = int.parse(inputs[3]); // Thor's starting Y position

    // game loop
    int tx = initialTX, ty = initialTY;
    while (true) {
        int remainingTurns = int.parse(stdin.readLineSync()); // The remaining amount of turns Thor can move. Do not remove this line.

        // Write an action using print()
        // To debug: stderr.writeln('Debug messages...');
        String dir = '';
        if (ty < lightY)
        {
            ty++;
            dir = dir + 'S';
        }
        else if (ty > lightY)
        {
            ty--;
            dir = dir + 'N';
        }
        if (tx < lightX)
        {
            tx++;
            dir = dir + 'E';
        }
        else if (tx > lightX)
        {
            tx--;
            dir = dir + 'W';
        }

        print(dir); // A single line providing the move to be made: N NE E SE S SW W or NW
    }
}