# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
# ---
# Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.

# lightX: the X position of the light of power
# lightY: the Y position of the light of power
# initialTX: Thor's starting X position
# initialTY: Thor's starting Y position
read lightX lightY initialTX initialTY

# game loop
tx=$initialTX
ty=$initialTY
while true; do
    # remainingTurns: The remaining amount of turns Thor can move. Do not remove this line.
    read remainingTurns

    # Write an action using echo
    # To debug: echo "Debug messages..." >&2
    dir=""
    if [ $ty -lt $lightY ]; then
        dir="${dir}S"
        ty=$((ty+1))
    elif [ $ty -gt $lightY ]; then
        dir="${dir}N"
        ty=$((ty-1))
    fi        
    if [ $tx -lt $lightX ]; then
        dir="${dir}E"
        tx=$((tx+1))
    elif [ $tx -gt $lightX ]; then
        dir="${dir}W"
        tx=$((tx-1))
    fi        
    echo $dir # A single line providing the move to be made: N NE E SE S SW W or NW
done