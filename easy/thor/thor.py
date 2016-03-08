import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
# ---
# Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.

# light_x: the X position of the light of power
# light_y: the Y position of the light of power
# initial_tx: Thor's starting X position
# initial_ty: Thor's starting Y position
light_x, light_y, initial_tx, initial_ty = [int(i) for i in input().split()]

# game loop
tx = initial_tx
ty = initial_ty
while True:
    remaining_turns = int(input())  # The remaining amount of turns Thor can move. Do not remove this line.

    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr)
    dir = ""
    if ty < light_y: 
        ty = ty + 1
        dir = dir + "S"
    elif ty > light_y:
        ty = ty - 1
        dir = dir + "N"
        
    if tx < light_x:
        tx = tx + 1
        dir = dir + "E"
    elif tx > light_x:
        tx = tx - 1
        dir = dir + "W"

    # A single line providing the move to be made: N NE E SE S SW W or NW
    print(dir)