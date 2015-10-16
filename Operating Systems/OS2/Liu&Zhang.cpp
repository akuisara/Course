/*
 Jingxian Liu & Qi (Sara) Zhang
 Program Name: Project OS2
 
 Purpose: The purpose of this project is to use both threads and semaphonres 
    to simulate the Latex text formating system.
 
 Input: 
    1) Input from keyboard: Filename
    2) An input text file of any length, which contains normal words, 
        punctuations, and control sequences '\c' (capitalize the first 
        letter of the next word), '\C' (capitalize all of the letters 
        of the next word), and '\u' (underline the next word (simulate 
        this by _word_))
 
 Output:
    1) Output on console:
            Prompt to enter input filename
            Error messages while file not found
    2) Output files: finalAnswer.txt

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


using namespace std;

// Function declarations
void * Store_Char_Array(void *);
void * Process_One_Line(void *);
void * Align_Display_Text(void *);

// Declare global constants and variables
const int total_lines = 200;
const int total_chars = 60;
const int outcolumn=50;
pthread_mutex_t mutex1, mutex2, mutex3;  // Counter semaphores

// Declare global boolean values
bool threadOneDone = false;
bool threadTwoDone = false;

int main() {
    
    // Initialize a two dimensional array with 200 lines,  
    // and 60 characters per line
    char ** input_content = new char*[total_lines];
    for (int i = 0; i < total_lines; i++) {
        input_content[i] = new char[total_chars];
    }

    // Set up semaphores
    pthread_mutex_init (&mutex1, NULL);
    pthread_mutex_init (&mutex2, NULL);
    pthread_mutex_init (&mutex3, NULL);

    // Lock mutex2 and mutex3
    pthread_mutex_lock (&mutex2);
    pthread_mutex_lock (&mutex3);
    
    // Initialize and create three processes
    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, Store_Char_Array, (void *) input_content);
    pthread_create(&thread2, NULL, Process_One_Line, (void *) input_content);
    pthread_create(&thread3, NULL, Align_Display_Text, (void *) input_content);
    
    // Wait for each thread to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Deallocate semaphores
    pthread_mutex_destroy (&mutex1);
    pthread_mutex_destroy (&mutex2);
    pthread_mutex_destroy (&mutex3);

    return 0;
}


void * Store_Char_Array(void * ptr)
{
    /* This function takes value from an input file and store the value into a two dimensional array, which has 200 lines in total, and 60 characters per line.
     - Pre-condition: An character array pointer 'ptr' needs to be passed into this function. 'ptr' points to a two dimensional array.
     - Post-condition: The modified 'ptr' will be passed back to the main function by reference.
     - Return: None
     */
    
    
    // Pass the pointer (pass by reference), and then cast void pointer to struct storeSublist
    char **temp_ptr = (char **) ptr;
    
    // Declare and set input filename
    string filename;
    
    // Get input filename from keyboard
    cout << "Please enter filename: (e.g., randomNums.txt)\n";
    getline(cin, filename);
    
    cout << "Filename: " << filename << endl;
    
    // Open input file. Exit if cannot open the file, print error message on console
    ifstream input_file;
    input_file.open(filename.c_str());
    if (!input_file.is_open())
    {
        cout<<"Error, file does not exist";
        exit(-1);
    }
    
    
    int count_line = 0;
    string next_line;
    // Iterate through each line of the input file to store data into the two dimensional array
    while (getline(input_file, next_line)) {
        // Lock itself
        pthread_mutex_lock(&mutex1);
       
        for(int i=0; i<next_line.length(); i++){
            temp_ptr[count_line][i] = next_line[i];
        }

        count_line++;

        // Unlock thread 2
        pthread_mutex_unlock(&mutex2);

    }

    // Change the boolean value after the first thread finished
    threadOneDone = true;
}


