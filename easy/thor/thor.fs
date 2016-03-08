(* Auto-generated code below aims at helping you parse *)
(* the standard input according to the problem statement. *)
(* --- *)
(* Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders. *)
open System

(* lightX: the X position of the light of power *)
(* lightY: the Y position of the light of power *)
(* initialTX: Thor's starting X position *)
(* initialTY: Thor's starting Y position *)
let token = (Console.In.ReadLine()).Split [|' '|]
let lightX = int(token.[0])
let lightY = int(token.[1])
let initialTX = int(token.[2])
let initialTY = int(token.[3])

(* game loop *)
let mutable tx = initialTX
let mutable ty = initialTY
while true do
    let remainingTurns = int(Console.In.ReadLine()) (* The remaining amount of turns Thor can move. Do not remove this line. *)
    
    (* Write an action using printfn *)
    (* To debug: Console.Error.WriteLine("Debug message") *)
    let mutable dir = ""
    if ty > lightY then
        dir <- dir + "N"
        ty <- ty - 1
    else if ty < lightY then
        dir <- dir + "S"
        ty <- ty + 1
        
    if tx < lightX then 
        dir <- dir + "E"
        tx <- tx + 1
    else if tx > lightX then
        dir <- dir + "W"
        tx <- tx - 1
    
    Console.WriteLine dir (* A single line providing the move to be made: N NE E SE S SW W or NW *)
    ()
