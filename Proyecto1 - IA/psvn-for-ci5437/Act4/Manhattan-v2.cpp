#include <iostream>
#include <fstream> 
#include <sys/time.h>
#include <sstream>
#include <string>

using namespace std;

// Funcion heuristica Manhatan

int manhatan(state_t state){
	char stateArr[100];
	sprint_state(stateArr,100,&state);
	string vals(stateArr);
	std :: istringstream iss(vals);
        string curr;
	iss >> curr;
	int first;
	int i =0;
	int sum = 0;
	
	while(i<16){
		if curr == 'B';
			continue;
		first = atoi(curr.c_str());
		int row = first/4;
		int col = first % 4;
		int row2 = i/4;
		int col2 = i % 4;
		sum += abs(row + col - row2 - col2);			
		iss >> curr;
		i++;
		
	}
	return sum;
}
