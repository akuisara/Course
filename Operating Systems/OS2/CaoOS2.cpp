/*
 * Yiqing Cao(Grace)
 *
 * Program name: OS1
 * Purpose: 
 * Input  : 
 * Output : 
 */

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

int row = 200;
int column = 60;
int outcolumn = 50;
int count_line = 0;
int line_count = 0;



// functions:
void * readFile(char ** ptr);
void * modifyText(char ** ptr);
void * displayFile(char ** ptr);



int main(){

	char ** ptr = new char*[row];
	for(int i = 0; i < row; i ++){
		ptr[i] = new char[column];
	}

	readFile(ptr);

	modifyText(ptr);

	displayFile(ptr);

	
	//display the array
	// for(int r = 0; r < count_line; r++){
	// 	for(int c = 0; c < column; c++)
	// 		cout << ptr[r][c];
	// 	cout << endl;
	// }

	return 0;
}

void * readFile(char** ptr){
	string infilename; // the name of the user input file

	cout << "Please enter the name of the text file:" << endl;
	cin >> infilename; // get the input filename

	string line;

	//read in all the text
	ifstream infile (infilename.c_str()); // open the input file
	if(infile.is_open()){
		while(getline(infile, line)){		
			for(int i = 0; i < line.length(); i++){
				ptr[count_line][i] = line[i];		
			}
			count_line ++;
		}
	}
}



void * modifyText(char ** ptr){
	while(line_count < row){	
		int i = 0;
		for(int i = 0; i < column; i++){
			if(ptr[line_count][i] == '\\'){
				if(ptr[line_count][i+1] == 'c'){
					ptr[line_count][i+2] = toupper(ptr[line_count][i+2]);
					ptr[line_count][i] = ' ';
					ptr[line_count][i+1] = ' ';
				}
				else if(ptr[line_count][i+1] == 'C'){
					int j = i;
					while(ptr[line_count][j+2] != ' ' && ptr[line_count][j+2] != '\n'){
						ptr[line_count][j+2] = toupper(ptr[line_count][j+2]);
						j++;
					}
					ptr[line_count][i] = ' ';
					ptr[line_count][i+1] = ' ';
				}
				else if(ptr[line_count][i+1] == 'u'){
					int k = i;
					ptr[line_count][k] = '_';
					while(ptr[line_count][k+1] != ' ' && ptr[line_count][k+1] != '\n'){ // include punctuation
						ptr[line_count][k+1] = ptr[line_count][k+2];
						k++;
					}
					ptr[line_count][k] = '_';
				}
			}		
		}
	line_count ++;
	}
}


void * displayFile(char ** ptr){
	char ** ptr2 = new char* [row];
	for(int i = 0; i < row; i ++){
		ptr2[i] = new char[outcolumn];
	}

	ofstream outfile;
	outfile.open("finalAnswer.txt");

	for(int i = 0; i < row; i++){
		int countnum = 0;
		while(ptr[i][countnum] != 0){
			countnum++;
		}
		int index = 0;
		for(int j = 0; j < outcolumn; j++){
			if(ptr[i][j] == ' '){
				index = j;
			}
		}
		for(int j = 0; j < index; j++){
			ptr2[i][j] = ptr[i][j];	
			outfile << ptr[i][j];	
		}
		for(int k = index; k < (outcolumn - countnum + index); k++){
			ptr2[i][k] = ' ';
			outfile << ' ';
		}
		for(int l = (outcolumn - countnum + index); l < outcolumn; l++){
			ptr2[i][l] = ptr[i][l-(50 - countnum)];
			outfile << ptr[i][l-(outcolumn - countnum)];
		}
		outfile << endl;
	}


	cout << "new: " << endl;

	for(int r = 0; r < row; r++){
		for(int c = 0; c < outcolumn; c++)
			cout << ptr2[r][c];
		cout << endl;
	}




	outfile.close();

}