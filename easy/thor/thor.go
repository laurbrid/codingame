package main

import "fmt"
//import "os"

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/

func main() {
    // lightX: the X position of the light of power
    // lightY: the Y position of the light of power
    // initialTX: Thor's starting X position
    // initialTY: Thor's starting Y position
    var lightX, lightY, initialTX, initialTY int
    fmt.Scan(&lightX, &lightY, &initialTX, &initialTY)
    
    var tx, ty int = initialTX, initialTY
    for {
        // remainingTurns: The remaining amount of turns Thor can move. Do not remove this line.
        var remainingTurns int
        fmt.Scan(&remainingTurns)
        
        var dir string = ""
        if ty < lightY {
            ty++
            dir += "S"
        } else if ty > lightY {
            ty--
            dir += "N"
        }
        if tx < lightX {
            tx++
            dir += "E"
        } else if tx > lightX {
            tx--
            dir += "W"
        }
        // fmt.Fprintln(os.Stderr, "Debug messages...")
        
        fmt.Println(dir) // A single line providing the move to be made: N NE E SE S SW W or NW
    }
}