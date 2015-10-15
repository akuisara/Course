/*
 Qi (Sara) Zhang
 Program Name: Project OS2
 
 Purpose:
 
 Input: 
    1) Input from keyboard:
        Filename
    2) Input files:
 
 Output:
    1) Output on console:
        Prompt to enter input filename if enabled, otherwise only the input filename will show up
        Error messages while file not found
    2) Output files:

 - I have abided by the Wheaton College honor code in this work.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <cstdlib> // Avoid the error related to exit() function
#include <pthread.h>
using namespace std;


// Function declarations
void * Store_Char_Array(void *);
void * Process_One_Line(void *);
void * Align_Display_Text(void *);
const int total_lines = 200;
const int total_chars = 60;
int count = 0;
pthread_mutex_t mutex2, mutex3;
int main() {
    
    char ** input_content = new char*[total_lines];
    for (int i = 0; i < total_lines; i++) {
        input_content[i] = new char[total_chars];
    }
    pthread_mutex_init (&mutex2, NULL);
    pthread_mutex_init (&mutex3, NULL);
    pthread_mutex_lock (&mutex2);
    pthread_mutex_lock(&mutex3);
    
    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, Store_Char_Array, (void *) input_content);
    pthread_create(&thread2, NULL, Process_One_Line, (void *) input_content);
    pthread_create(&thread3, NULL, Align_Display_Text, (void *) input_content);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    
    // Declare output stream
    ofstream output_file;
    
    // Generate the output into an output file called "finalAnswer.txt"
    output_file.open("finalAnswer.txt");
    
    output_file.close();
    
    return 0;
}


void * Store_Char_Array(void * ptr)
{
    /* This function
     - Pre-condition:
     - Post-condition:
     - Return: None
     */
    
    
    // Pass the pointer (pass by reference), and then cast void pointer to struct storeSublist
    char **temp_ptr = (char **) ptr;
    
    // Declare and set input filename
    string filename;
    filename = "text.txt";
    
    // Get input filename from keyboard
    // cout << "Please enter filename: (e.g., randomNums.txt)\n";
    // getline(cin, filename);
    
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
    while (getline(input_file, next_line)) {
        // getline(input_file, next_line);
        pthread_mutex_unclock(&mutex2);
        count_line++;
        for(int i=0; i<next_line.length(); i++){
            temp_ptr[count_line][i] = next_line[i];
//            Test:
           cout << count_line << '\t' << temp_ptr[count_line][i] << endl;
        }
    }
}


void * Process_One_Line(void * ptr)
{
    /* This function 
     - Pre-condition:
     - Post-condition:
     - Return: None
     */
    
    // Pass the pointer (pass by reference), and then cast void pointer to struct storeSublist
    char **temp_ptr = (char **) ptr;
    pthread_mutex_lock(&mutex2);
    count++;
    int j=0;
    for (int i=0; i < count; i++){
        j=0;
        while (temp_ptr[i][j]!='\n'){
            if (temp_ptr[i][j]=='\\'){
                if (temp_ptr[i][j+1]=='c'){
                    temp_ptr[i][j] = upper_case(temp_ptr[i][j+2]);
                    while (temp_ptr[i][j]!='\n'){
                        temp_ptr[i][j]
                    }
                }
                else if (temp_ptr[i][j+1]=='C'){

                }
                else if(temp_ptr[i][j+1]=='u'){

                }
            }
        }
    }

    
}


void * Align_Display_Text(void * ptr)
{
    /* This function
     - Pre-condition:
     - Post-condition:
     - Return: None
     */
    
    // Pass the pointer (pass by reference), and then cast void pointer to struct storeSublist
    char **temp_ptr = (char **) ptr;
    
}
