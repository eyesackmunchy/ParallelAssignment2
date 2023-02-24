// No more than 20 seconds
// my solution takes 1 sec
// if so, its contention or infinite loop
// or bad RNG and someone enters the room like a million times

#include <iostream>

// for square root
#include <cmath>

// For Input/output files
#include <fstream>

// for sleep
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// for threads
#include <thread>

#include <vector>
using namespace std;

bool CUPCAKE = true;
int countedGuests = 0;
const int numGuests = 100;
bool everyoneEaten = false;
bool inLab = false;
bool invited[numGuests] = {0}; // a value of 1 means that guest is invited and currently in the labyrinth
bool answer[numGuests] = {0}; // if all 1's, that means everyone invited at least once and we won





    // MINOTAUR BIRTHDAY //

void enterLab(int guestId) {
    bool didIeat = false;

    while (!everyoneEaten) {

        while (!invited[guestId])// waits until invited
            Sleep(0.1); // VERY IMPORTANT to release the CPU
            if (everyoneEaten) // kills thread ( i can probably go without this but idk)
                return; 
         
        //cout << "\nIm in the lab and my ID is ";
        //cout << guestId;
        
        // special, pre-chosen guest to start off the chain and to count the guests
        if (guestId == 0) {
            if (CUPCAKE) {
                countedGuests += 1;
                //cout << "\n I just counted another guest, the total amount rn is:";
                //cout << countedGuests;
                CUPCAKE = false; // eats cupcake
            }
            if (countedGuests == numGuests) 
                everyoneEaten = true;
        }

        else {
            if (!CUPCAKE && !didIeat) {
                CUPCAKE = true; // calls in cupcake
                didIeat = true;
            }
        }
        inLab = false; // next guest invited by startBirthday()
        invited[guestId] = false;
    }
}


bool getCupCake() {
    return CUPCAKE;
}

void eatCupCake(bool eat) {
    CUPCAKE = !(eat);
}

// returns TRUE for WIN (everyone visited and correctly identified) or FALSE if incorrect
bool startBirthday() {

    cout << "\n\nBEGIN BIRTHDAY\n\n";
    
    vector<thread> threads; 
    for (int i = 0; i < numGuests; i++) 
        //vector <int> &primes, int start, int end
        threads.emplace_back(enterLab, i);

    vector<thread> detachThreads = move(threads);
     for (thread &th : detachThreads) {
        th.detach();
    }


    int nextGuest = 0;
    
    /*inLab = true;
    invited[0] = true;
    //cout << "lets see if he made it in\n";
    while (inLab);
    //cout << "\nhes out!";
    everyoneEaten = true;*/
    //cout << "\ninviting guest id:";
    

    while (!everyoneEaten) {
        nextGuest = rand() % numGuests; 
        inLab = true;
        invited[nextGuest] = true;
        answer[nextGuest] = true;
        //cout << " ";
        //cout << nextGuest;
        //cout << "\n";
        while (inLab);
        invited[nextGuest] = false;
    }

    for (int i = 0; i < numGuests; i++)
        if (!answer[i])
            return false;

    return true;
}


int main() {
    cout << "Im about to start (I hard coded 100 guests btw and averaged 1.7 sec, 500 guests took 10 sec )";
    bool win = startBirthday();
    if (win)
        cout << "\n\n WE WONNN BABYYYY";
    else
        cout << "\n\n:(";
    return(0);
}