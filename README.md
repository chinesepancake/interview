The task is to implement an algorithm to rank two poker hands, which one wins. In the test, you get following for example following hands:
KQ23Q and TA3J7, where A = Ace, K = King, Q = Queen, J = Jack, T = Ten and 1…9 is according number.
So the algorithm should be able to say that the first hand wins (two queens vs. ace as high card).
Program should be written is c thus the program should be run as following:
gcc -o poker poker.c
./poker KQ23Q TA3J7 => First hand wins!
The hands must be ranked in following order from best to the worst: Four of a kind, Full House, Triples, Two pairs, Pair, Highest card. If for
example the hand has pairs with the same card AA346 AA258 the latter one wins because of the higher high card. A tie can also be possible.
Here are some hands and the right outcomes:
KTQTT AAQQT => First hand wins!
AKKAA 222T2 => Second hand wins!
A3A46 K32KT => First hand wins!
A3A46 258AA => Second hand wins!
TA982 98TA2 => It’s a tie!
32233 A4A5A => First hand wins!
The code should be preferably pushed to the github in a private repository.
