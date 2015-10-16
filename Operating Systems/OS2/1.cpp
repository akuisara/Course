#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;


int main(){

	char ** ptr = new char* [3];
	for(int i = 0; i < 3; i ++){
		ptr[i] = new char[60];
	}


	string infilename; // the name of the user input file

	cout << "Please enter the name of the text file:" << endl;
	cin >> infilename; // get the input filename

	string line;
	int count_line = 0;
	//read in all the text
	ifstream infile (infilename.c_str()); // open the input file
	if(infile.is_open()){
		while(getline(infile, line)){		
			for(int i = 0; i < line.length(); i++){
				ptr[count_line][i] = line[i];		
			}
			count_line ++;
			cout << line.length() << endl;
		}
	}


	int line_count = 0;
	while(line_count < 3){
		int i = 0;	
		for(int i = 0; i < 60; i++){
			if(ptr[line_count][i] == '\\'){
				if(ptr[line_count][i+1] == 'c'){
					ptr[line_count][i+2] = toupper(ptr[line_count][i+2]);
					ptr[line_count][i] = ' ';
					ptr[line_count][i+1] = ' ';
				}
				else if(ptr[line_count][i+1] == 'C'){
					int j = i;
					while(ptr[line_count][j+2] != ' ' && ptr[line_count][j+2] != 0){
						ptr[line_count][j+2] = toupper(ptr[line_count][j+2]);
						j++;
					}
					ptr[line_count][i] = ' ';
					ptr[line_count][i+1] = ' ';
					// int k = i;
					// while(ptr[line_count][k] != 0){
					// 	ptr[line_count][k] = ptr[line_count][k+2];
					// 	k++;
					// 	cout<< k<< endl;
					// }
				}
				else if(ptr[line_count][i+1] == 'u'){
					int k = i;
					ptr[line_count][k] = '_';
					while(ptr[line_count][k+1] != ' ' && ptr[line_count][k+1] != 0){ // include punctuation
						ptr[line_count][k+1] = ptr[line_count][k+2];
						k++;
					}
					ptr[line_count][k] = '_';
				}
			}
		}
		int a =0;
		string line1;
		while(ptr[line_count][a] != 0){
			line1 
		}
	line_count++;
	}



	
	// for(int i = 0; i < 8; i++){
	// 	int j = 0;
	// 	while(ptr[i][j] != 0){
	// 		j++;
	// 	}
	// 	cout << "j is " << j << endl;
	// }








	for(int r = 0; r < 3; r++){
		for(int c = 0; c < 60; c++)
			cout << ptr[r][c];
		cout << endl;
	}

	
	return 0;
}

