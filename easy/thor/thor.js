/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/

var inputs = readline().split(' ');
var lightX = parseInt(inputs[0]); // the X position of the light of power
var lightY = parseInt(inputs[1]); // the Y position of the light of power
var initialTX = parseInt(inputs[2]); // Thor's starting X position
var initialTY = parseInt(inputs[3]); // Thor's starting Y position

// game loop
var tx = initialTX;
var ty = initialTY
while (true) {
    var remainingTurns = parseInt(readline()); // The remaining amount of turns Thor can move. Do not remove this line.

    // Write an action using print()
    // To debug: printErr('Debug messages...');
    var dir = ''
    if (ty < lightY)
    {
        ty++;
        dir += 'S';
    }
    else if (ty > lightY)
    {
        ty--; 
        dir += 'N';
    }
    
    if (tx < lightX)
    {
        tx++;
        dir += "E";
    }
    else if (tx > lightX)
    {
        tx--;
        dir += "W";
    }

    print(dir); // A single line providing the move to be made: N NE E SE S SW W or NW
}