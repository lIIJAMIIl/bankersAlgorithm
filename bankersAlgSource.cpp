//Josh Romisher
//Banker's Algorithm
//Operating Systems
//11/18/22

#include <iostream>
#include <fstream>
#include <cstdlib>

using std::cout; using std::endl; using std::ifstream;

/*numProc represents the # of processes*/
const int numProc = 5;      

/*numRes represents the # of resources*/
const int numRes = 3;

bool safetyTest(int proc[], int available[], int max[][numRes], int allocated[][numRes]);

int main(){
    
    /*Declaring array data structures*/
    int allocated[numProc][numRes];
    int max[numProc][numRes];
    int available[numRes];

    /*Opening File Stream*/
    ifstream arrayIn;
    arrayIn.open("bankersAlgInput.txt");
    if(arrayIn.fail()){
        cout << "Error, file failed to open";
        exit(1);
    }

    for(int i = 0; i < numRes; ++i){
        arrayIn >> available[i];
    }
    
    for(int i = 0; i < numProc; ++i)
        for(int j = 0; j < numRes; ++j){
            arrayIn >> allocated[i][j];
        }
    
    for(int i = 0; i < numProc; ++i)
        for(int j = 0; j < numRes; ++j){
            arrayIn >> max[i][j];
        }

    arrayIn.close();

    cout << "Reading array input from file is complete, file closed\n";

    /*Process array for bool safetyTest parameter*/
    int proc[] = {0, 1 ,2 ,3 ,4};
    
    /*Available array Printout*/
    for(int i = 0; i < numRes; ++i)
        cout << "Resource " << i << " contains " <<  available[i] << " available instances of the resource" << endl;

   /*Allocated array printout*/
    for(int i = 0; i < numProc; ++i)
        for(int j = 0; j < numRes; ++j){
            cout << "Process P" << i << " is currently allocated " << allocated[i][j] << " instance(s) of resource " << j << endl;
    }
    
    /*Max instances of resource process can request*/
    for(int i = 0; i < numProc; ++i)
        for(int j = 0; j < numRes; ++j){
            cout << "Process P" << i << " may request at most " << max[i][j]<< " instances of resource " << j << endl;
    }

    safetyTest(proc, available, max, allocated);

    return 0;
        
}

bool safetyTest(int proc[], int available[], int max[][numRes], int allocated[][numRes]){
    /*Need vector initialization*/

    int need[numProc][numRes];

        for(int i = 0; i < numProc; ++i)
            for(int j = 0; j < numRes; ++j){
                need[i][j] = max[i][j] - allocated[i][j];
            }
    /*Finish vector keeps track of which processes are complete, initialized to false for all indeces*/
    int finish[numProc] = {0};

    /*correctSeq vector holds the Process numbers in order of safe sequence*/
    int correctSeq[numProc] = {0};

    /*Work vector, a copy of available resources to track available resources*/
    int work[numRes];
    for(int i = 0; i < numRes; ++i){
        work[i] = available[i];
        cout << "Work vector contains value " << work[i] << " at index " << i << endl;
    }

    /*Keeping track of number of unfinished processes or processes in safe state*/
    int safeCount = 0;

    while(safeCount < numProc){

        bool foundSafe = false;
        /*Scanning through each process, checking if finished, if not*/
        for(int p = 0; p < numProc; ++p){
            if(finish[p] == 0){
                int j;
                for(j = 0; j < numRes; ++j)
                    if(need[p][j] > work[j])
                        break;
                    
                /*Variable j reaches numRes without need[] execceding work[], process is able to complete,
                 releases resources to work, process added to correctSeq[], marks self as finished in finish[]*/
                if(j == numRes){
                    for(int k = 0; k < numRes; ++k){
                        work[k] += allocated[p][k];
                    }
                    correctSeq[safeCount++] = p;
                    finish[p] = 1;

                    foundSafe = true;
                }
            }
        }

        if(foundSafe == false){
            cout << "Error, system is not currently in a safe state" << endl;
            return false;
        }

    }

    cout << "System is currently in a safe state, and the correct sequence of process execution is: ";
    for(int i = 0; i < numProc; ++i){
        cout << correctSeq[i] << "->";
    }
    return true;
}
