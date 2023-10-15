# Entropy-Demonstration
This is a program for demonstrating the tendency towards entropy in a system with two cells. You provide the number of iterations you'd like to simulate, the range of numbers (particles), and the chance that a particle will "hop" into the other cell in a given iteration. It demonstrates just how much our universe tends towards entropy.
This code simulates a system with two cells, you can provide the number of particles, the chance in each new iteration that a particle will "hop" over to the other cell, and the number of iterations you'd like the code to print into a file called "Simulation.txt". This was adapted from an analogy I read on quora (https://qr.ae/pKt9jQ) to explain why Entropy (mostly) always decreases. If you imagine that each particle is distinct but indistinguishible, there are many more cases where the system will have a high entropy state (where the number of particles (n) in each of the cells is similar, the average of the # of particles in a cell approaches n/2) than when there is low entropy. I read the comment on quora and thought it was interesting, but wondered if there was any way to verify it, when I realised that while I couldn't 100% verify it mathematically, I now had the coding skills to at least try to make an accurate simulation of the situation the commenter described. This was my first completely independent coding project, and it was fun to make :) (Here's a graph of the frequency of different numbers in the first cell of a simulation with 100,000 iterations, you can tell just how much of a tendency there is towards entropy: https://imgur.com/Q8IfuMT)
