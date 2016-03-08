STDOUT.sync = true # DO NOT REMOVE
# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
# ---
# Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.

# light_x: the X position of the light of power
# light_y: the Y position of the light of power
# initial_tx: Thor's starting X position
# initial_ty: Thor's starting Y position
@light_x, @light_y, @initial_tx, @initial_ty = gets.split(" ").collect {|x| x.to_i}

@tx = @initial_tx
@ty = @initial_ty
# game loop
loop do
    remaining_turns = gets.to_i # The remaining amount of turns Thor can move. Do not remove this line.
    
    # Write an action using puts
    # To debug: STDERR.puts "Debug messages..."
    
    dir = ""
    if @ty < @light_y then
        dir = dir + "S"
        @ty = @ty + 1
    elsif @ty > @light_y then
        dir = dir + "N"
        @ty = @ty - 1        
    end    
    if @tx < @light_x then
        dir = dir + "E"
        @tx = @tx + 1
    elsif @tx > @light_x then
        dir = dir + "W"
        @tx = @tx - 1
    end
    
    puts dir # A single line providing the move to be made: N NE E SE S SW W or NW
end