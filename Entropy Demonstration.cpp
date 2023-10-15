#include <iostream>
#include <fstream>
#include <random>

//This code simulates a system with two cells, you can provide the number of particles, the chance in each new iteration that a particle will "hop" over to the other cell, and the number of iterations you'd like the code to print into a file called "Simulation.txt". This was adapted from an analogy I read on quora (https://qr.ae/pKt9jQ) to explain why Entropy (mostly) always decreases. If you imagine that each particle is distinct but indistinguishible, there are many more cases where the system will have a high entropy state (where the number of particles (n) in each of the cells is similar, the average of the # of particles in a cell approaches n/2) than when there is low entropy. I read the comment on quora and thought it was interesting, but wondered if there was any way to verify it, when I realised that while I couldn't 100% verify it mathematically, I now had the coding skills to at least try to make an accurate simulation of the situation the commenter described. This was my first completely independent coding project, and it was fun to make :) (Here's a graph of the frequency of different numbers in the first cell of a simulation with 100,000 iterations, you can tell just how much of a tendency there is towards entropy: https://imgur.com/Q8IfuMT)

using namespace std; //I learned that apparently I'm not supposed to do this in big projects because it can create undesired behavior if two commands have the same name in different namespaces, but this project only uses one

class SystemIterations {
public:
    int a;
    int b;
};

SystemIterations GiveIteration(int cellOneValue, int cellTwoValue, float hopChance) { //the meat of the program, the function that gives a new iteration when given the values of the two cells, and the chance of a "hop"
    int counter = 0;
    random_device rd; //this is the seed for the rng
    default_random_engine gen(rd()); //this is the actual generator itself, it's just the default one

    for (int i = 0; i < cellOneValue; i++) {
        bool coin_flip = bernoulli_distribution(hopChance)(gen); //this is what determines the range and does the actual random number calculation, but it's just boolean so I don't need to specify a range, and just use a bernoulli distribution instead, the "hopChance" would usually be 0.5, it specifies the chance of "success" i.e. it returning 1
        if (coin_flip) counter++;
    }
    int newCellOne = cellOneValue - counter;
    int newCellTwo = cellTwoValue + counter;
    //randomly decides how many "jumps" (the counter) occur in one of the cells ("hopChance" chance for each jump), and makes two new variables to represent the adjusted values of the cells, these are the hope from the first cell into the second

    counter = 0;
    for (int i = 0; i < cellTwoValue; i++) { //this uses the original value of the cell that was passed to this function, not the adjusted value, because that would mess it up
        bool coin_flip = bernoulli_distribution(hopChance)(gen);
        if (coin_flip) counter++;
    }
    newCellTwo -= counter;
    newCellOne += counter;
    //this for loop represents the jumps from the second cell into the first one, it adjusts the new ones accordingly

    SystemIterations NewIteration{ newCellOne, newCellTwo }; //the lines above and below sends back the new values for the cells

    return NewIteration;
}

int main() {
    int range;
    float hopChance;
    int numberOfIterations;
    cout << "**Simulation for the Demonstration of Entropy in a System of Two Cells**" << endl << endl;
    cout << "Range: ";
    cin >> range;
    cout << "# Of Iterations: ";
    cin >> numberOfIterations;
    cout << "Chance of 'Hop' (0-1, shouldn't matter, usually 0.5): ";
    cin >> hopChance;
    //has you input the dependencies in the simulation: The amount of particles/range, the chance of a "hop", and the number of iterations to simulate. No matter what you choose the distribution should be the same, so this is only to represent that in all cases entropy will decrease by being able to show all cases lead to the same outcome
  
    ofstream outputFile("Simulation.txt");
    //this creates the file that I'll be sending the data from the simulation to
   
    outputFile << numberOfIterations << " iterations , " << hopChance << " chance , " << "range: " << range << endl;
    //this puts the different conditions you input at the top of the text file that gets spit out, so you know them when looking at the data
   
    int cellValueHolder1 = range/2;
    int cellValueHolder2 = range/2;
    //these variables hold the value of the cell that gets spit out and re-input into the function that gives a new iteration

    for (int i = 0; i < numberOfIterations; i++) {
        SystemIterations Holder = GiveIteration(cellValueHolder1, cellValueHolder2, hopChance);
        outputFile << Holder.a << " , " << Holder.b << endl;
        cellValueHolder1 = Holder.a;
        cellValueHolder2 = Holder.b;
        cout << i+1 << endl; //the +1 is since it starts on 0
    }
    //this runs the Iteration function how ever many times the user says, while spitting out the values the function gives back into the file, and passing the function the new values after each time it runs
    //I also have it output the # of the loop that it's on so you know how much progress is being made

    outputFile.close(); //closes the file

    cout << "Done!"; //says "Done!" when... well... I'm not gonna explain it, you're not an idiot, are you?
}