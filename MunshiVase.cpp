// STRATEGY 3 - queue

// No more than 20 seconds
// my solution takes: 
// if so, its contention or infinite loop
// or bad RNG and someone enters the room like a million times

#include <iostream>

// For queueueue
#include <queue>

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

int countedGuests = 0;
const int numGuests = 100;
bool everyoneSeen = false;
//bool inRoom = false;
bool invited[numGuests] = {0}; // a value of 1 means that guest is invited and currently in the labyrinth
bool seenVase[numGuests] = {0}; // if all 1's, that means everyone invited at least once and we won
queue<int> vaseQueue;




    // MINOTAUR VASE //

void seeVase(int guestId) {
    bool didISeeVase = false;
    while (!everyoneSeen) {
        // simulates the guest going around doing other things at the party before wishing to join the queue
        float partyingTime = (rand() % 20 + 1)/ 20; 
        Sleep(partyingTime);
        vaseQueue.push(guestId);


        // if queue is empty and ready to join:
        if (vaseQueue.size() == 1) {
            //cout << "\nHEY THIS IS EMPTY IM COMING IN:";
            //cout << guestId;

            // add self to queue
            invited[guestId] = true;
        }

        /*else {
            //cout << "\n";
            //cout << "I'm sad I have to wait in queue :(";
            //cout << guestId;
    
            //add self to queue
            vaseQueue.push(guestId);
        }*/



        while (!invited[guestId])// waits until invited
            Sleep(0.1); // VERY IMPORTANT to release the CPU
            if (everyoneSeen) // kills thread ( i can probably go without this but idk)
                return; 
         
        ////cout << "\nIm in the lab and my ID is ";
        ////cout << guestId;
        
        // WHEN FINALLY INVITED IN:
    // simulates the guest looking at the vase
        float viewingTime = (rand() % 20 + 1)/ 20; 
        Sleep(viewingTime);  


        // add self to list who have seen vase:
        if (!didISeeVase) {
            //cout << "\nthis vase sucks";
            //cout << guestId;
            //cout << " man.";
            
            countedGuests++;
            seenVase[guestId] = true;
            didISeeVase = true;
            //cout << boolalpha;
            //cout << didISeeVase;
        }
            

        // notify next guest:
        invited[guestId] = false;
        //cout << "\n\n AM I CURRENTLY INVITED??? ";
        //cout << guestId;
        //cout << boolalpha;
        //cout << invited[guestId];
        //cout << "\n";

        while (vaseQueue.size() <= 3) // waits for the queue to have other guests
            Sleep(1);
            
        // when 2 or more in queue:
        vaseQueue.pop(); // deletes front element (this thread)
        Sleep(10);
        int nextGuest = vaseQueue.front();
        //cout << "\n\nguest ";
        //cout << guestId;
        //cout << " is OUTTT, next up is ";
        //cout << nextGuest;
        invited[nextGuest] = true;

        //party more before queuing up again
        //partyingTime = (rand() % 20 + 1)/ 20; 
        //Sleep(partyingTime);
    }
}



// returns TRUE for WIN (everyone visited and correctly identified) or FALSE if incorrect
bool startVase() {

    //cout << "\n\nBEGIN PARTY\n\n";
    

    /*//cout << "start with random guest";
    int randomGuest = rand() % numGuests; 
    vaseQueue.push(randomGuest);*/
    
    thread threadArray[numGuests];
    vector<thread> threads; 
    for (int i = 0; i < numGuests; i++) {
        //vector <int> &primes, int start, int end
        threads.emplace_back(seeVase, i);
        //Sleep(0.05);
    }

    vector<thread> detachThreads = move(threads);
    for (thread &th : detachThreads) {
        th.detach();
        //Sleep(0.05);
    }

    /*inRoom = true;
    invited[0] = true;
    ////cout << "lets see if he made it in\n";
    while (inRoom);
    ////cout << "\nhes out!";
    everyoneSeen = true;*/
    ////cout << "\ninviting guest id:";
    

    // keep checking if all have seen
    while (!everyoneSeen) {
        Sleep(0.2);
        if (countedGuests == numGuests)
            everyoneSeen = true;
    }

    // if any of the guests haven't seen the vase, return false for FAILED challenge
    for (int i = 0; i < numGuests; i++)
        if (!seenVase[i]) {
            
            //cout << "\nthis one didn't see it";
            //cout <<" it";
            //cout << i;
            return false;
        }

    return true;
}


int main() {
    cout << "Im about to start (I hard coded 100 guests btw it should take only 3.1 sec)";
    bool win = startVase();
    if (win)
        cout << "\n\n WE WONNN BABYYYY";
    else
        cout << "\n\n:(";
    return(0);
}