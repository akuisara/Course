/*
 
 Program Name: Project OS3
 
 Purpose: The purpose of this project is ...
 
 Input: 
    1) Input from keyboard: 
        - Input filename
        - The total simulation time (in integer seconds)
        - The quantum size (in integer milliseconds; usually between 10 and 100)
        - The number of processes allowed in the system (degree of multiprogramming - how many jobs are in the system)
    2) An input text file contains incomingQueue jobs. The first line is an integer that represents the total number of lines (jobs) in the file. Each subsequent line has four integers: start time of the job, PID, the probability of I/O requests, and the job length.

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
    - 

 - We have abided by the Wheaton College honor code in this work.
*/

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include<queue>
using namespace std;


//global int PROBABILITY;
time_t ioTimeStart = 0;

bool jobLeftInCPU = false;
bool enterIO = true;

int ioJobLength;
int totalJobLength = 0;
int totalWaitTime = 0;

const int PENALTYENTERCPU = 4;

struct jobs
{
    int jobStartTime;
    int jobPID;
    int jobProbIORequest;
    int jobLength;
    int jobLengthOriginal;
    bool firstEnter;// = false;
};

queue<jobs> incomingQueue;
queue<jobs> readyQueue;
queue<jobs> ioQueue;


int randomNumber(int start, int endtime)
{
    int randomNumber;
    srand(time(NULL));
    randomNumber = rand() % endtime + start;
    return randomNumber;
}

void io(int quantum, queue<jobs> &readyQueue, queue<jobs> &ioQueue, int &throughput, int &jobsInSystem){
    if(ioTimeStart != 0 ){
        if ((ioJobLength < (time(NULL) - ioTimeStart))) {
            enterIO = false;
        } else {
            enterIO = true;
        }
    }

    if(!ioQueue.empty() && enterIO){
        jobs inIO;
        inIO = ioQueue.front();

        ioTimeStart = time(NULL);
        
        // Pop the job after finished the IO
        ioQueue.pop();

        if (inIO.jobLength > 0) {
            // Generate initial random value for new process and put it at the end of the readyQueue queue
            ioJobLength = randomNumber(10,25);
            readyQueue.push(inIO);
        }
        
    }
}

int cpu(int quantum, queue<jobs> &readyQueue, queue<jobs> &ioQueue, int &throughput, int &jobsInSystem, int systemTimeAt, int simulationTime)
{
    if(!readyQueue.empty()){

        jobs inCPU;
        inCPU = readyQueue.front();

        if (inCPU.firstEnter == false){
            systemTimeAt = inCPU.jobStartTime;
            inCPU.firstEnter = true;
        }

        systemTimeAt = systemTimeAt + PENALTYENTERCPU;
        readyQueue.pop();
        cout << "\n\n\n\nBefore: " << systemTimeAt << endl;


        cout << "-------- cpu -------\n"
             << inCPU.jobStartTime << "\t"
             << inCPU.jobPID << "\t"
             << inCPU.jobProbIORequest << "\t"
             << inCPU.jobLength << "\n"
             << inCPU.firstEnter << "\n"
             << "-------- cpu -------\n";

        if((inCPU.jobLength > quantum) && ((systemTimeAt + quantum) <= simulationTime ))
        {
            inCPU.jobLength = inCPU.jobLength - quantum;
            systemTimeAt = systemTimeAt + quantum;
            int rrandomNumber;
            rrandomNumber = randomNumber(1,100);
            if(inCPU.jobProbIORequest <= rrandomNumber)
            {
                ioQueue.push(inCPU);
            }
            else
            {
                readyQueue.push(inCPU);
            }

        }
        else if(inCPU.jobLength <= quantum && ((systemTimeAt + quantum) <= simulationTime ))
        {
            systemTimeAt = systemTimeAt + inCPU.jobLength;
            inCPU.jobLength = inCPU.jobLength - inCPU.jobLength;
            throughput++;
            totalJobLength += inCPU.jobLengthOriginal;
            totalWaitTime += systemTimeAt - inCPU.jobLengthOriginal;
            cout << "Sys time: " << systemTimeAt << endl << "Total Wait: " << totalWaitTime << endl;

            int rrandomNumber;
            rrandomNumber = randomNumber(1,100);
            if(inCPU.jobProbIORequest <= rrandomNumber)
            {
                ioQueue.push(inCPU);
            }
            
            if(!incomingQueue.empty())
            {
                readyQueue.push(incomingQueue.front());
                readyQueue.pop();
            }
        } else if ((systemTimeAt + quantum) > simulationTime ) {
            systemTimeAt = simulationTime;
            jobLeftInCPU = true;
        }
    }
    cout << "After: " << systemTimeAt << endl;
    return systemTimeAt;
};