void * Process_One_Line(void * ptr)
{
    /* This function handles each line of the two dimensional array, and changes the characters based on the rules of the control sequences.
     - Pre-condition: An character array pointer 'ptr' needs to be passed into this function. 'ptr' points to a two dimensional array.
     - Post-condition: The modified 'ptr' will be passed back to the main function by reference.
     - Return: None
     */
    
    // Pass the pointer (pass by reference), and then cast void pointer to struct storeSublist
    char **temp_ptr = (char **) ptr;

    int j=0, i=0;
    // Running thread 2 while the first thread has not finished running
    while (!threadOneDone) {
        // Lock itself
        pthread_mutex_lock(&mutex2);

        j=0;
        while (temp_ptr[i][j]!= 0){
            if (temp_ptr[i][j]=='\\'){
                // Capitalize the first letter of the next word if the word is led by \c
                if (temp_ptr[i][j+1]=='c'){
                    temp_ptr[i][j+2] = toupper(temp_ptr[i][j+2]);
                    temp_ptr[i][j] = ' ';
                    temp_ptr[i][j+1] =' ';
                }
                // Capitalize all of the letters of the next word if the word is led by \C
                else if (temp_ptr[i][j+1]=='C'){
                    
                    int temp = j;
                    while(temp_ptr[i][temp+2] != ' ' && temp_ptr[i][temp+2] != 0){
                        temp_ptr[i][temp+2] = toupper(temp_ptr[i][temp+2]);
                        temp++;
                    }
                    temp_ptr[i][j] = ' ';
                    temp_ptr[i][j+1] = ' ';

                }
                // Underline the next word (simulate this by _word_) if the word is led by \u
                else if(temp_ptr[i][j+1]=='u'){
                    temp_ptr[i][j] = '_';
                    int temp = j;
                    while(temp_ptr[i][temp+1]!=' ' && temp_ptr[i][temp+1] != '\n'){
                        temp_ptr[i][temp+1] = temp_ptr[i][temp+2];
                        temp++;
                    }
                    temp_ptr[i][temp] = '_';
                }
            }
            j++;
        }
        i++;

        // Unlock thread 3
        pthread_mutex_unlock(&mutex3);
        
    }

    // Change the boolean value after the second thread finished
    threadTwoDone = true;

}


void * Align_Display_Text(void * ptr)
{
    /* This function takes each of the modified line and displays the text on both the console and the screen. The output is left and right justified.
     - Pre-condition: An character array pointer 'ptr' needs to be passed into this function. 'ptr' points to a two dimensional array.
     - Post-condition: The modified 'ptr' will be passed back to the main function by reference.
     - Return: None
     */
    
    // Pass the pointer (pass by reference), and then cast void pointer to struct storeSublist
    char ** temp_ptr = (char **) ptr;

    // Declare output stream
    ofstream outfile;
    // Generate the output into an output file called "finalAnswer.txt"
    outfile.open("finalAnswer.txt");

    int i = 0;
    // Running thread 3 while the first and the second threads have not finished running
    while (!threadOneDone || !threadTwoDone) {
        // Lock itself
        pthread_mutex_lock (&mutex3);
        //count the length of the row
        int countnum = 0;
        while(temp_ptr[i][countnum] != 0){
            countnum++;
        }
        int index = 0;
        // check if both thread one and two are done
        // if it is, just print out the last line
        if (threadOneDone && threadTwoDone){
            for (int j =0; j< countnum; j++){
                outfile << temp_ptr[i][j];
                cout << temp_ptr[i][j];
            }
            outfile << endl;
            cout << endl;
            outfile.close();

        }
        //if not, put space into the last space
        else{

            //get the space in the row
            
            for(int j = 0; j < countnum; j++){
                if(temp_ptr[i][j] == ' '){
                    index = j;
                }
            }
            //insert in spaces where there are space to fill 50 slot
            
            for(int j = 0; j < index; j++){

                cout << temp_ptr[i][j];
                outfile << temp_ptr[i][j];  
            }
            
            for(int k = index; k < (outcolumn - countnum + index); k++){

                cout << ' ';
                outfile << ' ';
            }
            
            for(int l = (outcolumn - countnum + index); l < outcolumn; l++){
                //print out the rest of the row
                cout << temp_ptr[i][l-(50 - countnum)];
                outfile << temp_ptr[i][l-(outcolumn - countnum)];
            }

            i++;

            // Unlock thread 1
            pthread_mutex_unlock (&mutex1);
            cout << endl;
            outfile << endl;
        }
    }
    
}
