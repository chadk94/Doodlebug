# Doodlebug
An evolutionary style simulation
Creates a grid of size 20 x 20 in which doodlebugs and ants look to survive in a predator/prey relationship. The game begins with 5 doodlebugs and 100 ants.

On a turn by turn basis (controlled by the user) the organisms cycle via the below patterns: 

This program also outputs a csv file tracking the number of ants and doodlebugs alive at each turn, showcasing the natural predator-prey cycle. 

Ant Specifications:
Every "turn" an ant moves to a neighboring cell randomly, if cell is full the ant stays. 
If the ant has been alive for three turns, it breeds and creates a new ant, then resets its counter.

Doodlebug Specifications:
Every "turn" a doodlebug looks to move to a cell that contains an ant, and if there is one consumes it
If a doodlebug survives for 8 turns it breeds and creates a new doodlebug, then resets its counter.
A doodlebug starves if it does not eat for 3 steps.

Doodlebugs move first.
