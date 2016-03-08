input = new Scanner(System.in);

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/

lightX = input.nextInt() // the X position of the light of power
lightY = input.nextInt() // the Y position of the light of power
initialTX = input.nextInt() // Thor's starting X position
initialTY = input.nextInt() // Thor's starting Y position

// game loop
tx = initialTX
ty = initialTY
while (true) {
    remainingTurns = input.nextInt() // The remaining amount of turns Thor can move. Do not remove this line.

    dir = ""
    if (ty < lightY) {
        ty++
        dir += "S"
    } else if (ty > lightY) {
        ty--
        dir += "N"
    }
    
    if (tx < lightX) {
        tx++
        dir += "E"
    } else if (tx > lightX) {
        tx--
        dir += "W"
    }
    // Write an action using println
    // To debug: System.err << "Debug messages...\n"

    println dir // A single line providing the move to be made: N NE E SE S SW W or NW
}