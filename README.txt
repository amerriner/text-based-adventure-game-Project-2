Short text-based adventure game to practice working with mutexes and I/O operations in c.
The game will start you in a randomly generated room and build a matrix. You must find the "end room" by choosing which room to travel to next.
On top of running the room-navigation game, this game also is able to return the current time of day with a second thread/mutex.
This can be called at any time by entering "time."

To compile: 
1. gcc -o merrinea.buildrooms merrinea.buildrooms.c
2. gcc -o merrinea.adventure merrinea.adventure.c -lpthread

To run: first run merrinea.buildrooms (builds the room matrix) then run merrinea.adventure