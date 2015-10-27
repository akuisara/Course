/*
 
 Program Name: Project OS3
 
 Purpose: The purpose of this project is ...
 
 Input: 
    1) Input from keyboard: 
        - Input filename
        - The total simulation time (in integer seconds)
        - The quantum size (in integer milliseconds; usually between 10 and 100)
        - The number of processes allowed in the system (degree of multiprogramming - how many jobs are in the system)
    2) An input text file contains incoming jobs. The first line is an integer that represents the total number of lines (jobs) in the file. Each subsequent line has four integers: start time of the job, PID, the probability of I/O requests, and the job length.

 Output:
    1) Output on console:
        - Prompt to enter input filename, simulation time, quantum size and the degree of multiprogramming
        - Error messages while file not found
        - Throughput (number of jobs completed during the simulation)
        - Number of jobs still in system
        - Number of jobs skipped
        - Average job length excluding I/O time
        - Average turnaround time
        - Average waiting time per process
        - Percentage of time CPU is busy (CPU utilization)

Question:
    - Are we assuming that the user inputs are in correct form, do we need to handle exceptions?
    - 

 - We have abided by the Wheaton College honor code in this work.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <cstdlib> // Avoid the error related to exit() function
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <map>


using namespace std;

// Function declarations
void * Handle_Int_Array(void *);


int main() {
    
    // Declare and set input filename
    string filename;
    
    // Get input filename from keyboard
    cout << "Please enter filename: (e.g., input.txt)\n";
    getline(cin, filename);
    
    // Open input file. Exit if cannot open the file, print error message on console
    ifstream input_file;
    input_file.open(filename.c_str());
    if (!input_file.is_open())
    {
        cout<<"Error, file does not exist";
        exit(-1);
    }

    int totalJobs;
    input_file >> totalJobs;
    const int total_line = totalJobs;

    // Initialize a two dimensional array with 200 lines,  
    // and 60 characters per line
    int ** input_content = new int*[total_line];
    for (int i = 0; i < total_line; i++) {
        input_content[i] = new int[4];
    }

    int count_line = 0;
    // Iterate through each line of the input file to store data into the two dimensional array
    while (!input_file.eof()) {
        for(int i=0; i<4; i++){
            input_file >> input_content[count_line][i];
        }
        count_line++;
    }

    // Initialize and create three processes
    int multiprogrammingDegree;
    cout << "Degree of multiprogramming: ";
    cin >> multiprogrammingDegree;

    map<string, int> ThreadName;
    for (int i=1; i <= multiprogrammingDegree; i++) {
        pthread_t ThreadName["thread"+to_string(i)] = i;
        pthread_create(&ThreadName["thread"+to_string(i)], NULL, Store_Char_Array, (void *) input_content);
    }

    // Wait for each thread to finish
    // for (int i=1; i <= multiprogrammingDegree; i++) {
    //     pthread_join(ThreadName["thread"+to_string(i)], NULL);
    // }

    return 0;
}


void * Handle_Int_Array(void * ptr)
{
    /* This function ...
     - Pre-condition: An integer array pointer 'ptr' needs to be passed into this function. 'ptr' points to a two dimensional array.
     - Post-condition: The modified 'ptr' will be passed back to the main function by reference.
     - Return: None
     */
    
    
    // Pass the pointer (pass by reference), and then cast void pointer to struct storeSublist
    int *temp_ptr = (int *) ptr;
    cout << "haha\n";

}
