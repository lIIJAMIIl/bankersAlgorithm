# bankersAlgorithm
Operating Systems Class Project, Banker's Algorithm Implementation

Project Description: This project illustrates the use of the banker's algorithm for deadlock avoidance. I first initialized a series of arrays to hold the necessary data. The values within the arrays were filled using file i/o input from bankersAlgInut.txt. Proc[] holds the identifying number of the processes, so that they can later be assigned to the correctSeq[] array, which holds the correct sequence of processes for the system to be in a safe state. Array available[] holds the current number of resources instances available to the processes attempting to access these resources. Array allocated[] holds the number of resources currently allocated to each process. Array max[] holds the max number of resource instances each process can request. 

I then implemented a boolean function that takes proc[], available[], max[], and allocated[] as parameters. Within this function, safetyTest(), I used array's need[], work[], finish[], and correctSeq[]. Need[]’s values are calculated by taking the max[] array and subtracting the currently allocated resources from allocated[]. Work[] is a copy of available, and keeps track of the resources currently available, as well as those released by processes that have successfully completed. Finish[] keeps track of processes that have completed and released their resources. CorrectSeq[] holds the process numbers in order of completion in a safe state. The function safetyTest() will return an error if the system is not in a safe state after execution, and returns the correct order for processes to complete execution in a safe state otherwise.

Running bankersAlgSource.cpp: g++ bankersAlgSource.cpp -o bankers -> ./bankers //be sure to include bankersAlgInput.txt in directory with bankersAlgSource.cpp
