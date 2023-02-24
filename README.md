# ParallelAssignment2
_Minotaur Cupcake in Labyrinth and Vase Viewing_  
  
`g++ -std=c++20 -pthread MunshiMinotaur.cpp`  or `g++ -std=c++20 -pthread MunshiVase.cpp` 
to compile, then 
`.\a`
to execute. 

#### Isaac Munshi is391848 5090407 2/23/2023  
#### COP 4520 Concepts of Parallel and Distributed Processing

For #1, my solution was based on choosing a 'leader' out of the guests (Guest # 0) to start the chain and to keep count of how many times the cupcake was eaten.  
For #2, I chose approach #3 with a queue to serve the guests.


# Problem 1 - Cupcakes
## Proof of Correctness:
### Safety Property  
#### Mutual Exclusion  
In the Cupcake problem, I designed my solution such that only 1 guest (thread) may enter the maze at a time.  
My threads were not computing on objects - instead, they were all running on seperate instances of a function.  
So, without the use of object private variables, how do we keep track of thread ID's, and how do we keep track of a variable to show whether or not a thread is in the maze?  

To work around not having private variables, I instead used a function parameter to carry the ID for each thread which I assigned in the instantiating for-loop.  
Then, to keep track of who is in the labyrinth (globally), I used a global/public boolean variable called `inLab` to show if someone is in the labyrinth.  
To tell a specific thread to enter the labyrinth, I created a global/public array called `invited` whose n-indexes represent each one of the n-guests.  
For example, `invited` gets initialized with all `false`s. But when index 9 is `true`, that means the thread with an ID of 9 is allowed to enter the labyrinth.

Through the use of `inLab` and `invited`, I have maintained Mutual Exclusion. When `inLab` is true, exactly 1 thread is allowed into the lab, and our Main function hangs with the line `while (inLab);`.  
After a thread is done eating their cupcake, they change `inLab` to true, which only then allows Main to continue and invite another guest.  
Also, through simple means, only one value of `invited` would ever be true, and each thread waits for their index to be `true` before doing anything.  
Thus, only 1 thread is active in the maze at a time.
    
### Liveness Property  
#### No Infinite Loop  
I actually ran into many infinite loops while producing this code, but it was simply logic issues.  
It is a little difficult to manage all of the flags when both the Main function and the thread functions both operate on them, but after some bug-fixing and troubleshooting, I fixed all my logic.  
The simple no-loop logic is that one person is designated the leader (the thread with ID 0), and he counts +1 every time he sees a cupcake on the plate.  
All the others follow a simple rule: if the plate is empty, and it's their first time seeing an empty plate, they must eat a cupcake (if they want) and, more importantly, leave the plate with a cupcake on it.    
If there is already a cupcake on the plate, do nothing.  
If there is no cupcake but they have already eaten a cupcake, do nothing.  
  
This strategy allows the leader to count the guests that have visited. Each time a guest visits (when the plate is empty), they leave a cupcake, and that acts as a flag to the leader.  
Thus, the leader just counts until they count to the number of guests they started with.


# Problem 1 - Cupcakes
## Proof of Correctness:
### Safety Property  
#### Mutual Exclusion/No Conten
In the Vase problem, I chose approach #3 which makes use of a Queue and I did not have to use a boolean like I did last time in the case of `inLab`.  
Instead, the queue acts as a flag itself (if it is empty/only has 1 element).  
  
Also, the queue is naturally mutually exclusive. Although many threads can push their values onto it in the same instance, you can only pop 1 element at a time.  
I used this to my advantage and I let the threads push their ID's whenever they were done partying. I simulted their partying by having the thread sleep for a random amount of time.  
If they were the only one in the queue, they can go right on in. Otherwise, they stand in line and sleep.  
Then, when the thread viewing the vase is done, the thread itself 'notifies' the other thread by popping itself off the queue and calling the top-most value of the queue - the next thread in line.  
I used a similar tactic to problem 1 by having an array to see who is invited to the room called `invited`.  
So, when a thread leaves the vase room, they set their `invited` value to `false`, they pop their ID off of the queue, and then they look at the new head and set the appropriate `invited` index to true to signal the next thread to enter.  

So by the use of a queue, only 1 value in `invited` is ever true at a time thus proving Mutual Exclusion.

    
### Liveness Property  
#### No Infinite Loop  
I actually ran into many infinite loops while producing this code, but it was simply logic issues.  
It is a little difficult to manage all of the flags when both the Main function and the thread functions both operate on them, but after some bug-fixing and troubleshooting, I fixed all my logic.  
The simple no-loop logic is that one person is designated the leader (the thread with ID 0), and he counts +1 every time he sees a cupcake on the plate.  
All the others follow a simple rule: if the plate is empty, and it's their first time seeing an empty plate, they must eat a cupcake (if they want) and, more importantly, leave the plate with a cupcake on it.    
If there is already a cupcake on the plate, do nothing.  
If there is no cupcake but they have already eaten a cupcake, do nothing.  
  
This strategy allows the leader to count the guests that have visited. Each time a guest visits (when the plate is empty), they leave a cupcake, and that acts as a flag to the leader.  
Thus, the leader just counts until they count to the number of guests they started with.

# Problem 2 - Vase
## Proof of Correctness:
### Safety Property  
#### Mutual Exclusion/No Contention
In the Vase problem, I chose approach #3 which makes use of a Queue and I did not have to use a boolean like I did last time in the case of `inLab`.  
Instead, the queue acts as a flag itself (if it is empty/only has 1 element).  
  
Also, the queue is naturally mutually exclusive. Although many threads can push their values onto it in the same instance, you can only pop 1 element at a time.  
I used this to my advantage and I let the threads push their ID's whenever they were done partying. I simulted their partying by having the thread sleep for a random amount of time.  
If they were the only one in the queue, they can go right on in. Otherwise, they stand in line and sleep.  
Then, when the thread viewing the vase is done, the thread itself 'notifies' the other thread by popping itself off the queue and calling the top-most value of the queue - the next thread in line.  
I used a similar tactic to problem 1 by having an array to see who is invited to the room called `invited`.  
So, when a thread leaves the vase room, they set their `invited` value to `false`, they pop their ID off of the queue, and then they look at the new head and set the appropriate `invited` index to true to signal the next thread to enter.  

So by the use of a queue, only 1 value in `invited` is ever true at a time thus proving Mutual Exclusion.

    
### Liveness Property  
#### No Infinite Loop  
I actually ran into many infinite loops while producing this code, but it was simply logic issues.  
It is a little difficult to manage all of the flags when both the Main function and the thread functions both operate on them, but after some bug-fixing and troubleshooting, I fixed all my logic.  
The simple no-loop logic is that one person is designated the leader (the thread with ID 0), and he counts +1 every time he sees a cupcake on the plate.  
All the others follow a simple rule: if the plate is empty, and it's their first time seeing an empty plate, they must eat a cupcake (if they want) and, more importantly, leave the plate with a cupcake on it.    
If there is already a cupcake on the plate, do nothing.  
If there is no cupcake but they have already eaten a cupcake, do nothing.  
  
This strategy allows the leader to count the guests that have visited. Each time a guest visits (when the plate is empty), they leave a cupcake, and that acts as a flag to the leader.  
Thus, the leader just counts until they count to the number of guests they started with.

  
Q.E.D.