int nbjobsstillinsystem(queue<jobs> readyQueue, queue<jobs> ioQueue)
{
    int jobsInSystem = 0;
    while(!readyQueue.empty())
    {
        jobsInSystem++;
        readyQueue.pop();
    }
    while(!ioQueue.empty())
    {
        jobsInSystem++;
        ioQueue.pop();
    }
    if (jobLeftInCPU){
        jobsInSystem++;
    }

    return jobsInSystem;
}

int totaljobsSkipped(queue<jobs> incomingQueue)
{
    int jobsSkipped = 0 ;
    while(!incomingQueue.empty())
    {
        jobsSkipped++;
        incomingQueue.pop();
    }
    return jobsSkipped;
}

int main()
{
    ifstream file;
    string filename;
    float simulationTime;
    int quantumSize;
    int numProcesses;
    int lines;

    cout << "Please enter the file name: ";
    // cin >> filename;
    filename = "input.txt";
    file.open(filename.c_str());

    if(file.is_open())
    {
        int throughput = 0;
        int jobsInSystem = 0;
        int systemTimeAt = 0;
        int jobsSkipped = 0;

        cout << "What is the desired simulation time (in seconds)? ";
        cin >> simulationTime;
        simulationTime = simulationTime * 1000;

        cout << "What is the desired quantum size (in milliseconds)? ";
        cin >> quantumSize;

        cout << "What is the number of processes allowed in the system? ";
        cin >> numProcesses;

        jobs nextjob;
        file >> lines;
        for(int i=0; i<lines; i++)
        {
            file >> nextjob.jobStartTime 
                 >> nextjob.jobPID 
                 >> nextjob.jobProbIORequest 
                 >> nextjob.jobLength;

            nextjob.firstEnter = false;
            nextjob.jobLengthOriginal = nextjob.jobLength;
            incomingQueue.push(nextjob);

            cout << nextjob.jobStartTime << "\t"
                 << nextjob.jobPID << "\t"
                 << nextjob.jobProbIORequest << "\t"
                 << nextjob.jobLength << "\n";
        }

        for(int j=0; j<numProcesses; j++)
        {
            readyQueue.push(incomingQueue.front());
            incomingQueue.pop();
        }

        while(systemTimeAt < simulationTime && (!readyQueue.empty() || !ioQueue.empty()))
        {

            systemTimeAt = cpu(quantumSize, readyQueue, ioQueue, throughput, jobsInSystem, systemTimeAt, simulationTime);
            io(quantumSize, readyQueue, ioQueue, throughput, jobsInSystem);
        }
        jobsInSystem = nbjobsstillinsystem(readyQueue, ioQueue);
        jobsSkipped = totaljobsSkipped(incomingQueue);

        // Need to change the output placeholders
        cout << "\n\n\n\nThroughput (number of jobs completed during the simulation):\t" << throughput << endl
             << "Number of jobs still in system:\t" << jobsInSystem << endl
             << "Number of jobs skipped:\t" << jobsSkipped << endl
             << "Average job length excluding I/O time:\t" << totalJobLength/throughput << " (ms)" << endl
             << "Average turnaround time:\t" << throughput << " (ms)" << endl
             << "Average waiting time per process:\t" << totalWaitTime << " (ms)" << endl
             << "CPU utilization (percentage of time CPU is busy):\t" << throughput << '%' << endl;

    }
    else
        cout << "sorry not a valid file" << endl;


    return 0;
}
