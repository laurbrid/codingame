import Foundation

public struct StderrOutputStream: OutputStreamType {
    public mutating func write(string: String) { fputs(string, stderr) }
}
public var errStream = StderrOutputStream()

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/

let inputs = (readLine()!).componentsSeparatedByString(" ")
let lightX = Int(inputs[0])! // the X position of the light of power
let lightY = Int(inputs[1])! // the Y position of the light of power
let initialTX = Int(inputs[2])! // Thor's starting X position
let initialTY = Int(inputs[3])! // Thor's starting Y position

// game loop
var tx = initialTX
var ty = initialTY
while true {
    let remainingTurns = Int(readLine()!)! // The remaining amount of turns Thor can move. Do not remove this line.

    // Write an action using print("message...")
    // To debug: debugPrint("Debug messages...", toStream: &errStream)
    var dir = ""
    if ty < lightY {
        ty = ty + 1
        dir = dir + "S"
    }
    else if ty > lightY {
        ty = ty - 1
        dir = dir + "N"
    }
    if tx < lightX {
        tx = tx + 1
        dir = dir + "E"
    }
    else if tx > lightX {
        tx = tx - 1
        dir = dir + "W"
    }

    print(dir) // A single line providing the move to be made: N NE E SE S SW W or NW
}